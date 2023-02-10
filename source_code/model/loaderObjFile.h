#ifndef LOADEROBJFILE_H
#define LOADEROBJFILE_H

#include <gltypes.h>
#include <QFile>
#include <QVector>
#include <QRegularExpression>

#include "vertexData.h"
#include "infoObject3D.h"

/*---------------Парсер obj files--------------------*/

namespace s21_3DViewer
{
class LoaderObj
{
public:
  LoaderObj() = default;

  static bool loadObj(QString const& filePath, InfoObject3D& info, QVector<VertexData>& vertexes,
                      QVector<GLuint>& indexes)
  {
    QFile objFile(filePath);

    if (!objFile.exists() || !objFile.open(QIODevice::ReadOnly))
    {
      return false;
    }

    QTextStream input(&objFile);

    unsigned long facesObject = 0;

    QVector<QVector3D> vertCoord{};
    QVector<QVector2D> texCoord{};
    QVector<QVector3D> normlCoord{};

    while (!input.atEnd())
    {
      QString str = input.readLine();

      if (str.isEmpty())
        continue;

      QStringList list = str.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

      if (list[0] == "v")
      {
        readCoords(list, vertCoord);
        continue;
      }

      if (list[0] == "vt")
      {
        readTexCoords(list, texCoord);
        continue;
      }

      if (list[0] == "vn")
      {
        readNormals(list, normlCoord);
        continue;
      }

      if (list[0] == "f")
      {
        readFaces(list, vertCoord, texCoord, normlCoord, vertexes, indexes);
        ++facesObject;
        continue;
      }

      vertexes.clear();
      indexes.clear();

      objFile.close();
      return false;
    }

    objFile.close();

    info.setSumVert(vertCoord.length());
    info.setSumFaces(facesObject);
    info.setPathToObj(filePath);

    return true;
  }

private:
  static void readCoords(const QStringList& list, QVector<QVector3D>& vertCoord)
  {
    if (list.size() < 4)
      return;

    vertCoord.push_back(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
  }

  static void readTexCoords(const QStringList& list, QVector<QVector2D>& texCoord)
  {
    if (list.size() < 3)
      return;

    texCoord.push_back(QVector2D(list[1].toFloat(), list[2].toFloat()));
  }

  static void readNormals(const QStringList& list, QVector<QVector3D>& normlCoord)
  {
    if (list.size() < 4)
      return;

    normlCoord.push_back(QVector3D(list[1].toFloat(), list[2].toFloat(), list[3].toFloat()));
  }

  static void readFaces(QStringList const& list, QVector<QVector3D> const& vertCoord,
                        QVector<QVector2D> const& texCoord, QVector<QVector3D> const& normlCoord,
                        QVector<VertexData>& vertexes, QVector<GLuint>& indexes)
  {
    qsizetype first_of_many{};

    unsigned count_many{};

    for (qsizetype i = 1; i < list.length(); ++i)
    {
      if (list[i].contains("//"))
      {
        QStringList stringList = list[i].split("//");

        if (stringList.length() != 2)
          return;

        qsizetype vertIndex = stringList[0].toLong() - 1;
        qsizetype normlIndex = stringList[1].toLong() - 1;

        if (vertIndex >= vertCoord.length() || normlIndex >= normlCoord.length())
          return;

        vertexes.append(VertexData(vertCoord[vertIndex], QVector2D(0.0, 0.0), normlCoord[normlIndex]));
        indexes.append(indexes.size());
        continue;
      }

      if (list[i].contains("/"))
      {
        QStringList stringList = list[i].split("/");

        switch (stringList.length())
        {
          case 2: {
            qsizetype vertIndex = stringList[0].toLong() - 1;
            qsizetype texIndex = stringList[1].toLong() - 1;

            if (vertIndex >= vertCoord.length() || texIndex >= texCoord.length())
              return;

            vertexes.append(VertexData(vertCoord[vertIndex], texCoord[texIndex], QVector3D(0.0, 0.0, 0.0)));
            indexes.append(indexes.size());
            break;
          }

          case 3: {
            qsizetype vertIndex = stringList[0].toLong() - 1;
            qsizetype texIndex = stringList[1].toLong() - 1;
            qsizetype normlIndex = stringList[2].toLong() - 1;

            if (vertIndex >= vertCoord.length() || texIndex >= texCoord.length() || normlIndex >= normlCoord.length())
            {
              return;
            }

            vertexes.append(VertexData(vertCoord[vertIndex], texCoord[texIndex], normlCoord[normlIndex]));
            indexes.append(indexes.size());
            break;
          }

          default:
            return;
        }

        continue;
      }

      qsizetype vertxIndex = list[i].toLong() - 1;

      if (vertxIndex >= vertCoord.length())
        return;

      vertexes.append(VertexData(vertCoord[vertxIndex], QVector2D(0.0, 0.0), QVector3D(0.0, 0.0, 0.0)));
      indexes.append(indexes.size());
    }
  }
};

}  // namespace s21_3DViewer

/*---------------------------------------------------*/

#endif  // LOADEROBJFILE_H
