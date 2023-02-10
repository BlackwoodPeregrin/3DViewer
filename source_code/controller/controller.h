#pragma once

#include "../model/camera3D.h"
#include "../model/object3D.h"

namespace s21_3DViewer
{
class Controller;
class Memento
{
public:
  Memento(QString pathToTexture, GroupSettings stateSets, Camera3D stateCamera)
  {
    pathToTexture_ = pathToTexture;
    stateSets_ = stateSets;
    stateCamera_ = stateCamera;
  }

  Memento(Memento const&) = delete;
  Memento(Memento&&) = delete;

  Memento& operator=(Memento const&) = delete;
  Memento& operator=(Memento&&) = delete;

private:
  friend Controller;

  GroupSettings getStateSets()
  {
    return stateSets_;
  }

  Camera3D getStateCamera()
  {
    return stateCamera_;
  }

  QString getStateTexture()
  {
    return pathToTexture_;
  }

  QString pathToTexture_;
  GroupSettings stateSets_;
  Camera3D stateCamera_;
};

class Controller
{
private:
  Controller()
  {
  }
  Controller(Controller const&) = delete;
  Controller& operator=(Controller const&) = delete;

public:
  static Controller& getInstance()
  {
    static Controller controller;
    return controller;
  }

  /*--------MAIN SETTINGS SETTERS--------------*/
  unsigned get_projection_sets()
  {
    return settings_.get_projection();
  }

  unsigned get_line_type_sets(unsigned indexSetting = 0)
  {
    return settings_.get_lineType_index_setting(indexSetting);
  }

  float get_line_size_sets(unsigned indexSetting = 0)
  {
    return settings_.get_lineSize_index_setting(indexSetting);
  }

  QVector4D get_line_color_sets(unsigned indexSetting = 0)
  {
    std::array<float, RGBA::N> tmp = settings_.get_lineColor_index_setting(indexSetting);

    return QVector4D(tmp[RGBA::RED], tmp[RGBA::GREEN], tmp[RGBA::BLUE], tmp[RGBA::ALPHA]);
  }

  unsigned get_vert_type_sets(unsigned indexSetting = 0)
  {
    return settings_.get_vertType_index_setting(indexSetting);
  }

  float get_vert_size_sets(unsigned indexSetting = 0)
  {
    return settings_.get_vertSize_index_setting(indexSetting);
  }

  QVector4D get_vert_color_sets(unsigned indexSetting = 0)
  {
    std::array<float, RGBA::N> tmp = settings_.get_vertColor_index_setting(indexSetting);
    return QVector4D(tmp[RGBA::RED], tmp[RGBA::GREEN], tmp[RGBA::BLUE], tmp[RGBA::ALPHA]);
  }
  const QVector4D get_bg_color_sets()
  {
    std::array<float, RGBA::N> tmp = settings_.get_bgColor_setting();
    return QVector4D(tmp[RGBA::RED], tmp[RGBA::GREEN], tmp[RGBA::BLUE], tmp[RGBA::ALPHA]);
  }
  const QVector4D get_surfaces_color_sets(const unsigned& indexSetting = 0)
  {
    std::array<float, RGBA::N> tmp = settings_.get_surfaceColor_index_setting(indexSetting);
    return QVector4D(tmp[RGBA::RED], tmp[RGBA::GREEN], tmp[RGBA::BLUE], tmp[RGBA::ALPHA]);
  }
  const unsigned& get_draw_type_sets(const unsigned& indexSetting = 0)
  {
    return settings_.get_drawType_index_setting(indexSetting);
  }
  const QString get_texture_path_sets(const unsigned& indexSetting = 0)
  {
    QString texturePath = QString::fromUtf8(settings_.get_texture_path_index_settings(indexSetting).c_str());
    return texturePath;
  }

  /*--------MAIN SETTINGS GETTERS-------------*/
  void set_projection_sets(const unsigned& typeProjaction)
  {
    settings_.set_projection(typeProjaction);
  }

