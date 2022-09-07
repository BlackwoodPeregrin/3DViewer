#pragma once

#include <QGuiApplication>
#include <QScreen>
#include <array>
#include <fstream>
#include <string>

namespace s21_3DViewer {

constexpr float kMaxLineSize = 10.0;
constexpr float kMinLineSize = 1.0;

constexpr float kMaxVertSize = 20.0;
constexpr float kMinVertSize = 20.0;

constexpr float kMaxLightPower = 30.0;
constexpr float kMinLightPower = 0.0;

constexpr float kMaxLightSpecularFactor = 100.0;
constexpr float kMinLightSpecularFactor = 1.0;

constexpr float kMaxLightAmbientFactor = 1.0;
constexpr float kMinLightAmbientFactor = 0.0;

constexpr unsigned kSumSettingObject = 5;
constexpr unsigned kSumLightSourses = 5;

enum RGBA { RED, GREEN, BLUE, ALPHA, N };
enum projType { Parallel, Central };
enum lineType { Solid, Dashed };
enum vertType { None, Circle, Square };
enum typeDraw { Points, Lines, Line_Loop, Line_Strip, Triangles };
enum lightStatus { OFF, ON };
enum shaddingType { Flat, Soft };

/*-------------------------------Default Object
 * Settings-----------------------------------*/
constexpr unsigned kDefaultLineType = lineType::Solid;
constexpr float kDefaultLineSize = 1.0;
constexpr std::array<float, RGBA::N> kDefaultLineColor = {1.0, 1.0, 1.0,
                                                          1.0};  // white;
constexpr unsigned kDefaultVertType = vertType::Square;
constexpr float kDefaultVertSize = 5.0;
constexpr std::array<float, RGBA::N> kDefaultVertColor = {1.0, 0.0, 0.0,
                                                          1.0};  // red
constexpr std::array<float, RGBA::N> kDefaultSurfacesColor = {1.0, 1.0, 1.0,
                                                              1.0};  // white;
constexpr unsigned kDefaultDrawType = typeDraw::Lines;

/*-------------------------------Default Lights
 * Settings-----------------------------------*/
constexpr std::array<float, RGBA::N> kDefaultLightPosition_ = {0.0, 0.0, 0.0,
                                                               1.0};
constexpr float kDefaultLightPower = 1;
constexpr float kDefaultSpecularFactor = 50.0;
constexpr float kDefaultAmbientFactor = 0.0;
constexpr std::array<float, RGBA::N> kDefaultSpecularColor = {1.0, 1.0, 1.0,
                                                              1.0};  // white
// light color RGB
constexpr float kDefaultLightColorRed = 1.0;
constexpr float kDefaultLightColorGreen = 1.0;
constexpr float kDefaultLightColorBLue = 1.0;
//
constexpr bool kDefaultLightShade = shaddingType::Soft;
constexpr bool kDefaultLightStatus = lightStatus::OFF;
/*----------------------------------------------------------------------------------*/

/*-------------------------------Default Common
 * Settings----------------------------*/
constexpr unsigned kDefaultProjection = projType::Central;
constexpr std::array<float, RGBA::N> kDefaultBgColor = {0.0, 0.0, 0.0,
                                                        1.0};  // black
/*----------------------------------------------------------------------------------*/

/*-------------------------------Default Screen
 * Settings----------------------------*/
constexpr float kDefaultWidthScreen = 0.8;   //
constexpr float kDefaultHeightScreen = 0.9;  //
/*----------------------------------------------------------------------------------*/

class SettingObject {
 public:
  SettingObject();
  SettingObject(const SettingObject &other) { *this = other; }
  void operator=(const SettingObject &other) {
    line_type_ = other.line_type_;
    line_size_ = other.line_size_;
    line_color_ = other.line_color_;
    vert_type_ = other.vert_type_;
    vert_size_ = other.vert_size_;
    vert_color_ = other.vert_color_;
    surfaces_color_ = other.surfaces_color_;
    draw_type_ = other.draw_type_;
    pathToTexture_ = other.pathToTexture_;
  }

  const unsigned &get_line_type() { return line_type_; }
  const std::array<float, RGBA::N> &get_line_color() { return line_color_; }
  const float &get_line_size() { return line_size_; }
  const unsigned &get_vert_type() { return vert_type_; }
  const std::array<float, RGBA::N> &get_vert_color() { return vert_color_; }
  const float &get_vert_size() { return vert_size_; }
  const std::array<float, RGBA::N> &get_surfaces_color() {
    return surfaces_color_;
  }
  const unsigned &get_draw_type() { return draw_type_; }
  const std::string &get_texture_path() { return pathToTexture_; }

