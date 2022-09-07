#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QQuaternion>
#include <QVector3D>
#include <fstream>

namespace s21_3DViewer {

class Camera3D {
 public:
  Camera3D();
  Camera3D(const Camera3D &other);
  void operator=(const Camera3D &other);

  void translate(const QVector3D &t);
  void rotate(const QQuaternion &r);
  void scale(const float &s);

  const QMatrix4x4 &getViewMatrix();

  void set_default_camera();

  void load_camera();

  void save_camera();

 private:
  QMatrix4x4 viewMatrix_;
  QQuaternion rotate_;
  QVector3D translate_;
  float scale_;
};
}  // namespace s21_3DViewer
