#include "openGLWidget.h"

s21_3DViewer::Widget::Widget(QWidget* parent) : QOpenGLWidget(parent)
{
}

void s21_3DViewer::Widget::resizeGL(int w, int h)
{
  projectionMatrix_.setToIdentity();

  switch (controller_.projection_sets())
  {
    case projType::Central: {
      float aspect = w / float(h);
      projectionMatrix_.perspective(45, aspect, 0.1f, 1000.0f);
      break;
    }

    case projType::Parallel: {
      projectionMatrix_.ortho(-5, 5, -3, 3, -100, 100);
      break;
    }

    default:
      break;
  }
}

void s21_3DViewer::Widget::initializeGL()
{
  QVector4D bg_color = controller_.bgColor_sets();
  glClearColor(bg_color.x(), bg_color.y(), bg_color.z(), bg_color.w());
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  initShaders();
}

void s21_3DViewer::Widget::paintGL()
{
  /*---получаем цвет заднего фона из настроек и устанавливаем его---*/

  QVector4D bg_color = controller_.bgColor_sets();
  glClearColor(bg_color.x(), bg_color.y(), bg_color.z(), bg_color.w());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  /*---отрисовка происходит только в случае наличия модели(ей)---*/

  if (!controller_.haveObjects())
    return;

  program_.bind();
  program_.setUniformValue("u_projectionMatrix", projectionMatrix_);
  program_.setUniformValue("u_viewMatrix", controller_.viewMatrixCamera());
  program_.setUniformValue("u_shadding", controller_.lightShade());
  program_.setUniformValue("u_lightPosition", controller_.lightPosition_sets());

  if (controller_.lightStatus_sets() == lightStatus::ON)
    program_.setUniformValue("u_lightPower", controller_.lightPower_sets());
  else
    program_.setUniformValue("u_lightPower", 0.0f);

  program_.setUniformValue("u_specularFactor", controller_.specularFactor_sets());
  program_.setUniformValue("u_ambientFactor", controller_.ambientFactor_sets());
  program_.setUniformValue("u_specularColor", controller_.specularColor());
  program_.setUniformValue("u_lightColor", controller_.lightColor_sets());

  for (int index_obj = 0; index_obj < controller_.sumObjects(); ++index_obj)
  {
    bindBuffersObject(index_obj);

    program_.setUniformValue("u_modelMatrix", controller_.modelMatrix_object(index_obj));

    /*-----если у объекта есть текстура подгружаем ее в шейдер-------*/
    if (controller_.texture_object())
      controller_.texture_object()->bind(0);

    program_.setUniformValue("u_texture", 0);

    if (controller_.vertType_sets() != vertType::None && controller_.vertSize_sets())
    {
      glPointSize(controller_.vertSize_sets());

      if (controller_.vertType_sets() == vertType::Square)
      {
        glDisable(GL_POINT_SMOOTH);
        glEnable(GL_POINT_SIZE);
      }
      else
      {
        glDisable(GL_POINT_SIZE);
        glEnable(GL_POINT_SMOOTH);
      }

      /*---получаем цвет точек из настроек и устанавливаем его---*/
      program_.setUniformValue("u_resultColor", controller_.vertColor_sets());

      context()->functions()->glDrawElements(GL_POINTS, controller_.indexBuffer_object(index_obj).size(),
                                             GL_UNSIGNED_INT, 0);
    }

    unsigned typeDrawing = controller_.drawType_sets();  // получаем тип отрисовки из настроек

    switch (typeDrawing)
    {
      case typeDraw::Lines:
      case typeDraw::Line_Loop:
      case typeDraw::Line_Strip: {
        glLineWidth(controller_.lineSize_sets());
        program_.setUniformValue("u_resultColor", controller_.lineColor_sets());

        if (controller_.lineType_sets() == lineType::Dashed)
        {
          glEnable(GL_LINE_STIPPLE);
          glLineStipple(2, 0X00FF);
        }
        else
        {
          glDisable(GL_LINE_STIPPLE);
        }

        context()->functions()->glDrawElements(typeDrawing, controller_.indexBuffer_object(index_obj).size(),
                                               GL_UNSIGNED_INT, 0);
        break;
      }

      case typeDraw::Triangles: {
        program_.setUniformValue("u_resultColor", controller_.surfacesColor_sets());
        context()->functions()->glDrawElements(typeDrawing, controller_.indexBuffer_object(index_obj).size(),
                                               GL_UNSIGNED_INT, 0);
        break;
      }

      default:
        break;
    }

    releaseBuffersObject(index_obj);

    if (controller_.texture_object())
      controller_.texture_object()->release();
  }

  context()->functions()->glFlush();
  program_.release();
}

void s21_3DViewer::Widget::mousePressEvent(QMouseEvent* event)
{
  if (!controller_.haveObjects())
    return;

  if (event->buttons() == Qt::LeftButton)
    mousePosition_ = QVector2D(event->position());

  event->accept();
}

void s21_3DViewer::Widget::mouseMoveEvent(QMouseEvent* event)
{
  if (!controller_.haveObjects())
    return;

  if (event->buttons() == Qt::LeftButton)
  {
    QVector2D diff = QVector2D(event->position()) - mousePosition_;
    mousePosition_ = QVector2D(event->position());

    float angle = diff.length() / 2.0;

    QVector3D axis = QVector3D(diff.y(), diff.x(), 0.0);

    controller_.rotateCamera(QQuaternion::fromAxisAndAngle(axis, angle));

    update();
  }
}

void s21_3DViewer::Widget::wheelEvent(QWheelEvent* event)
{
  if (!controller_.haveObjects())
    return;

  if (event->angleDelta().y() > 0)
    controller_.scaleCamera(0.03);
  else
    controller_.scaleCamera(-0.03);

  update();
}

void s21_3DViewer::Widget::initShaders()
{
  if (!program_.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vertex_shader.vsh"))
    close();

  if (!program_.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.fsh"))
    close();

  if (!program_.link())
    close();
}

void s21_3DViewer::Widget::bindBuffersObject(qsizetype index_obj)
{
  controller_.vertexBuffer_object(index_obj).bind();

  int offset = 0;
  int vertLoc = program_.attributeLocation("a_position");
  program_.enableAttributeArray(vertLoc);
  program_.setAttributeBuffer(vertLoc, GL_FLOAT, offset, 3, sizeof(s21_3DViewer::VertexData));

  offset += sizeof(QVector3D);

  int texLoc = program_.attributeLocation("a_texcoord");
  program_.enableAttributeArray(texLoc);
  program_.setAttributeBuffer(texLoc, GL_FLOAT, offset, 2, sizeof(s21_3DViewer::VertexData));

  offset += sizeof(QVector2D);

  int normLoc = program_.attributeLocation("a_normal");
  program_.enableAttributeArray(normLoc);
  program_.setAttributeBuffer(normLoc, GL_FLOAT, offset, 3, sizeof(s21_3DViewer::VertexData));

  controller_.indexBuffer_object(index_obj).bind();
}

void s21_3DViewer::Widget::releaseBuffersObject(qsizetype index_obj)
{
  controller_.vertexBuffer_object(index_obj).release();
  controller_.indexBuffer_object(index_obj).release();
}

#include "openGLWidget.h"