  void set_line_type_sets(const unsigned& lineType, const unsigned& indexSetting = 0)
  {
    settings_.set_lineType_index_setting(lineType, indexSetting);
  }

  void set_line_color_sets(float r, float g, float b, float a, unsigned indexSetting = 0)
  {
    settings_.set_lineColor_index_setting(r, g, b, a, indexSetting);
  }

  void set_line_size_sets(float lineSize, unsigned indexSetting = 0)
  {
    settings_.set_lineSize_index_setting(lineSize, indexSetting);
  }

  void set_vert_type_sets(const unsigned& vertType, const unsigned& indexSetting = 0)
  {
    settings_.set_vertType_index_setting(vertType, indexSetting);
  }

  void set_vert_color_sets(float r, float g, float b, float a, unsigned indexSetting = 0)
  {
    settings_.set_vertColor_index_setting(r, g, b, a, indexSetting);
  }

  void set_vert_size_sets(const float& vertSize, const unsigned& indexSetting = 0)
  {
    settings_.set_vertSize_index_setting(vertSize, indexSetting);
  }
  void set_bg_color_sets(const float& r, const float& g, const float& b, const float& a)
  {
    settings_.set_bgColor(r, g, b, a);
  }
  void set_surfaces_color_sets(const float& r, const float& g, const float& b, const float& a,
                               const unsigned& indexSetting = 0)
  {
    settings_.set_surfaceColor_index_setting(r, g, b, a, indexSetting);
  }
  void set_draw_type_sets(const unsigned& drawType, const unsigned& indexSetting = 0)
  {
    settings_.set_drawType_index_setting(drawType, indexSetting);
  }
  void set_texture_path_sets(const QString& texturePath, const unsigned& indexSetting = 0)
  {
    settings_.set_texture_path_index_settings(texturePath.toStdString(), indexSetting);
  }

  /*-----CAMERA OPTIONS------*/
  void translate_camera(const QVector3D& t)
  {
    camera_.translate(t);
  }
  void rotate_camera(const QQuaternion& r)
  {
    camera_.rotate(r);
  }
  void scale_camera(const float& s)
  {
    camera_.scale(s);
  }
  const QMatrix4x4& get_view_matrix()
  {
    return camera_.getViewMatrix();
  }

  /*-----OBJECTS OPTIONS------*/
  bool have_objects()
  {
    return !objects_.isEmpty();
  }
  unsigned get_sum_objects()
  {
    return objects_.sumObjects();
  }

  bool add_object(const QString& filePath)
  {
    QString texturePath = QString::fromUtf8(settings_.get_texture_path_index_settings().c_str());
    if (texturePath.isEmpty())
    {
      return objects_.add_object(filePath);
    }
    else
    {
      bool res = objects_.add_object(filePath);
      if (res == true)
      {
        objects_.add_texture_to_object(texturePath);
      }
      return res;
    }
  }
  void delete_all_objects()
  {
    objects_.deleteAllObjects();
  }
  /*----translate----*/
  void x_translate_object(const float& x, const unsigned& indexObj = 0)
  {
    objects_.translateX_object(x / 20, indexObj);
  }
  void y_translate_object(const float& y, const unsigned& indexObj = 0)
  {
    objects_.translateY_object(y / 20, indexObj);
  }
  void z_translate_object(const float& z, const unsigned& indexObj = 0)
  {
    objects_.translateZ_object(z / 20, indexObj);
  }
  /*----rotate----*/
  void x_rotate_object(const float& x, const unsigned& indexObj = 0)
  {
    objects_.rotateX_object(x, indexObj);
  }
  void y_rotate_object(const float& y, const unsigned& indexObj = 0)
  {
    objects_.rotateY_object(y, indexObj);
  }
  void z_rotate_object(const float& z, const unsigned& indexObj = 0)
  {
    objects_.rotateZ_object(z, indexObj);
  }
  /*----scale----*/
  void scale_object(const float& s, const unsigned& indexObj = 0)
  {
    objects_.scale_object(s / 2, indexObj);
  }