  void set_line_type(const unsigned &lineType);
  void set_line_size(const float &lineSize);
  void set_line_color(const float &r, const float &g, const float &b,
                      const float &a);
  void set_line_color(const std::array<float, RGBA::N> &color);
  void set_vert_type(const unsigned &vertType);
  void set_vert_size(const float &vertSize);
  void set_vert_color(const float &r, const float &g, const float &b,
                      const float &a);
  void set_vert_color(const std::array<float, RGBA::N> &color);
  void set_surfaces_color(const float &r, const float &g, const float &b,
                          const float &a);
  void set_surfaces_color(const std::array<float, RGBA::N> &color);
  void set_draw_type(const unsigned &drawType);
  void set_texture_path(const std::string &pathToTexture);

  // сохранения в файл настроек
  void save(unsigned num);
  void load(unsigned num);
  void set_default();

 private:
  /*---значение натсроек линий---*/
  unsigned line_type_;
  float line_size_;
  std::array<float, RGBA::N> line_color_;
  /*---значение натсроек вершин---*/
  unsigned vert_type_;
  float vert_size_;
  std::array<float, RGBA::N> vert_color_;
  /*---значение натсроек цвета поверхности---*/
  std::array<float, RGBA::N> surfaces_color_;
  /*---значение натсроек типа отрисовки---*/
  unsigned draw_type_;
  /*---путь до текстуры объекта, если есть---*/
  std::string pathToTexture_;
};

class LightSource {
 public:
  LightSource();
  LightSource(const LightSource &other) { *this = other; }
  void operator=(const LightSource &other) {
    light_position_ = other.light_position_;
    light_power_ = other.light_power_;
    specular_factor_ = other.specular_factor_;
    ambient_factor_ = other.ambient_factor_;
    specular_color_ = other.specular_color_;
    light_color_red_ = other.light_color_red_;
    light_color_green_ = other.light_color_green_;
    light_color_blue_ = other.light_color_blue_;
  }
  /*---getters light---*/
  const std::array<float, RGBA::N> &get_light_position() {
    return light_position_;
  }
  const float &get_light_power() { return light_power_; }
  const float &get_light_specular_factor() { return specular_factor_; }
  const float &get_light_ambient_factor() { return ambient_factor_; }
  const std::array<float, RGBA::N> &get_light_specular_color() {
    return specular_color_;
  }
  const float &get_light_color_red() { return light_color_red_; }
  const float &get_light_color_green() { return light_color_green_; }
  const float &get_light_color_blue() { return light_color_blue_; }

  /*---setters light---*/
  void set_light_position(const float &x, const float &y, const float &z,
                          const float &w = 1.0);
  void set_light_position(std::array<float, 4> position);
  void set_light_power(const float &lightPower);
  void set_light_specular_factor(const float &sF);
  void set_light_ambient_factor(const float &aF);
  void set_light_specular_color(const float &r, const float &g, const float &b,
                                const float &a);
  void set_light_specular_color(const std::array<float, RGBA::N> &color);
  void set_light_color_red(const float &red);
  void set_light_color_green(const float &green);
  void set_light_color_blue(const float &blue);

  // сохранения в файл настроек
  void save(unsigned num);
  void load(unsigned num);
  void set_default();

 private:
  std::array<float, RGBA::N> light_position_;
  float light_power_;
  float specular_factor_;
  float ambient_factor_;
  std::array<float, RGBA::N> specular_color_;
  float light_color_red_;
  float light_color_green_;
  float light_color_blue_;
};

class GroupSettings {
 public:
  GroupSettings();
  GroupSettings(const GroupSettings &group);
  ~GroupSettings();

  void operator=(const GroupSettings &group);

  void add_settings_to_group();
  void add_lightSource_to_group();

  /*---LINES---*/
  const unsigned &get_lineType_index_setting(const unsigned &index = 0) {
    return groupSettings_[index].get_line_type();
  }
  const float &get_lineSize_index_setting(const unsigned &index = 0) {
    return groupSettings_[index].get_line_size();
  }
  const std::array<float, RGBA::N> &get_lineColor_index_setting(
      const unsigned &index = 0) {
    return groupSettings_[index].get_line_color();
  }
  void set_lineType_index_setting(const unsigned &lineType,
                                  const unsigned &index = 0);
  void set_lineSize_index_setting(const float &lineSize,
                                  const unsigned &index = 0);
  void set_lineColor_index_setting(const float &r, const float &g,
                                   const float &b, const float &a,
                                   const unsigned &index = 0);
  /*----------------*/

  /*---VERTEXES---*/
  const unsigned &get_vertType_index_setting(const unsigned &index = 0) {
    return groupSettings_[index].get_vert_type();
  }
  const float &get_vertSize_index_setting(const unsigned &index = 0) {
    return groupSettings_[index].get_vert_size();
  }
  const std::array<float, RGBA::N> &get_vertColor_index_setting(
      const unsigned &index = 0) {
    return groupSettings_[index].get_vert_color();
  }
  void set_vertType_index_setting(const unsigned &vertType,
                                  const unsigned &index = 0);
  void set_vertSize_index_setting(const float &vertSize,
                                  const unsigned &index = 0);
  void set_vertColor_index_setting(const float &r, const float &g,
                                   const float &b, const float &a,
                                   const unsigned &index = 0);
  /*----------------*/

