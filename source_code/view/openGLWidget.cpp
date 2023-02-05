#define GL_SILENCE_DEPRECATION

#include "openGLWidget.h"

#include <QFile>
#include <QOpenGLContext>
#include <QRegularExpression>

namespace s21_3DViewer {

Widget::Widget(QWidget *parent) : QOpenGLWidget(parent) {}

Widget::~Widget() {}

void Widget::initializeGL() {
  QVector4D bg_color = controller_.get_bg_color_sets();
  glClearColor(bg_color.x(), bg_color.y(), bg_color.z(), bg_color.w());
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  initShaders();
}

void Widget::resizeGL(int w, int h) {
  projectionMatrix_.setToIdentity();
  if (controller_.get_projection_sets() == projType::Central) {
    float aspect = w / float(h);
    projectionMatrix_.perspective(45, aspect, 0.1f, 1000.0f);
  } else if (controller_.get_projection_sets() == projType::Parallel) {
    projectionMatrix_.ortho(-5, 5, -3, 3, -100, 100);
  }
}

void Widget::bindBuffersObject(qsizetype index_obj) {
  controller_.get_vertex_buffer_object(index_obj).bind();

  int offset = 0;
  int vertLoc = program_.attributeLocation("a_position");
  program_.enableAttributeArray(vertLoc);
  program_.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3,
                              sizeof(s21_3DViewer::VertexData));

  offset += sizeof(QVector3D);

  int texLoc = program_.attributeLocation("a_texcoord");
  program_.enableAttributeArray(texLoc);
  program_.setAttributeBuffer(texLoc, GL_FLOAT, offset, 2,
                              sizeof(s21_3DViewer::VertexData));

  offset += sizeof(QVector2D);

  int normLoc = program_.attributeLocation("a_normal");
  program_.enableAttributeArray(normLoc);
  program_.setAttributeBuffer(normLoc, GL_FLOAT, offset, 3,
                              sizeof(s21_3DViewer::VertexData));

  controller_.get_index_buffer_object(index_obj).bind();
}

void Widget::releaseBuffersObject(qsizetype index_obj) {
  controller_.get_vertex_buffer_object(index_obj).release();
  controller_.get_index_buffer_object(index_obj).release();
}

