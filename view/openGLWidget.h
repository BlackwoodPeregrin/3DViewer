#pragma once

#include <QDoubleSpinBox>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>
#include <QQuaternion>
#include <QWheelEvent>

#include "../controller/controller.h"

namespace s21_3DViewer {

class Widget : public QOpenGLWidget {
  Q_OBJECT

 public:
  explicit Widget(QWidget *parent = nullptr);
  ~Widget();
  void resizeGL(int w, int h);

 protected:
  void initializeGL();
  void paintGL();

  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void wheelEvent(QWheelEvent *event);
  void initShaders();

  void bindBuffersObject(qsizetype index_obj);
  void releaseBuffersObject(qsizetype index_obj);

 private:
  QMatrix4x4 projectionMatrix_;
  QOpenGLShaderProgram program_;
  QVector2D mousePosition_;
  Controller &controller_ = Controller::getInstance();
};
}  // namespace s21_3DViewer
