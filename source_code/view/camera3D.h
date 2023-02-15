#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QQuaternion>
#include <QVector3D>
#include <fstream>

namespace s21_3DViewer
{
class Camera3D
{
public:
  Camera3D();
  Camera3D(const Camera3D& other);

  void operator=(const Camera3D& other);

  void translate(const QVector3D& t);
  void rotate(const QQuaternion& r);
  void scale(float s);

  QMatrix4x4 viewMatrix() const;

  void setDefaultCamera();

  void load_camera();
  void save_camera();

private:
  enum Type
  {
    kScalar,
    kRotateX,
    kRotateY,
    kRotateZ,
    kTransalteX,
    kTransalteY,
    kTransalteZ,
    kScale
  };

  QQuaternion m_rotate;
  QVector3D m_translate;
  float m_scale;
};
}  // namespace s21_3DViewer
