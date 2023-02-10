#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <QVector2D>
#include <QVector3D>

namespace s21_3DViewer
{
struct VertexData
{
  VertexData(QVector3D p, QVector2D t, QVector3D n) : position(p), textCoord(t), normal(n)
  {
  }

  VertexData(VertexData const& other)
  {
    *this = other;
  }

  VertexData(VertexData&& other)
  {
    *this = std::move(other);
  }

  VertexData& operator=(VertexData const& other)
  {
    position = other.position;
    textCoord = other.textCoord;
    normal = other.normal;
  }

  VertexData& operator=(VertexData&& other)
  {
    position = std::move(other.position);
    textCoord = std::move(other.textCoord);
    normal = std::move(other.normal);
  }

private:
  QVector3D position;
  QVector2D textCoord;
  QVector3D normal;
};

}  // namespace s21_3DViewer

#endif  // VERTEXDATA_H