  QMatrix4x4 get_model_matrix_object(const unsigned& indexObj = 0)
  {
    return objects_.get_model_matrix_object(indexObj);
  }

  QOpenGLBuffer& get_vertex_buffer_object(const unsigned& indexObj = 0)
  {
    return objects_.get_vertex_buffer_object(indexObj);
  }

  QOpenGLBuffer& get_index_buffer_object(const unsigned& indexObj = 0)
  {
    return objects_.get_index_buffer_object(indexObj);
  }

  const Object3D::InfoObject3D& get_info_object(const unsigned& indexObj = 0)
  {
    return objects_.get_info_object(indexObj);
  }

  QOpenGLTexture* get_texture_object(const unsigned& indexObj = 0)
  {
    return objects_.get_texture_object(indexObj);
  }

  void add_texture_to_object(const QString& pathTexture, const unsigned& indexObj = 0)
  {
    objects_.add_texture_to_object(pathTexture, indexObj);
  }

  void add_texture_to_object(const unsigned& indexObj = 0)
  {
    QString texturePath = QString::fromUtf8(settings_.get_texture_path_index_settings(indexObj).c_str());
    objects_.add_texture_to_object(texturePath, indexObj);
  }

  void delete_texture_from_object(const unsigned& indexObj = 0)
  {
    objects_.delete_texture_from_object(indexObj);
    settings_.set_texture_path_index_settings("");
  }

  /*-----GET LIGHT OPTIONS------*/
  const QVector4D getLightPosition(const unsigned& indexSetting = 0)
  {
    std::array<float, RGBA::N> tmp = settings_.get_lightPosition_index_light(indexSetting);
    return QVector4D(tmp[RGBA::RED], tmp[RGBA::GREEN], tmp[RGBA::BLUE], tmp[RGBA::ALPHA]);
  }
  const float& getLightPower(const unsigned& indexSetting = 0)
  {
    return settings_.get_lightPower_index_light(indexSetting);
  }
  const float& getSpecularFactor(const unsigned& indexSetting = 0)
  {
    return settings_.get_lightSpecularFactor_index_light(indexSetting);
  }
  const QVector4D getSpecularColor(const unsigned& indexSetting = 0)
  {
    std::array<float, RGBA::N> color = settings_.get_lightSpecularColor_index_light(indexSetting);
    return QVector4D(color[RGBA::RED], color[RGBA::GREEN], color[RGBA::BLUE], color[RGBA::ALPHA]);
  }

  const QVector4D getLightColor(const unsigned& indexSetting = 0)
  {
    float red = settings_.get_lightColor_red_index_light(indexSetting);
    float green = settings_.get_lightColor_green_index_light(indexSetting);
    float blue = settings_.get_lightColor_blue_index_light(indexSetting);
    return QVector4D(red, green, blue, 1.0);
  }
  const float& getAmbientFactor(const unsigned& indexSetting = 0)
  {
    return settings_.get_lightAmbientFactor_index_light(indexSetting);
  }