void Widget::paintGL() {
  /*---получаем цвет заднего фона из настроек и устанавливаем его---*/
  QVector4D bg_color = controller_.get_bg_color_sets();
  glClearColor(bg_color.x(), bg_color.y(), bg_color.z(), bg_color.w());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /*---------------------------------------------------------------*/
  /*---отрисовка происходит только в случае наличия модели(ей)---*/
  if (controller_.have_objects()) {
    program_.bind();
    program_.setUniformValue("u_projectionMatrix", projectionMatrix_);

    program_.setUniformValue("u_viewMatrix", controller_.get_view_matrix());

    program_.setUniformValue("u_shadding", controller_.getLightShade());

    program_.setUniformValue("u_lightPosition", controller_.getLightPosition());
    if (controller_.getLightStatus() == lightStatus::ON) {
      program_.setUniformValue("u_lightPower", controller_.getLightPower());
    } else {
      program_.setUniformValue("u_lightPower", 0.0f);
    }
    program_.setUniformValue("u_specularFactor",
                             controller_.getSpecularFactor());
    program_.setUniformValue("u_specularColor", controller_.getSpecularColor());
    program_.setUniformValue("u_ambientFactor", controller_.getAmbientFactor());
    program_.setUniformValue("u_lightColor", controller_.getLightColor());

    for (qsizetype index_obj = 0; index_obj < controller_.get_sum_objects();
         ++index_obj) {
      bindBuffersObject(index_obj);
      QMatrix4x4 model;
      model.setToIdentity();
      model.translate(5, 0);
      program_.setUniformValue("u_modelMatrix",
                               controller_.get_model_matrix_object(index_obj));

      /*-----если у объекта есть текстура подгружаем ее в шейдер-------*/
      if (controller_.get_texture_object() != nullptr) {
        controller_.get_texture_object()->bind(0);
      }
      program_.setUniformValue("u_texture", 0);
      /*---------------------------------------------------------------*/

      if (controller_.get_vert_type_sets() != vertType::None &&
          controller_.get_vert_size_sets() != 0) {
        glPointSize(controller_.get_vert_size_sets());  // устанавливаем размер
                                                        // точек из настроек
        if (controller_.get_vert_type_sets() == vertType::Square) {
          glDisable(GL_POINT_SMOOTH);
          glEnable(GL_POINT_SIZE);
        } else {
          glDisable(GL_POINT_SIZE);
          glEnable(GL_POINT_SMOOTH);
        }
        /*---получаем цвет точек из настроек и устанавливаем его---*/
        program_.setUniformValue("u_resultColor",
                                 controller_.get_vert_color_sets());
        /*---------------------------------------------------------------*/
        context()->functions()->glDrawElements(
            GL_POINTS, controller_.get_index_buffer_object(index_obj).size(),
            GL_UNSIGNED_INT, 0);
      }

      unsigned typeDrawing =
          controller_
              .get_draw_type_sets();  // получаем тип отрисовки из настроек
      if (typeDrawing == typeDraw::Triangles) {
        /*---получаем цвет поверхностей из настроек и устанавливаем его---*/
        program_.setUniformValue("u_resultColor",
                                 controller_.get_surfaces_color_sets());
        /*---------------------------------------------------------------*/
        context()->functions()->glDrawElements(
            typeDrawing, controller_.get_index_buffer_object(index_obj).size(),
            GL_UNSIGNED_INT, 0);
      } else if (typeDrawing >= typeDraw::Lines &&
                 typeDrawing <= typeDraw::Line_Strip) {
        glLineWidth(controller_.get_line_size_sets());  // устанавливаем размер
                                                        // линиий из настроек
        /*---получаем цвет линий из натсроек и устанавливаем его---*/
        program_.setUniformValue("u_resultColor",
                                 controller_.get_line_color_sets());
        /*---------------------------------------------------------------*/
        if (controller_.get_line_type_sets() == lineType::Dashed) {
          glEnable(GL_LINE_STIPPLE);
          glLineStipple(2, 0X00FF);
        } else {
          glDisable(GL_LINE_STIPPLE);
        }
        context()->functions()->glDrawElements(
            typeDrawing, controller_.get_index_buffer_object(index_obj).size(),
            GL_UNSIGNED_INT, 0);
      }

      releaseBuffersObject(index_obj);
      if (controller_.get_texture_object() != nullptr) {
        controller_.get_texture_object()->release();
      }
    }
    context()->functions()->glFlush();
    program_.release();
  }
}

void Widget::mousePressEvent(QMouseEvent *event) {
  if (controller_.have_objects()) {
    if (event->buttons() == Qt::LeftButton) {
      mousePosition_ = QVector2D(event->position());
    }
    event->accept();
  }
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
  if (controller_.have_objects()) {
    if (event->buttons() == Qt::LeftButton) {
      QVector2D diff = QVector2D(event->position()) - mousePosition_;
      mousePosition_ = QVector2D(event->position());

      float angle = diff.length() / 2.0;

      QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);

      controller_.rotate_camera(QQuaternion::fromAxisAndAngle(axis, angle));
      update();
    }
  }
}

void Widget::wheelEvent(QWheelEvent *event) {
  if (controller_.have_objects()) {
    if (event->angleDelta().y() > 0) {
      controller_.scale_camera(0.03);
    } else if (event->angleDelta().y() < 0) {
      controller_.scale_camera(-0.03);
    }
    update();
  }
}

void Widget::initShaders() {
  if (!program_.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                        ":/vertex_shader.vsh")) {
    close();
  }
  if (!program_.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                        ":/fragment_shader.fsh")) {
    close();
  }
  if (!program_.link()) {
    close();
  }
}
}  // namespace s21_3DViewer
