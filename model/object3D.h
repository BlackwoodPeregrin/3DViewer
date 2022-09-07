#pragma once

#include <QMatrix4x4>
#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QQuaternion>
#include <QString>
#include <QVector2D>
#include <QVector3D>
#include <QVector>

#include "s21_matrix_oop.h"
#include "settings.h"

namespace s21_3DViewer {

struct VertexData {
  VertexData() {}
  VertexData(QVector3D p, QVector2D t, QVector3D n)
      : position(p), textCoord(t), normal(n) {}

 private:
  QVector3D position;
  QVector2D textCoord;
  QVector3D normal;
};

class Object3D {
  /*-----Структура для хранения информации об объекте----*/
 public:
  struct InfoObject3D {
    InfoObject3D() {}

    void setSumVert(unsigned const long &sumVert) { sumVertex_ = sumVert; }
    const unsigned long &getSumVert() { return sumVertex_; }

    void setSumFaces(unsigned const long &sumEdge) { sumEdge_ = sumEdge; }
    const unsigned long &getSumFaces() { return sumEdge_; }

    void setPathToObj(const QString &path) { pathToObject_ = path; }
    const QString &getPathToObj() { return pathToObject_; }

    void setPathToTextureObj(const QString &path) { pathToTextureObj_ = path; }
    const QString &getPathToTextureObj() { return pathToTextureObj_; }
    void deleteTexture() { pathToTextureObj_.clear(); }

   private:
    unsigned long sumVertex_;
    unsigned long sumEdge_;
    QString pathToObject_;
    QString pathToTextureObj_;
  };
  InfoObject3D info_;
  /*---------------------------------------------------*/

 public:
  Object3D();
  Object3D(const Object3D &other);
  Object3D(const QVector<VertexData> &verData, const QVector<GLuint> &indexData,
           const Object3D::InfoObject3D &infoObj);
  ~Object3D();
  void operator=(const Object3D &other);

  void init(const QVector<VertexData> &verData,
            const QVector<GLuint> &indexData,
            const Object3D::InfoObject3D &infoObj);

  void x_translate(const float &x) { xTranslate_ = x; }
  void y_translate(const float &y) { yTranslate_ = y; }
  void z_translate(const float &z) { zTranslate_ = z; }

  void x_rotate(const float &x) { xRotate_ = x; }
  void y_rotate(const float &y) { yRotate_ = y; }
  void z_rotate(const float &z) { zRotate_ = z; }

  void scale(const float &s) { scale_ = s; }

  const S21Matrix getModelMatrix();

  QOpenGLBuffer &getVertBuffer() { return vertBuffer_; }
  QOpenGLBuffer &getIndexBuffer() { return indexBuffer_; }
  const InfoObject3D &get_info() { return info_; }

  void delete_texture();
  void add_texture(const QString &pathTexture);
  QOpenGLTexture *get_texture() { return m_texture; }

 private:
  void free();

 private:
  float xRotate_;
  float yRotate_;
  float zRotate_;

  float xTranslate_;
  float yTranslate_;
  float zTranslate_;

  float scale_;

  QOpenGLTexture *m_texture;

  QOpenGLBuffer vertBuffer_;
  QOpenGLBuffer indexBuffer_;
};

/*---------------Парсер obj files--------------------*/
class LoaderObj {
 public:
  LoaderObj() {}
  const std::pair<QVector<VertexData>, QVector<GLuint>> loadObj(
      const QString &filePath, Object3D::InfoObject3D *info);

 private:
  void free_vectors();
  bool readCoords(const QStringList &list, bool *okCheck);
  bool readTexCoords(const QStringList &list, bool *okCheck);
  bool readNormals(const QStringList &list, bool *okCheck);
  bool readFaces(const QStringList &list, QVector<VertexData> *vertexes,
                 QVector<GLuint> *indexes, bool *okCheck);

 private:
  QVector<QVector3D> coords;
  QVector<QVector2D> texCoords;
  QVector<QVector3D> normals;
};
/*---------------------------------------------------*/

class GroupObjects3D {
 public:
  GroupObjects3D() {}
  ~GroupObjects3D() { deleteAllObjects(); }

  bool isEmpty() { return objects_.isEmpty(); }
  unsigned sumObjects() { return objects_.length(); }
  bool add_object(const QString &filePath) {
    Object3D::InfoObject3D info;
    std::pair<QVector<VertexData>, QVector<GLuint>> p =
        loader_.loadObj(filePath, &info);
    if (p.first.isEmpty()) {
      return false;
    } else {
      if (!objects_.isEmpty()) {
        objects_.pop_back();
      }
      objects_.append(new Object3D(p.first, p.second, info));
      return true;
    }
  }
  void deleteAllObjects() {
    while (!objects_.isEmpty()) {
      objects_.pop_back();
    }
  }
  /*----translate----*/
  void translateX_object(const float &x, const unsigned &indexObj = 0) {
    objects_[indexObj]->x_translate(x);
  }
  void translateY_object(const float &y, const unsigned &indexObj = 0) {
    objects_[indexObj]->y_translate(y);
  }
  void translateZ_object(const float &z, const unsigned &indexObj = 0) {
    objects_[indexObj]->z_translate(z);
  }
  /*----rotate----*/
  void rotateX_object(const float &x, const unsigned &indexObj = 0) {
    objects_[indexObj]->x_rotate(x);
  }
  void rotateY_object(const float &y, const unsigned &indexObj = 0) {
    objects_[indexObj]->y_rotate(y);
  }
  void rotateZ_object(const float &z, const unsigned &indexObj = 0) {
    objects_[indexObj]->z_rotate(z);
  }
  /*----scale----*/
  void scale_object(const float &s, const unsigned &indexObj = 0) {
    objects_[indexObj]->scale(s);
  }
  /*----model Matrix----*/
  const S21Matrix get_model_matrix_object(const unsigned &indexObj = 0) {
    return objects_[indexObj]->getModelMatrix();
  }
  /*----vertext buffer----*/
  QOpenGLBuffer &get_vertex_buffer_object(const unsigned &indexObj = 0) {
    return objects_[indexObj]->getVertBuffer();
  }
  /*----index buffer----*/
  QOpenGLBuffer &get_index_buffer_object(const unsigned &indexObj = 0) {
    return objects_[indexObj]->getIndexBuffer();
  }
  /*----info about object----*/
  const Object3D::InfoObject3D &get_info_object(const unsigned &indexObj = 0) {
    return objects_[indexObj]->get_info();
  }
  /*----texture object----*/
  QOpenGLTexture *get_texture_object(const unsigned &indexObj = 0) {
    return objects_[indexObj]->get_texture();
  }
  void add_texture_to_object(const QString &path,
                             const unsigned &indexObj = 0) {
    return objects_[indexObj]->add_texture(path);
  }
  void delete_texture_from_object(const unsigned &indexObj = 0) {
    return objects_[indexObj]->delete_texture();
  }

 private:
  QVector<Object3D *> objects_;
  LoaderObj loader_;
};

}  // namespace s21_3DViewer
