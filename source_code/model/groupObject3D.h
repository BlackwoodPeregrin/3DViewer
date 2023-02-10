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

  /*----translate----*/
  void translateX_object(float x, unsigned indexObj = 0)
  {
    m_objects[indexObj].xTranslate(x);
  }

  void translateY_object(float y, unsigned indexObj = 0)
  {
    m_objects[indexObj].yTranslate(y);
  }

  void translateZ_object(float z, unsigned indexObj = 0)
  {
    m_objects[indexObj].zTranslate(z);
  }

  /*----rotate----*/
  void rotateX_object(float x, unsigned indexObj = 0)
  {
    m_objects[indexObj].xRotate(x);
  }

  void rotateY_object(float y, unsigned indexObj = 0)
  {
    m_objects[indexObj].yRotate(y);
  }

  void rotateZ_object(float z, unsigned indexObj = 0)
  {
    m_objects[indexObj].zRotate(z);
  }

  /*----scale----*/
  void scale_object(float s, unsigned indexObj = 0)
  {
    m_objects[indexObj].scale(s);
  }

  /*----model Matrix----*/
  QMatrix4x4 modelMatrix_object(unsigned indexObj = 0)
  {
    return m_objects[indexObj].modelMatrix();
  }

  /*----vertext buffer----*/
  const QOpenGLBuffer& vertexBuffer_object(unsigned indexObj = 0) const
  {
    return m_objects[indexObj].vertBuffer();
  }

  /*----index buffer----*/
  const QOpenGLBuffer& indexBuffer_object(unsigned indexObj = 0) const
  {
    return m_objects[indexObj].indexBuffer();
  }

  /*----info about object----*/
  const InfoObject3D& info_object(unsigned indexObj = 0)
  {
    return m_objects[indexObj].info();
  }

  /*----texture object----*/
  const QOpenGLTexture* texture_object(unsigned indexObj = 0)
  {
    return m_objects[indexObj].texture();
  }

  bool addTextureTo_object(const QString& path, unsigned indexObj = 0)
  {
    return m_objects[indexObj].addTexture(path);
  }

  bool deleteTextureFrom_object(unsigned indexObj = 0)
  {
    return m_objects[indexObj].deleteTexture();
  }

private:
  QVector<Object3D> m_objects;
};

}  // namespace s21_3DViewer

#endif  // GROUPOBJECT3D_H