  /*---SURFACES COLOR---*/
  const std::array<float, RGBA::N> &get_surfaceColor_index_setting(
      const unsigned &index = 0) {
    return groupSettings_[index].get_surfaces_color();
  }
  void set_surfaceColor_index_setting(const float &r, const float &g,
                                      const float &b, const float &a,
                                      const unsigned &index = 0);
  /*----------------*/

  /*---TYPE DRAWING---*/
  const unsigned &get_drawType_index_setting(const unsigned &index = 0) {
    return groupSettings_[index].get_draw_type();
  }
  void set_drawType_index_setting(const unsigned &drawType,
                                  const unsigned &index = 0);
  /*----------------*/

  /*---TEXTURE PATH---*/
  const std::string &get_texture_path_index_settings(
      const unsigned &index = 0) {
    return groupSettings_[index].get_texture_path();
  }
  void set_texture_path_index_settings(const std::string &texturePath,
                                       const unsigned &index = 0) {
    groupSettings_[index].set_texture_path(texturePath);
  }
  /*----------------*/

  /*---LIGHT SETTINGS---*/
  const std::array<float, RGBA::N> &get_lightPosition_index_light(
      const unsigned &index = 0) {
    return lightSourses_[index].get_light_position();
  }

  const float &get_lightPower_index_light(const unsigned &index = 0) {
    return lightSourses_[index].get_light_power();
  }

  const float &get_lightSpecularFactor_index_light(const unsigned &index = 0) {
    return lightSourses_[index].get_light_specular_factor();
  }

  const float &get_lightAmbientFactor_index_light(const unsigned &index = 0) {
    return lightSourses_[index].get_light_ambient_factor();
  }

  const std::array<float, RGBA::N> &get_lightSpecularColor_index_light(
      const unsigned &index = 0) {
    return lightSourses_[index].get_light_specular_color();
  }

  const float &get_lightColor_red_index_light(const unsigned &index = 0) {
    return lightSourses_[index].get_light_color_red();
  }

  const float &get_lightColor_green_index_light(const unsigned &index = 0) {
    return lightSourses_[index].get_light_color_green();
  }

  const float &get_lightColor_blue_index_light(const unsigned &index = 0) {
    return lightSourses_[index].get_light_color_blue();
  }

  void set_lightPosition_index_light(const float &x, const float &y,
                                     const float &z, const float &w = 1.0,
                                     const unsigned &index = 0);
  void set_lightPower_index_light(const float &power,
                                  const unsigned &index = 0);
  void set_lightSpecularFactor_index_light(const float &sF,
                                           const unsigned &index = 0);
  void set_lightAmbientFactor_index_light(const float &aF,
                                          const unsigned &index = 0);
  void set_lightSpecularColor_index_light(const float &r, const float &g,
                                          const float &b, const float &a,
                                          const unsigned &index = 0);
  void set_lightColor_red_index_light(const float &red,
                                      const unsigned &index = 0);
  void set_lightColor_green_index_light(const float &green,
                                        const unsigned &index = 0);
  void set_lightColor_blue_index_light(const float &blue,
                                       const unsigned &index = 0);
  /*----------------*/

  /*---PROJACTION---*/
  const unsigned &get_projection() { return projection_; }
  void set_projection(const unsigned &typeProjaction);
  /*----------------*/

  /*---BACKGROUND COLOR---*/
  const std::array<float, RGBA::N> &get_bgColor_setting() { return bgColor_; }
  void set_bgColor(const float &r, const float &g, const float &b,
                   const float &a);
  void set_bgColor(const std::array<float, RGBA::N> &color);
  /*----------------*/

  /*---LIGHT STATUS---*/
  const bool &get_lightStatus() { return lightStatus_; }
  void set_lightStatus(const bool &lightStatus);
  /*----------------*/

  /*---LIGHT SHADE---*/
  const bool &get_lightShade() { return shadding_; }
  void set_lightShade(const bool &lightShade);
  /*----------------*/

  /*---WINDOW SIZE SETTINGS---*/
  const float &get_window_width() { return windowWidth_; }
  const float &get_window_height() { return windowHeight_; }
  void set_window_width(const float &w);
  void set_window_height(const float &h);
  /*----------------*/

  // сохранения в файл настроек
  void save();
  void load();
  void set_default();

 private:
  /*---значение проекции---*/
  unsigned projection_;
  /*---для чтения разрешения экрана---*/
  QRect screenGeometry = QGuiApplication::primaryScreen()->geometry();
  /*---значение отвечающее за включен/выключен свет---*/
  bool lightStatus_;
  /*---тип затенения---*/
  bool shadding_;
  /*---значение данего фона---*/
  std::array<float, RGBA::N> bgColor_;
  /*---значение ширины экрана---*/
  float windowWidth_;
  /*---значение высоты экрана---*/
  float windowHeight_;

  QVector<SettingObject> groupSettings_;
  QVector<LightSource> lightSourses_;
};

}  // namespace s21_3DViewer
