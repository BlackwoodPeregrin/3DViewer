#ifndef INFOOBJECT3D_H
#define INFOOBJECT3D_H

#include <QString>

/*-----Класс для хранения информации об объекте----*/

namespace s21_3DViewer
{
class InfoObject3D
{
public:
  InfoObject3D() = default;

  InfoObject3D(InfoObject3D const& other)
  {
    *this = other;
  }

  InfoObject3D(InfoObject3D const&&) = delete;

  ~InfoObject3D() = default;

  InfoObject3D& operator=(InfoObject3D const& other)
  {
    sumVertex_ = other.sumVertex_;
    sumEdge_ = other.sumEdge_;
    pathToObject_ = other.pathToObject_;
    pathToTextureObj_ = other.pathToTextureObj_;
  }

  InfoObject3D& operator=(InfoObject3D&&) = delete;

  void setSumVert(unsigned long sumVert)
  {
    sumVertex_ = sumVert;
  }

  void setSumFaces(unsigned long sumEdge)
  {
    sumEdge_ = sumEdge;
  }

  void setPathToObj(const QString& path)
  {
    pathToObject_ = path;
  }

  void setPathToTextureObj(const QString& path)
  {
    pathToTextureObj_ = path;
  }

  unsigned long sumVert() const
  {
    return sumVertex_;
  }

  unsigned long sumFaces() const
  {
    return sumEdge_;
  }

  const QString& pathToObj() const
  {
    return pathToObject_;
  }

  const QString& pathToTextureObj() const
  {
    return pathToTextureObj_;
  }

  void deleteTexture()
  {
    pathToTextureObj_.clear();
  }

private:
  unsigned long sumVertex_;
  unsigned long sumEdge_;
  QString pathToObject_;
  QString pathToTextureObj_;
};

}  // namespace s21_3DViewer

/*---------------------------------------------------*/

#endif  // INFOOBJECT3D_H
