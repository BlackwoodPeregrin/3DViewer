#ifndef GROUPOBJECT3D_H
#define GROUPOBJECT3D_H

#include "object3D.h"
#include "infoObject3D.h"
#include "loaderObjFile.h"

namespace s21_3DViewer
{
class GroupObjects3D
{
public:
  GroupObjects3D() = default;
  ~GroupObjects3D() = default;

  bool isEmpty() const
  {
    return m_objects.isEmpty();
  }

  unsigned sumObjects() const
  {
    return m_objects.length();
  }

  bool addObject(const QString& filePath)
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

  void deleteAllObjects()
  {
    m_objects.clear();
  }

  /*----translate----*/
  void translateX_index(float x, unsigned indexObj = 0)
  {
    m_objects[indexObj].xTranslate(x);
  }

  void translateY_index(float y, unsigned indexObj = 0)
  {
    m_objects[indexObj].yTranslate(y);
  }

  void translateZ_index(float z, unsigned indexObj = 0)
  {
    m_objects[indexObj].zTranslate(z);
  }

  /*----rotate----*/
  void rotateX_index(float x, unsigned indexObj = 0)
  {
    m_objects[indexObj].xRotate(x);
  }

  void rotateY_index(float y, unsigned indexObj = 0)
  {
    m_objects[indexObj].yRotate(y);
  }

  void rotateZ_index(float z, unsigned indexObj = 0)
  {
    m_objects[indexObj].zRotate(z);
  }

  /*----scale----*/
  void scale_index(float s, unsigned indexObj = 0)
  {
    m_objects[indexObj].scale(s);
  }

  /*----model Matrix----*/
  QMatrix4x4 modelMatrix_index(unsigned indexObj = 0) const
  {
    return m_objects[indexObj].modelMatrix();
  }

  /*----vertext buffer----*/
  QOpenGLBuffer& vertexBuffer_index(unsigned indexObj = 0)
  {
    return m_objects[indexObj].vertBuffer();
  }

  /*----index buffer----*/
  QOpenGLBuffer& indexBuffer_index(unsigned indexObj = 0)
  {
    return m_objects[indexObj].indexBuffer();
  }

  /*----info about object----*/
  const InfoObject3D& info_index(unsigned indexObj = 0) const
  {
    return m_objects[indexObj].info();
  }

  /*----texture object----*/

  bool deleteTextureFrom_index(unsigned indexObj = 0)
  {
    if (!m_objects[indexObj].deleteTexture())
      return false;

    m_objects[indexObj].setPathToTexture("");
    return true;
  }

  bool addTexture_index(const QString& p, unsigned indexObj = 0)
  {
    if (!m_objects[indexObj].addTexture(p))
      return false;

    m_objects[indexObj].setPathToTexture(p);
    return true;
  }

  QOpenGLTexture* texture_index(unsigned indexObj = 0)
  {
    return m_objects[indexObj].texture();
  }

  const QString& pathToTexture_index(unsigned indexObj = 0) const
  {
    return m_objects[indexObj].pathToTexture();
  }

private:
  QVector<Object3D> m_objects;
};

}  // namespace s21_3DViewer

#endif  // GROUPOBJECT3D_H
