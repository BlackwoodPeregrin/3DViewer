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

  Object3D(const QVector<VertexData>& verData, const QVector<GLuint>& indexData, const InfoObject3D& infoObj)
    : Object3D()
  {
    m_vertBuffer.create();
    m_vertBuffer.bind();
    m_vertBuffer.allocate(verData.constData(), verData.size() * sizeof(VertexData));
    m_vertBuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexData.constData(), indexData.size() * sizeof(GLuint));
    m_indexBuffer.release();

    m_info = infoObj;  // устанавливаем информацию об объекте
  }

  ~Object3D()
  {
    free();
  }

  void xTranslate(float x)
  {
    m_xT = x;
  }

  void yTranslate(float y)
  {
    m_yT = y;
  }

  void zTranslate(float z)
  {
    m_zT = z;
  }

  void xRotate(float x)
  {
    m_xR = x;
  }

  void yRotate(float y)
  {
    m_yR = y;
  }

  void zRotate(float z)
  {
    m_zR = z;
  }

  void scale(float s)
  {
    m_scale = s;
  }

  QMatrix4x4 modelMatrix() const
  {
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.translate(m_xT, m_yT, m_zT);
    matrix.rotate(m_xR, m_yR, m_zR);
    matrix.scale(m_scale);
    return matrix;
  }

  QOpenGLBuffer& vertBuffer()
  {
    return m_vertBuffer;
  }

  QOpenGLBuffer& indexBuffer()
  {
    return m_indexBuffer;
  }

  const InfoObject3D& info() const
  {
    return m_info;
  }

  bool deleteTexture()
  {
    if (!m_texture || !m_texture->isCreated())
      return false;

    delete m_texture;
    m_texture = nullptr;
    m_info.deleteTexture();

    return true;
  }

  bool addTexture(const QString& pathTexture)
  {
    if (pathTexture.isEmpty())
      return false;

    deleteTexture();
    m_texture = new QOpenGLTexture(QImage(pathTexture).mirrored());
    m_info.setPathToTextureObj(pathTexture);

    return true;
  }

  QOpenGLTexture* texture()
  {
    return m_texture;
  }

  const QString& pathToTexture() const
  {
    return m_info.pathToTextureObj();
  }

  void setPathToTexture(const QString& p)
  {
    m_info.setPathToTextureObj(p);
  }

private:
  void free()
  {
    if (m_vertBuffer.isCreated())
      m_vertBuffer.destroy();

    if (m_indexBuffer.isCreated())
      m_indexBuffer.destroy();

    deleteTexture();
  }

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
