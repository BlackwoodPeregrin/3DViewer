#pragma once

#include "../view/camera3D.h"
#include "../model/groupObject3D.h"
#include "../model/settings/groupSetting.h"
#include "../memento/memento.h"

namespace s21_3DViewer
{
class Controller
{
private:
  Controller() = default;
  ~Controller() = default;
  Controller(Controller const&) = delete;
  Controller(Controller&&) = delete;
  Controller& operator=(Controller const&) = delete;
  Controller& operator=(Controller&&) = delete;

public:
  static Controller& getInstance();

  /*--- Group Setting ---*/

  /*--- Draw Group Setting ---*/

  unsigned lineType_sets(unsigned indexSetting = 0) const;
  float lineSize_sets(unsigned indexSetting = 0) const;
  QVector4D lineColor_sets(unsigned indexSetting = 0) const;
  float lineColorRed_sets(unsigned indexSetting = 0) const;
  float lineColorGreen_sets(unsigned indexSetting = 0) const;
  float lineColorBlue_sets(unsigned indexSetting = 0) const;
  float lineColorAlpha_sets(unsigned indexSetting = 0) const;
  unsigned vertType_sets(unsigned indexSetting = 0) const;
  float vertSize_sets(unsigned indexSetting = 0) const;
  QVector4D vertColor_sets(unsigned indexSetting = 0) const;
  float vertColorRed_sets(unsigned indexSetting = 0) const;
  float vertColorGreen_sets(unsigned indexSetting = 0) const;
  float vertColorBlue_sets(unsigned indexSetting = 0) const;
  float vertColorAlpha_sets(unsigned indexSetting = 0) const;
  QVector4D surfacesColor_sets(unsigned indexSetting = 0) const;
  float surfacesColorRed_sets(unsigned indexSetting = 0) const;
  float surfacesColorGreen_sets(unsigned indexSetting = 0) const;
  float surfacesColorBlue_sets(unsigned indexSetting = 0) const;
  float surfacesColorAlpha_sets(unsigned indexSetting = 0) const;
  unsigned drawType_sets(unsigned indexSetting = 0) const;

  void setLineType_sets(unsigned lineType, unsigned indexSetting = 0);
  void setLineSize_sets(float lineSize, unsigned indexSetting = 0);
  void setLineColor_sets(float r, float g, float b, float a, unsigned indexSetting = 0);
  void setLineColor_sets(const QVector4D& color, unsigned indexSetting = 0);
  void setVertType_sets(unsigned vertType, unsigned indexSetting = 0);
  void setVertSize_sets(float vertSize, unsigned indexSetting = 0);

  void setVertColor_sets(float r, float g, float b, float a, unsigned indexSetting = 0);
  void setVertColor_sets(const QVector4D& color, unsigned indexSetting = 0);
  void setSurfaces_color_sets(float r, float g, float b, float a, unsigned indexSetting = 0);
  void setSurfaces_color_sets(const QVector4D& color, unsigned indexSetting = 0);
  void setDrawType_sets(unsigned drawType, unsigned indexSetting = 0);

  /*--- Light Group Setting ---*/

  QVector4D lightPosition_sets(unsigned indexSetting = 0) const;
  float lightPositionX_sets(unsigned indexSetting = 0) const;
  float lightPositionY_sets(unsigned indexSetting = 0) const;
  float lightPositionZ_sets(unsigned indexSetting = 0) const;
  float lightPower_sets(unsigned indexSetting = 0) const;
  float specularFactor_sets(unsigned indexSetting = 0) const;
  float ambientFactor_sets(unsigned indexSetting = 0) const;
  QVector4D specularColor(unsigned indexSetting = 0) const;
  float specularColorRed_sets(unsigned indexSetting = 0) const;
  float specularColorGreen_sets(unsigned indexSetting = 0) const;
  float specularColorBlue_sets(unsigned indexSetting = 0) const;
  float specularColorAlpha_sets(unsigned indexSetting = 0) const;
  QVector4D lightColor_sets(unsigned indexSetting = 0) const;
  float lightColorRed_sets(unsigned indexSetting = 0) const;
  float lightColorGreen_sets(unsigned indexSetting = 0) const;
  float lightColorBlue_sets(unsigned indexSetting = 0) const;
  float lightColorAlpha_sets(unsigned indexSetting = 0) const;

  void setLightPosition_sets(float x, float y, float z, unsigned indexSetting = 0);
  void setLightPosition_sets(const QVector3D& pos, unsigned indexSetting = 0);
  void setLightPositionX_sets(float x, unsigned indexSetting = 0);
  void setLightPositionY_sets(float y, unsigned indexSetting = 0);
  void setLightPositionZ_sets(float z, unsigned indexSetting = 0);
  void setLightPower_sets(float power, unsigned indexSetting = 0);
  void setSpecularFactor_sets(float sF, unsigned indexSetting = 0);
  void setAmbientFactor_sets(float aF, unsigned indexSetting = 0);
  void setLightSpecularColor_sets(float r, float g, float b, float a, unsigned indexSetting = 0);
  void setLightSpecularColor_sets(const QVector4D& color, unsigned indexSetting = 0);
  void setLightSpecularColorRed_sets(float r, unsigned indexSetting = 0);
  void setLightSpecularColorGreen_sets(float g, unsigned indexSetting = 0);
  void setLightSpecularColorBlue_sets(float b, unsigned indexSetting = 0);
  void setLightSpecularColorAlpha_sets(float a, unsigned indexSetting = 0);
  void setLightColor_sets(float r, float g, float b, float a, unsigned indexSetting = 0);
  void setLightColor_sets(const QVector4D& color, unsigned indexSetting = 0);
  void setLightColorRed_sets(float r, unsigned indexSetting = 0);
  void setLightColorGreen_sets(float g, unsigned indexSetting = 0);
  void setLightColorBlue_sets(float b, unsigned indexSetting = 0);
  void setLightColorAlpha_sets(float a, unsigned indexSetting = 0);

