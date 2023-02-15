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

  bool isEmpty() const;

  unsigned sumObjects() const;

  bool addObject(const QString& filePath);
  void deleteAllObjects();

  /*----translate----*/
  void translateX_index(float x, unsigned indexObj = 0);
  void translateY_index(float y, unsigned indexObj = 0);
  void translateZ_index(float z, unsigned indexObj = 0);

  /*----rotate----*/
  void rotateX_index(float x, unsigned indexObj = 0);
  void rotateY_index(float y, unsigned indexObj = 0);
  void rotateZ_index(float z, unsigned indexObj = 0);

  /*----scale----*/
  void scale_index(float s, unsigned indexObj = 0);

  /*----model Matrix----*/
  QMatrix4x4 modelMatrix_index(unsigned indexObj = 0) const;

  /*----vertext buffer----*/
  QOpenGLBuffer& vertexBuffer_index(unsigned indexObj = 0);

  /*----index buffer----*/
  QOpenGLBuffer& indexBuffer_index(unsigned indexObj = 0);

  /*----info about object----*/
  const InfoObject3D& info_index(unsigned indexObj = 0) const;

  /*----texture object----*/

  bool deleteTextureFrom_index(unsigned indexObj = 0);
  bool addTexture_index(const QString& p, unsigned indexObj = 0);
  QOpenGLTexture* texture_index(unsigned indexObj = 0);
  const QString& pathToTexture_index(unsigned indexObj = 0) const;

private:
  QVector<Object3D> m_objects;
};

}  // namespace s21_3DViewer

#endif  // GROUPOBJECT3D_H
