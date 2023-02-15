#include "groupObject3D.h"

namespace s21_3DViewer
{
bool GroupObjects3D::isEmpty() const
{
  return m_objects.isEmpty();
}

unsigned GroupObjects3D::sumObjects() const
{
  return m_objects.length();
}

bool GroupObjects3D::addObject(const QString& filePath)
{
  InfoObject3D info;
  QVector<VertexData> vertexes;
  QVector<GLuint> indexes;

  if (!LoaderObj::loadObj(filePath, info, vertexes, indexes))
    return false;

  if (!m_objects.isEmpty())
    m_objects.pop_back();

  Object3D object(vertexes, indexes, info);
  m_objects.push_back(object);

  return true;
}

void GroupObjects3D::deleteAllObjects()
{
  m_objects.clear();
}

void GroupObjects3D::translateX_index(float x, unsigned indexObj)
{
  m_objects[indexObj].xTranslate(x);
}

void GroupObjects3D::translateY_index(float y, unsigned indexObj)
{
  m_objects[indexObj].yTranslate(y);
}

void GroupObjects3D::translateZ_index(float z, unsigned indexObj)
{
  m_objects[indexObj].zTranslate(z);
}

void GroupObjects3D::rotateX_index(float x, unsigned indexObj)
{
  m_objects[indexObj].xRotate(x);
}

void GroupObjects3D::rotateY_index(float y, unsigned indexObj)
{
  m_objects[indexObj].yRotate(y);
}

void GroupObjects3D::rotateZ_index(float z, unsigned indexObj)
{
  m_objects[indexObj].zRotate(z);
}

void GroupObjects3D::scale_index(float s, unsigned indexObj)
{
  m_objects[indexObj].scale(s);
}

QMatrix4x4 GroupObjects3D::modelMatrix_index(unsigned indexObj) const
{
  return m_objects[indexObj].modelMatrix();
}

QOpenGLBuffer& GroupObjects3D::vertexBuffer_index(unsigned indexObj)
{
  return m_objects[indexObj].vertBuffer();
}

QOpenGLBuffer& GroupObjects3D::indexBuffer_index(unsigned indexObj)
{
  return m_objects[indexObj].indexBuffer();
}

const InfoObject3D& GroupObjects3D::info_index(unsigned indexObj) const
{
  return m_objects[indexObj].info();
}

bool GroupObjects3D::deleteTextureFrom_index(unsigned indexObj)
{
  if (!m_objects[indexObj].deleteTexture())
    return false;

  m_objects[indexObj].setPathToTexture("");
  return true;
}

bool GroupObjects3D::addTexture_index(const QString& p, unsigned indexObj)
{
  if (!m_objects[indexObj].addTexture(p))
    return false;

  m_objects[indexObj].setPathToTexture(p);
  return true;
}

QOpenGLTexture* GroupObjects3D::texture_index(unsigned indexObj)
{
  return m_objects[indexObj].texture();
}

const QString& GroupObjects3D::pathToTexture_index(unsigned indexObj) const
{
  return m_objects[indexObj].pathToTexture();
}

}  // namespace s21_3DViewer