  /*-----SET LIGHT OPTIONS------*/
  void setLightPosition(const float& x, const float& y, const float& z, const float& w = 1.0,
                        const unsigned& indexSetting = 0)
  {
    settings_.set_lightPosition_index_light(x, y, z, w, indexSetting);
  }
  void setLightPower(const float& power, const unsigned& indexSetting = 0)
  {
    settings_.set_lightPower_index_light(power, indexSetting);
  }
  void setSpecularFactor(const float& sF, const unsigned& indexSetting = 0)
  {
    settings_.set_lightSpecularFactor_index_light(sF, indexSetting);
  }
  void setSpecularColor(const float& r, const float& g, const float& b, const float& a,
                        const unsigned& indexSetting = 0)
  {
    settings_.set_lightSpecularColor_index_light(r, g, b, a, indexSetting);
  }
  void setLightColorRed(const float& red, const unsigned& indexSetting = 0)
  {
    settings_.set_lightColor_red_index_light(red, indexSetting);
  }
  void setLightColorGreen(const float& green, const unsigned& indexSetting = 0)
  {
    settings_.set_lightColor_green_index_light(green, indexSetting);
  }
  void setLightColorBlue(const float& blue, const unsigned& indexSetting = 0)
  {
    settings_.set_lightColor_blue_index_light(blue, indexSetting);
  }
  void setAmbientFactor(const float& aF, const unsigned& indexSetting = 0)
  {
    settings_.set_lightAmbientFactor_index_light(aF, indexSetting);
  }

  /*-----LIGHT STATUS------*/
  const bool& getLightStatus()
  {
    return settings_.get_lightStatus();
  }
  void setLightStatus(const bool& status)
  {
    settings_.set_lightStatus(status);
  }

  /*-----LIGHT SHADE------*/
  const bool& getLightShade()
  {
    return settings_.get_lightShade();
  }
  void setLightShade(const bool& shade)
  {
    settings_.set_lightShade(shade);
  }

  /*---WINDOW SIZE SETTINGS---*/
  const float& get_windowWidth_sets()
  {
    return settings_.get_window_width();
  }
  const float& get_windowHeight_sets()
  {
    return settings_.get_window_height();
  }
  void set_windowWidth_sets(const float& src)
  {
    settings_.set_window_width(src);
  }
  void set_windowHeight_sets(const float& src)
  {
    settings_.set_window_height(src);
  }

  /*---pattern memento---*/
  void getStateMementoPrev()
  {
    if (caretakerPrev_.length() > 0)
    {
      settings_ = caretakerPrev_.back().getStateSets();
      camera_ = caretakerPrev_.back().getStateCamera();
      QString texturePath = caretakerPrev_.back().getStateTexture();
      settings_.set_texture_path_index_settings(texturePath.toStdString());
      if (texturePath.isEmpty())
      {
        objects_.delete_texture_from_object();
      }
      else
      {
        objects_.add_texture_to_object(texturePath);
      }
      caretakerPrev_.pop_back();
    }
  }
  void getStateMementoNext()
  {
    if (caretakerNext_.length() > 0)
    {
      settings_ = caretakerNext_.back().getStateSets();
      camera_ = caretakerNext_.back().getStateCamera();
      QString texturePath = caretakerNext_.back().getStateTexture();

      settings_.set_texture_path_index_settings(texturePath.toStdString());

      if (texturePath.isEmpty())
      {
        objects_.delete_texture_from_object();
      }
      else
      {
        objects_.add_texture_to_object(texturePath);
      }
      caretakerNext_.pop_back();
    }
  }
  void backupPrev()
  {
    Object3D::InfoObject3D info = objects_.get_info_object();
    QString texturePath = info.getPathToTextureObj();

    Memento state(texturePath, settings_, camera_);
    caretakerPrev_.append(state);
  }
  void backupNext()
  {
    Object3D::InfoObject3D info = objects_.get_info_object();
    QString texturePath = info.getPathToTextureObj();

    Memento state(texturePath, settings_, camera_);
    caretakerNext_.append(state);
  }
  void clearConditions()
  {
    caretakerPrev_.clear();
    caretakerNext_.clear();
  }
  /*---------------------*/

  // save settings in config file //
  void save_settings()
  {
    settings_.save();
  }
  void save_camera()
  {
    camera_.save_camera();
  }

private:
  GroupObjects3D objects_;
  GroupSettings settings_;
  Camera3D camera_;
  /*---pattern memento---*/
  QVector<Memento> caretakerPrev_;
  QVector<Memento> caretakerNext_;
  /*---------------------*/
};
}  // namespace s21_3DViewer
