#include "object3D.h"

namespace s21_3DViewer
{
Object3D::Object3D(const QVector<VertexData>& verData, const QVector<GLuint>& indexData, const InfoObject3D& infoObj)
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

Object3D::~Object3D()
{
  free();
}

void Object3D::xTranslate(float x)
{
  m_xT = x;
}

void Object3D::yTranslate(float y)
{
  m_yT = y;
}

void Object3D::zTranslate(float z)
{
  m_zT = z;
}

void Object3D::xRotate(float x)
{
  m_xR = x;
}

void Object3D::yRotate(float y)
{
  m_yR = y;
}

void Object3D::zRotate(float z)
{
  m_zR = z;
}

void Object3D::scale(float s)
{
  m_scale = s;
}

QMatrix4x4 Object3D::modelMatrix() const
{
  QMatrix4x4 matrix;
  matrix.setToIdentity();
  matrix.translate(m_xT, m_yT, m_zT);
  matrix.rotate(m_xR, m_yR, m_zR);
  matrix.scale(m_scale);
  return matrix;
}

QOpenGLBuffer& Object3D::vertBuffer()
{
  return m_vertBuffer;
}

QOpenGLBuffer& Object3D::indexBuffer()
{
  return m_indexBuffer;
}

const InfoObject3D& Object3D::info() const
{
  return m_info;
}

bool Object3D::deleteTexture()
{
  if (!m_texture || !m_texture->isCreated())
    return false;

  delete m_texture;
  m_texture = nullptr;
  m_info.deleteTexture();

  return true;
}

bool Object3D::addTexture(const QString& pathTexture)
{
  if (pathTexture.isEmpty())
    return false;

  deleteTexture();
  m_texture = new QOpenGLTexture(QImage(pathTexture).mirrored());
  m_info.setPathToTextureObj(pathTexture);

  return true;
}

QOpenGLTexture* Object3D::texture()
{
  return m_texture;
}

const QString& Object3D::pathToTexture() const
{
  return m_info.pathToTextureObj();
}

void Object3D::setPathToTexture(const QString& p)
{
  m_info.setPathToTextureObj(p);
}

void Object3D::free()
{
  if (m_vertBuffer.isCreated())
    m_vertBuffer.destroy();

  if (m_indexBuffer.isCreated())
    m_indexBuffer.destroy();

  deleteTexture();
}

}  // namespace s21_3DViewer
