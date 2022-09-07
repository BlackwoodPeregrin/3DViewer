#include "object3D.h"

#include <QFile>
#include <QMatrix4x4>
#include <QRegularExpression>
#include <QStringList>
#include <QTextStream>

namespace s21_3DViewer {

Object3D::Object3D()
    : m_texture(nullptr),
      vertBuffer_(QOpenGLBuffer::VertexBuffer),
      indexBuffer_(QOpenGLBuffer::IndexBuffer) {
  xRotate_ = 0.0;
  yRotate_ = 0.0;
  zRotate_ = 0.0;
  xTranslate_ = 0.0;
  yTranslate_ = 0.0;
  zTranslate_ = 0.0;
  scale_ = 1.0;
}

Object3D::Object3D(const QVector<VertexData> &verData,
                   const QVector<GLuint> &indexData,
                   const Object3D::InfoObject3D &infoObj)
    : m_texture(nullptr),
      vertBuffer_(QOpenGLBuffer::VertexBuffer),
      indexBuffer_(QOpenGLBuffer::IndexBuffer) {
  init(verData, indexData, infoObj);
  xRotate_ = 0.0;
  yRotate_ = 0.0;
  zRotate_ = 0.0;
  xTranslate_ = 0.0;
  yTranslate_ = 0.0;
  zTranslate_ = 0.0;
  scale_ = 1.0;
}

Object3D::~Object3D() { free(); }

void Object3D::free() {
  if (vertBuffer_.isCreated()) {
    vertBuffer_.destroy();
  }
  if (indexBuffer_.isCreated()) {
    indexBuffer_.destroy();
  }
  delete_texture();
}

void Object3D::init(const QVector<VertexData> &verData,
                    const QVector<GLuint> &indexData,
                    const Object3D::InfoObject3D &infoObj) {
  free();

  vertBuffer_.create();
  vertBuffer_.bind();
  vertBuffer_.allocate(verData.constData(),
                       verData.size() * sizeof(VertexData));
  vertBuffer_.release();

  indexBuffer_.create();
  indexBuffer_.bind();
  indexBuffer_.allocate(indexData.constData(),
                        indexData.size() * sizeof(GLuint));
  indexBuffer_.release();

  info_ = infoObj;  // устанавливаем информацию об объекте
}

const S21Matrix Object3D::getModelMatrix() {
  S21Matrix modelMatrix(4, 4);
  modelMatrix.setToIdentity();
  modelMatrix.translateX(xTranslate_);
  modelMatrix.translateY(yTranslate_);
  modelMatrix.translateZ(zTranslate_);
  modelMatrix.rotateX(xRotate_);
  modelMatrix.rotateY(yRotate_);
  modelMatrix.rotateZ(zRotate_);
  modelMatrix.scale(scale_);
  return modelMatrix;
}

void Object3D::delete_texture() {
  if (m_texture != nullptr && m_texture->isCreated()) {
    delete m_texture;
    m_texture = nullptr;
    info_.deleteTexture();
  }
}

void Object3D::add_texture(const QString &pathTexture) {
  delete_texture();
  if (!pathTexture.isEmpty()) {
    m_texture = new QOpenGLTexture(QImage(pathTexture).mirrored());
    info_.setPathToTextureObj(pathTexture);
  }
}

// parser obj. files

const std::pair<QVector<VertexData>, QVector<GLuint>> LoaderObj::loadObj(
    const QString &filePath, Object3D::InfoObject3D *info) {
  QFile objFile(filePath);

  QVector<VertexData> vertexes;
  QVector<GLuint> indexes;

  if (objFile.exists()) {
    objFile.open(QIODevice::ReadOnly);
    QTextStream input(&objFile);
    bool okCheck[3] = {true, true, true};
    bool Error = false;
    unsigned long facesObject = 0;
    while (!input.atEnd()) {
      QString str = input.readLine();
      if (str.isEmpty()) {
        continue;
      }
      QStringList list =
          str.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
      if (list[0] == "v") {
        Error = readCoords(list, okCheck);
      } else if (list[0] == "vt") {
        Error = readTexCoords(list, okCheck);
      } else if (list[0] == "vn") {
        Error = readNormals(list, okCheck);
      } else if (list[0] == "f") {
        Error = readFaces(list, &vertexes, &indexes, okCheck);
        ++facesObject;
      }
      if (Error == true) {
        vertexes.clear();
        indexes.clear();
        break;
      }
    }
    objFile.close();
    if (info != nullptr) {
      info->setSumVert(coords.length());
      info->setSumFaces(facesObject);
      info->setPathToObj(filePath);
    }
    free_vectors();
  }
  return {vertexes, indexes};
}

void LoaderObj::free_vectors() {
  coords.clear();
  texCoords.clear();
  normals.clear();
}

bool LoaderObj::readCoords(const QStringList &list, bool *okCheck) {
  if (list.length() == 4) {
    coords.append(QVector3D(list[1].toFloat(&okCheck[0]),
                            list[2].toFloat(&okCheck[1]),
                            list[3].toFloat(&okCheck[2])));
    return !(okCheck[0] && okCheck[1] && okCheck[2]);
  }
  return true;
}

bool LoaderObj::readTexCoords(const QStringList &list, bool *okCheck) {
  if (list.length() == 3) {
    texCoords.append(
        QVector2D(list[1].toFloat(&okCheck[0]), list[2].toFloat(&okCheck[1])));
    return !(okCheck[0] && okCheck[1]);
  }
  return true;
}

bool LoaderObj::readNormals(const QStringList &list, bool *okCheck) {
  if (list.length() == 4) {
    normals.append(QVector3D(list[1].toFloat(&okCheck[0]),
                             list[2].toFloat(&okCheck[1]),
                             list[3].toFloat(&okCheck[2])));
    return !(okCheck[0] && okCheck[1] && okCheck[2]);
  }
  return true;
}

bool LoaderObj::readFaces(const QStringList &list,
                          QVector<VertexData> *vertexes,
                          QVector<GLuint> *indexes, bool *okCheck) {
  bool res = false;
  QStringList vert;
  qsizetype first_of_many;
  unsigned count_many{};
  for (qsizetype i = 1; i < list.length(); ++i) {
    if (list[i].contains("/") == false) {
      qsizetype vertxIndex = list[i].toLong(&okCheck[0]) - 1;
      if (vertxIndex < 0) vertxIndex += coords.length() + 1;
      if (count_many == 0) first_of_many = vertxIndex;
      count_many++;
      if (vertxIndex < coords.length()) {
        vertexes->append(VertexData(coords[vertxIndex], QVector2D(0.0, 0.0),
                                    QVector3D(0.0, 0.0, 0.0)));
        indexes->append(indexes->size());
      } else {
        res = true;
        break;
      }
      if (count_many > 2 && i < list.length() - 1) {
        vertexes->append(VertexData(coords[first_of_many], QVector2D(0.0, 0.0),
                                    QVector3D(0.0, 0.0, 0.0)));
        indexes->append(indexes->size());
        vertexes->append(VertexData(coords[vertxIndex], QVector2D(0.0, 0.0),
                                    QVector3D(0.0, 0.0, 0.0)));
        indexes->append(indexes->size());
      }
    } else {
      if (list[i].contains("//") == true) {
        vert = list[i].split("//");
        if (vert.length() == 2) {
          qsizetype vertxIndex = vert[0].toLong(&okCheck[0]) - 1;
          qsizetype normalIndex = vert[1].toLong(&okCheck[2]) - 1;
          if (vertxIndex < coords.length() && normalIndex < normals.length()) {
            vertexes->append(VertexData(coords[vertxIndex], QVector2D(0.0, 0.0),
                                        normals[normalIndex]));
            indexes->append(indexes->size());
          } else {
            res = true;
            break;
          }
        } else {
          res = true;
          break;
        }
      } else {
        vert = list[i].split("/");
        if (vert.length() == 2) {
          qsizetype vertxIndex = vert[0].toLong(&okCheck[0]) - 1;
          qsizetype texIndex = vert[1].toLong(&okCheck[1]) - 1;
          if (vertxIndex < coords.length() && texIndex < texCoords.length()) {
            vertexes->append(VertexData(coords[vertxIndex], texCoords[texIndex],
                                        QVector3D(0.0, 0.0, 0.0)));
            indexes->append(indexes->size());
          } else {
            res = true;
            break;
          }
        } else if (vert.length() == 3) {
          qsizetype vertxIndex = vert[0].toLong(&okCheck[0]) - 1;
          qsizetype texIndex = vert[1].toLong(&okCheck[1]) - 1;
          qsizetype normalIndex = vert[2].toLong(&okCheck[2]) - 1;
          if (vertxIndex < coords.length() && texIndex < texCoords.length() &&
              normalIndex < normals.length()) {
            vertexes->append(VertexData(coords[vertxIndex], texCoords[texIndex],
                                        normals[normalIndex]));
            indexes->append(indexes->size());
          } else {
            res = true;
            break;
          }
        } else {
          res = true;
          break;
        }
      }
    }
  }
  return res;
}

}  // namespace s21_3DViewer