  /*--- Main Group Setting ---*/

  unsigned projection_sets() const;
  bool lightStatus_sets() const;
  bool lightShade() const;
  QVector4D bgColor_sets() const;
  float bgColorRed_sets() const;
  float bgColorGreen_sets() const;
  float bgColorBlue_sets() const;
  float bgColorAlpha_sets() const;
  float wScreen_sets() const;
  float hScreent_sets() const;

  void setProjection_sets(unsigned typeProjaction);
  void setLightStatus_sets(bool status);
  void setLightShade_sets(bool shade);
  void setBgColor_sets(float r, float g, float b, float a);
  void setBgColorRed_sets(float r);
  void setBgColorGreen_sets(float g);
  void setBgColorBlue_sets(float b);
  void setBgColorAlpha_sets(float a);
  void setWScreen_sets(float w);
  void setHScreen_sets(float h);

  /*--- Camera Setting ---*/

  void translateCamera(const QVector3D& t);
  void rotateCamera(const QQuaternion& r);
  void scaleCamera(float s);
  QMatrix4x4 viewMatrixCamera() const;

  /*--- Object Group Setting ---*/

  bool haveObjects() const;
  unsigned sumObjects() const;
  bool add_object(const QString& filePath);
  void delete_all_objects();

  void translateX_object(float x, unsigned indexObj = 0);
  void translateY_object(float y, unsigned indexObj = 0);
  void translateZ_object(float z, unsigned indexObj = 0);
  void rotateX_object(float x, unsigned indexObj = 0);
  void rotateY_object(float y, unsigned indexObj = 0);
  void rotateZ_object(float z, unsigned indexObj = 0);
  void scale_object(float s, unsigned indexObj = 0);

  QMatrix4x4 modelMatrix_object(unsigned indexObj = 0) const;
  QOpenGLBuffer& vertexBuffer_object(unsigned indexObj = 0);
  QOpenGLBuffer& indexBuffer_object(unsigned indexObj = 0);
  const InfoObject3D& info_object(unsigned indexObj = 0) const;
  void addTexture_object(const QString& pathTexture, unsigned indexObj = 0);
  void deleteTextureFrom_object(unsigned indexObj = 0);
  QOpenGLTexture* texture_object(unsigned indexObj = 0);
  const QString& pathToTexture_object(unsigned indexObj = 0) const;

  /*---pattern memento---*/
  //  void getStateMementoPrev()
  //  {
  //    if (caretakerPrev_.length() > 0)
  //    {
  //      m_setting = caretakerPrev_.back().getStateSets();
  //      m_camera = caretakerPrev_.back().getStateCamera();
  //      QString texturePath = caretakerPrev_.back().getStateTexture();
  //      m_setting.set_texture_path_index_settings(texturePath.toStdString());
  //      if (texturePath.isEmpty())
  //      {
  //        m_object.delete_texture_from_object();
  //      }
  //      else
  //      {
  //        m_object.add_texture_to_object(texturePath);
  //      }
  //      caretakerPrev_.pop_back();
  //    }
  //  }
  //  void getStateMementoNext()
  //  {
  //    if (caretakerNext_.length() > 0)
  //    {
  //      m_setting = caretakerNext_.back().getStateSets();
  //      m_camera = caretakerNext_.back().getStateCamera();
  //      QString texturePath = caretakerNext_.back().getStateTexture();

  //      m_setting.set_texture_path_index_settings(texturePath.toStdString());

  //      if (texturePath.isEmpty())
  //      {
  //        m_object.delete_texture_from_object();
  //      }
  //      else
  //      {
  //        m_object.add_texture_to_object(texturePath);
  //      }
  //      caretakerNext_.pop_back();
  //    }
  //  }
  //  void backupPrev()
  //  {
  //    Object3D::InfoObject3D info = m_object.info_object();
  //    QString texturePath = info.getPathToTextureObj();

  //    Memento state(texturePath, m_setting, m_camera);
  //    caretakerPrev_.append(state);
  //  }
  //  void backupNext()
  //  {
  //    Object3D::InfoObject3D info = m_object.info_object();
  //    QString texturePath = info.getPathToTextureObj();

  //    Memento state(texturePath, m_setting, m_camera);
  //    caretakerNext_.append(state);
  //  }
  //  void clearConditions()
  //  {
  //    caretakerPrev_.clear();
  //    caretakerNext_.clear();
  //  }
  /*---------------------*/

  // save settings in config file //
  void save_settings()
  {
    //    m_setting.save();
  }
  void save_camera()
  {
    //    m_camera.save_camera();
  }

private:
  GroupObjects3D m_object;
  GroupSettings m_setting;
  Camera3D m_camera;
  Memento m_memento;
};
}  // namespace s21_3DViewer
