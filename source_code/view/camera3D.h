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
  Camera3D()
  {
    load_camera();
  }

  Camera3D(const Camera3D& other)
  {
    *this = other;
  }

  void operator=(const Camera3D& other)
  {
    viewMatrix_ = other.viewMatrix_;
    m_rotate = other.m_rotate;
    m_translate = other.m_translate;
    m_scale = other.m_scale;
  }

  void translate(const QVector3D& t)
  {
    m_translate += t;
  }

  void rotate(const QQuaternion& r)
  {
    m_rotate = r * m_rotate;
  }

  void scale(float s)
  {
    m_scale += s;
  }

  QMatrix4x4 viewMatrix()
  {
    QMatrix4x4 viewMatrix_;
    viewMatrix_.setToIdentity();
    viewMatrix_.translate(m_translate);
    viewMatrix_.rotate(m_rotate);
    viewMatrix_.scale(m_scale);
    return viewMatrix_;
  }

  void setDefaultCamera()
  {
    m_rotate = QQuaternion();
    m_translate = QVector3D(0.0, 0.0, -5.0);
    m_scale = 1.0;
  }

  void load_camera()
  {
    setDefaultCamera();

    QString pathToConfig = QCoreApplication::applicationDirPath() + "/settings/";

    if (!QDir(pathToConfig).exists())
      return;

    QString filename = pathToConfig + "CameraSettings.conf";

    std::fstream src(filename.toStdString(), std::fstream::in);

    if (!src.is_open())
      return;

    setlocale(LC_ALL, "en_US.UTF-8");

    while (src)
    {
      int type;
      float val;

      src >> type >> val;

      switch (type)
      {
        case kScalar:
          m_rotate.setScalar(val);
          break;
        case kRotateX:
          m_rotate.setX(val);
          break;
        case kRotateY:
          m_rotate.setY(val);
          break;
        case kRotateZ:
          m_rotate.setZ(val);
          break;
        case kTransalteX:
          m_translate.setX(val);
          break;
        case kTransalteY:
          m_translate.setY(val);
          break;
        case kTransalteZ:
          m_translate.setZ(val);
          break;
        case kScale:
          m_scale = val;
          break;
        default:
          break;
      }

      if (m_scale == 0.0)
        m_scale = 1.0;
    }
  }

  void save_camera()
  {
    QString pathToConfig = QCoreApplication::applicationDirPath() + "/settings/";

    if (!QDir(pathToConfig).exists())
      QDir().mkdir(pathToConfig);

    QString filename = pathToConfig + "CameraSettings.conf";
    std::fstream tgt(filename.toStdString(), std::fstream::out | std::fstream::trunc);

    if (!tgt.is_open())
      return;

    setlocale(LC_ALL, "en_US.UTF-8");

    tgt << kScalar << " " << m_rotate.scalar() << std::endl;
    tgt << kRotateX << " " << m_rotate.vector().x() << std::endl;
    tgt << kRotateY << " " << m_rotate.vector().y() << std::endl;
    tgt << kRotateZ << " " << m_rotate.vector().z() << std::endl;
    tgt << kTransalteX << " " << m_translate.x() << std::endl;
    tgt << kTransalteY << " " << m_translate.y() << std::endl;
    tgt << kTransalteZ << " " << m_translate.z() << std::endl;
    tgt << kScale << " " << m_scale << std::endl;
  }

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
