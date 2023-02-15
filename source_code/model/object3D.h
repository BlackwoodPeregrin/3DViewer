#pragma once

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QString>
#include <QVector>

#include "infoObject3D.h"
#include "vertexData.h"

namespace s21_3DViewer
{
class Object3D
{
public:
  Object3D() = default;
  Object3D(const QVector<VertexData>& verData, const QVector<GLuint>& indexData, const InfoObject3D& infoObj);

  ~Object3D();

  void xTranslate(float x);
  void yTranslate(float y);
  void zTranslate(float z);
  void xRotate(float x);
  void yRotate(float y);
  void zRotate(float z);
  void scale(float s);

  QMatrix4x4 modelMatrix() const;

  QOpenGLBuffer& vertBuffer();
  QOpenGLBuffer& indexBuffer();

  const InfoObject3D& info() const;

  bool deleteTexture();
  bool addTexture(const QString& pathTexture);
  QOpenGLTexture* texture();
  const QString& pathToTexture() const;
  void setPathToTexture(const QString& p);

private:
  void free();

  float m_xR{ 0 };
  float m_yR{ 0.0 };
  float m_zR{ 0.0 };

  float m_xT{ 0.0 };
  float m_yT{ 0.0 };
  float m_zT{ 0.0 };

  float m_scale{ 1.0 };

  QOpenGLTexture* m_texture{ nullptr };

  QOpenGLBuffer m_vertBuffer{ QOpenGLBuffer::VertexBuffer };
  QOpenGLBuffer m_indexBuffer{ QOpenGLBuffer::IndexBuffer };

  InfoObject3D m_info{};
};

}  // namespace s21_3DViewer
