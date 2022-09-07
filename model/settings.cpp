#include "settings.h"

#include <QDir>

namespace s21_3DViewer {

std::array<float, RGBA::N> stoFArray(const std::string &src) {
  std::array<float, RGBA::N> res{};
  int off_a{}, off_b = src.find(' ', off_a);
  for (int i{}; i < 4; i++) {
    res[i] = stof(src.substr(off_a, off_b - off_a));
    off_a = src.find_first_not_of(' ', off_b);
    off_b = src.find(' ', off_a);
  }
  return res;
}

bool is_rgbarray_within_limits(const std::array<float, N> &src) {
  for (float i : src) {
    if (i < 0.0f || i > 1.0f) {
      return false;
    }
  }
  return true;
}

bool is_colorset_within_limits(const float &r, const float &g, const float &b,
                               const float &a) {
  for (float i : {r, g, b, a}) {
    if (i < 0.0f || i > 1.0f) {
      return false;
    }
  }
  return true;
}

/*-------------------CLASS SettingObject----------------------*/

SettingObject::SettingObject() { set_default(); }

void SettingObject::save(unsigned num) {
  QString config_file = QCoreApplication::applicationDirPath() + "/settings/";
  if (!QDir(config_file).exists()) {
    QDir().mkdir(config_file);
  }
  std::string filename = config_file.toStdString() + "SettingObject" +
                         std::to_string(num) + ".conf";
  std::fstream tgt(filename, std::fstream::out | std::fstream::trunc);
  if (tgt.is_open()) {
    setlocale(LC_ALL, "en_US.UTF-8");
    tgt << "line_type_ " << line_type_ << std::endl;
    tgt << "line_size_ " << line_size_ << std::endl;
    tgt << "vert_type_ " << vert_type_ << std::endl;
    tgt << "vert_size_ " << vert_size_ << std::endl;
    tgt << "draw_type_ " << draw_type_ << std::endl;
    tgt << "pathToTexture_ " << pathToTexture_ << std::endl;

    tgt << "line_color_";
    for (int i{}; i < 4; i++) tgt << ' ' << line_color_[i];
    tgt << std::endl;
    tgt << "vert_color_";
    for (int i{}; i < 4; i++) tgt << ' ' << vert_color_[i];
    tgt << std::endl;
    tgt << "surfaces_color_";
    for (int i{}; i < 4; i++) tgt << ' ' << surfaces_color_[i];
    tgt << std::endl;
    tgt.close();
  }
}

void SettingObject::load(unsigned num) {
  set_default();
  QString config_file = QCoreApplication::applicationDirPath() + "/settings/";
  if (QDir(config_file).exists()) {
    std::string filename = config_file.toStdString() + "SettingObject" +
                           std::to_string(num) + ".conf";
    std::fstream src(filename, std::fstream::in);
    if (src.is_open()) {
      setlocale(LC_ALL, "en_US.UTF-8");
      std::string line{}, opt{}, val{};
      while (src) {
        std::getline(src, line);
        int pos = line.find(' ');
        if (pos != -1) {
          opt = line.substr(0, pos);
          val = line.substr(pos + 1);
          if (opt == "line_type_") {
            set_line_type(stoi(val));
          } else if (opt == "line_size_") {
            set_line_size(stof(val));
          } else if (opt == "vert_type_") {
            set_vert_type(stoi(val));
          } else if (opt == "vert_size_") {
            set_vert_size(stof(val));
          } else if (opt == "draw_type_") {
            set_draw_type(stoi(val));
          } else if (opt == "line_color_") {
            set_line_color(stoFArray(val));
          } else if (opt == "vert_color_") {
            set_vert_color(stoFArray(val));
          } else if (opt == "surfaces_color_") {
            set_surfaces_color(stoFArray(val));
          } else if (opt == "pathToTexture_") {
            set_texture_path(val);
          }
        }
      }
      src.close();
    }
  }
}

void SettingObject::set_default() {
  line_type_ = kDefaultLineType;
  line_size_ = kDefaultLineSize;
  line_color_ = kDefaultLineColor;
  vert_type_ = kDefaultVertType;
  vert_size_ = kDefaultVertSize;
  vert_color_ = kDefaultVertColor;
  surfaces_color_ = kDefaultSurfacesColor;
  draw_type_ = kDefaultDrawType;
  pathToTexture_ = "";
}

void SettingObject::set_line_type(const unsigned &lineType) {
  line_type_ = lineType <= lineType::Dashed ? lineType : kDefaultLineType;
}

void SettingObject::set_line_size(const float &lineSize) {
  line_size_ = lineSize <= kMaxLineSize ? lineSize : kDefaultLineSize;
}

void SettingObject::set_line_color(const float &r, const float &g,
                                   const float &b, const float &a) {
  if (is_colorset_within_limits(r, g, b, a)) {
    line_color_ = {r, g, b, a};
  } else {
    line_color_ = kDefaultLineColor;
  }
}

void SettingObject::set_line_color(const std::array<float, N> &color) {
  if (is_rgbarray_within_limits(color)) {
    line_color_ = color;
  } else {
    line_color_ = kDefaultLineColor;
  }
}

void SettingObject::set_vert_type(const unsigned &vertType) {
  vert_type_ = vertType <= vertType::Square ? vertType : kDefaultVertType;
}

void SettingObject::set_vert_size(const float &vertSize) {
  vert_size_ = vertSize <= kMaxVertSize ? vertSize : kDefaultVertSize;
}

void SettingObject::set_vert_color(const float &r, const float &g,
                                   const float &b, const float &a) {
  if (is_colorset_within_limits(r, g, b, a)) {
    vert_color_ = {r, g, b, a};
  } else {
    vert_color_ = kDefaultVertColor;
  }
}

void SettingObject::set_vert_color(const std::array<float, N> &color) {
  if (is_rgbarray_within_limits(color)) {
    vert_color_ = color;
  } else {
    vert_color_ = kDefaultVertColor;
  }
}

void SettingObject::set_surfaces_color(const float &r, const float &g,
                                       const float &b, const float &a) {
  if (is_colorset_within_limits(r, g, b, a)) {
    surfaces_color_ = {r, g, b, a};
  } else {
    surfaces_color_ = kDefaultSurfacesColor;
  }
}

void SettingObject::set_surfaces_color(const std::array<float, N> &color) {
  if (is_rgbarray_within_limits(color)) {
    surfaces_color_ = color;
  } else {
    surfaces_color_ = kDefaultSurfacesColor;
  }
}

void SettingObject::set_draw_type(const unsigned &drawType) {
  draw_type_ = drawType <= typeDraw::Triangles ? drawType : kDefaultDrawType;
}

void SettingObject::set_texture_path(const std::string &pathToTexture) {
  pathToTexture_ = pathToTexture;
}

/*----------------------------------------------------------*/

/*-------------------CLASS LIGHTSOURCE----------------------*/

LightSource::LightSource() { set_default(); }

void LightSource::save(unsigned num) {
  QString config_file = QCoreApplication::applicationDirPath() + "/settings/";
  if (!QDir(config_file).exists()) {
    QDir().mkdir(config_file);
  }
  std::string filename =
      config_file.toStdString() + "LightSource" + std::to_string(num) + ".conf";
  std::fstream tgt(filename, std::fstream::out | std::fstream::trunc);
  if (tgt.is_open()) {
    setlocale(LC_ALL, "en_US.UTF-8");
    tgt << "light_power_ " << light_power_ << std::endl;
    tgt << "specular_factor_ " << specular_factor_ << std::endl;
    tgt << "ambient_factor_ " << ambient_factor_ << std::endl;

    tgt << "light_position_";
    for (int i{}; i < 4; i++) tgt << ' ' << light_position_[i];
    tgt << std::endl;
    tgt << "specular_color_";
    for (int i{}; i < 4; i++) tgt << ' ' << specular_color_[i];
    tgt << std::endl;
    tgt << "light_color_red_ " << light_color_red_ << std::endl;
    tgt << "light_color_green_ " << light_color_green_ << std::endl;
    tgt << "light_color_blue_ " << light_color_blue_ << std::endl;
    tgt.close();
  }
}

void LightSource::load(unsigned num) {
  set_default();
  QString config_file = QCoreApplication::applicationDirPath() + "/settings/";
  if (QDir(config_file).exists()) {
    std::string filename = config_file.toStdString() + "LightSource" +
                           std::to_string(num) + ".conf";
    std::fstream src(filename, std::fstream::in);
    if (src.is_open()) {
      setlocale(LC_ALL, "en_US.UTF-8");
      std::string line{}, opt{}, val{};
      while (src) {
        std::getline(src, line);
        int pos = line.find(' ');
        if (pos != -1) {
          opt = line.substr(0, pos);
          val = line.substr(pos + 1);
          if (opt == "light_power_") {
            set_light_power(stof(val));
          } else if (opt == "specular_factor_") {
            set_light_specular_factor(stof(val));
          } else if (opt == "ambient_factor_") {
            set_light_ambient_factor(stof(val));
          } else if (opt == "light_position_") {
            set_light_position(stoFArray(val));
          } else if (opt == "specular_color_") {
            set_light_specular_color(stoFArray(val));
          } else if (opt == "light_color_red_") {
            set_light_color_red(stof(val));
          } else if (opt == "light_color_green_") {
            set_light_color_green(stof(val));
          } else if (opt == "light_color_blue_") {
            set_light_color_blue(stof(val));
          }
        }
      }
      src.close();
    }
  }
}

void LightSource::set_default() {
  light_position_ = kDefaultLightPosition_;
  light_power_ = kDefaultLightPower;
  specular_factor_ = kDefaultSpecularFactor;
  ambient_factor_ = kDefaultAmbientFactor;
  specular_color_ = kDefaultSpecularColor;
  light_color_red_ = kDefaultLightColorRed;
  light_color_green_ = kDefaultLightColorGreen;
  light_color_blue_ = kDefaultLightColorBLue;
}

void LightSource::set_light_position(const float &x, const float &y,
                                     const float &z, const float &w) {
  light_position_ = {x, y, z, w};
}

void LightSource::set_light_position(std::array<float, 4> position) {
  light_position_ = position;
}

void LightSource::set_light_power(const float &lightPower) {
  light_power_ = lightPower <= kMaxLightPower ? lightPower : kDefaultLightPower;
}

void LightSource::set_light_specular_factor(const float &sF) {
  specular_factor_ =
      sF <= kMaxLightSpecularFactor ? sF : kDefaultSpecularFactor;
}

void LightSource::set_light_ambient_factor(const float &aF) {
  ambient_factor_ = aF <= kMaxLightAmbientFactor ? aF : kDefaultAmbientFactor;
}

void LightSource::set_light_specular_color(const float &r, const float &g,
                                           const float &b, const float &a) {
  if (is_colorset_within_limits(r, g, b, a)) {
    specular_color_ = {r, g, b, a};
  } else {
    specular_color_ = kDefaultSpecularColor;
  }
}

void LightSource::set_light_specular_color(const std::array<float, N> &color) {
  if (is_rgbarray_within_limits(color)) {
    specular_color_ = color;
  } else {
    specular_color_ = kDefaultSpecularColor;
  }
}

void LightSource::set_light_color_red(const float &red) {
  light_color_red_ = red;
}

void LightSource::set_light_color_green(const float &green) {
  light_color_green_ = green;
}

void LightSource::set_light_color_blue(const float &blue) {
  light_color_blue_ = blue;
}

/*----------------------------------------------------------*/

/*-------------------CLASS GROUPSETTINGS--------------------*/

GroupSettings::GroupSettings() { load(); }

GroupSettings::GroupSettings(const GroupSettings &group) { *this = group; }

GroupSettings::~GroupSettings() {}

void GroupSettings::operator=(const GroupSettings &group) {
  projection_ = group.projection_;
  lightStatus_ = group.lightStatus_;
  bgColor_ = group.bgColor_;
  windowWidth_ = group.windowWidth_;
  windowHeight_ = group.windowHeight_;
  groupSettings_ = group.groupSettings_;
  lightSourses_ = group.lightSourses_;
  shadding_ = group.shadding_;
}

void GroupSettings::add_settings_to_group() {
  groupSettings_.append(SettingObject());
}

void GroupSettings::add_lightSource_to_group() {
  lightSourses_.append(LightSource());
}

void GroupSettings::set_lineType_index_setting(const unsigned &lineType,
                                               const unsigned &index) {
  return groupSettings_[index].set_line_type(lineType);
}

void GroupSettings::set_lineSize_index_setting(const float &lineSize,
                                               const unsigned &index) {
  groupSettings_[index].set_line_size(lineSize);
}

void GroupSettings::set_lineColor_index_setting(const float &r, const float &g,
                                                const float &b, const float &a,
                                                const unsigned &index) {
  groupSettings_[index].set_line_color(r, g, b, a);
}

void GroupSettings::set_vertType_index_setting(const unsigned &vertType,
                                               const unsigned &index) {
  return groupSettings_[index].set_vert_type(vertType);
}

void GroupSettings::set_vertSize_index_setting(const float &vertSize,
                                               const unsigned &index) {
  groupSettings_[index].set_vert_size(vertSize);
}

void GroupSettings::set_vertColor_index_setting(const float &r, const float &g,
                                                const float &b, const float &a,
                                                const unsigned &index) {
  groupSettings_[index].set_vert_color(r, g, b, a);
}

void GroupSettings::set_surfaceColor_index_setting(const float &r,
                                                   const float &g,
                                                   const float &b,
                                                   const float &a,
                                                   const unsigned &index) {
  groupSettings_[index].set_surfaces_color(r, g, b, a);
}

void GroupSettings::set_drawType_index_setting(const unsigned &drawType,
                                               const unsigned &index) {
  return groupSettings_[index].set_draw_type(drawType);
}

void GroupSettings::set_lightPosition_index_light(const float &x,
                                                  const float &y,
                                                  const float &z,
                                                  const float &w,
                                                  const unsigned &index) {
  lightSourses_[index].set_light_position(x, y, z, w);
}

void GroupSettings::set_lightPower_index_light(const float &power,
                                               const unsigned &index) {
  lightSourses_[index].set_light_power(power);
}

void GroupSettings::set_lightSpecularFactor_index_light(const float &sF,
                                                        const unsigned &index) {
  lightSourses_[index].set_light_specular_factor(sF);
}

void GroupSettings::set_lightAmbientFactor_index_light(const float &aF,
                                                       const unsigned &index) {
  lightSourses_[index].set_light_ambient_factor(aF);
}

void GroupSettings::set_lightSpecularColor_index_light(const float &r,
                                                       const float &g,
                                                       const float &b,
                                                       const float &a,
                                                       const unsigned &index) {
  lightSourses_[index].set_light_specular_color(r, g, b, a);
}

void GroupSettings::set_lightColor_red_index_light(const float &red,
                                                   const unsigned &index) {
  lightSourses_[index].set_light_color_red(red);
}

void GroupSettings::set_lightColor_green_index_light(const float &green,
                                                     const unsigned &index) {
  lightSourses_[index].set_light_color_green(green);
}

void GroupSettings::set_lightColor_blue_index_light(const float &blue,
                                                    const unsigned &index) {
  lightSourses_[index].set_light_color_blue(blue);
}

void GroupSettings::set_projection(const unsigned &typeProjaction) {
  projection_ =
      typeProjaction <= projType::Central ? typeProjaction : kDefaultProjection;
}

void GroupSettings::set_bgColor(const float &r, const float &g, const float &b,
                                const float &a) {
  if (is_colorset_within_limits(r, g, b, a)) {
    bgColor_ = {r, g, b, a};
  } else {
    bgColor_ = kDefaultBgColor;
  }
}

void GroupSettings::set_bgColor(const std::array<float, N> &color) {
  if (is_rgbarray_within_limits(color)) {
    bgColor_ = color;
  } else {
    bgColor_ = kDefaultBgColor;
  }
}

void GroupSettings::set_lightStatus(const bool &lightStatus) {
  lightStatus_ = lightStatus;
}

void GroupSettings::set_lightShade(const bool &lightShade) {
  shadding_ = lightShade;
}

void GroupSettings::set_window_width(const float &w) {
  windowWidth_ = w <= screenGeometry.width() ? w : kDefaultWidthScreen;
}

void GroupSettings::set_window_height(const float &h) {
  windowHeight_ = h <= screenGeometry.height() ? h : kDefaultHeightScreen;
}

void GroupSettings::save() {
  QString config_file = QCoreApplication::applicationDirPath() + "/settings/";
  if (!QDir(config_file).exists()) {
    QDir().mkdir(config_file);
  }
  std::string filename = config_file.toStdString() + "GroupSettings.conf";
  std::fstream tgt(filename, std::fstream::out | std::fstream::trunc);
  if (tgt.is_open()) {
    setlocale(LC_ALL, "en_US.UTF-8");
    tgt << "projection_ " << projection_ << std::endl;
    tgt << "lightStatus_ " << lightStatus_ << std::endl;
    tgt << "lightShade_ " << shadding_ << std::endl;
    tgt << "windowWidth_ " << windowWidth_ << std::endl;
    tgt << "windowHeight_ " << windowHeight_ << std::endl;

    tgt << "bgColor_";
    for (int i{}; i < 4; i++) tgt << ' ' << bgColor_[i];
    tgt << std::endl;

    tgt << "num_group_settings " << groupSettings_.size() << std::endl;
    tgt << "num_light_sourses " << lightSourses_.size() << std::endl;
    tgt.close();

    for (unsigned i{}; i < groupSettings_.size(); i++)
      groupSettings_[i].save(i);
    for (unsigned i{}; i < lightSourses_.size(); i++) lightSourses_[i].save(i);
  }
}

void GroupSettings::load() {
  set_default();
  QString config_file = QCoreApplication::applicationDirPath() + "/settings/";
  if (QDir(config_file).exists()) {
    std::string filename = config_file.toStdString() + "GroupSettings.conf";
    std::fstream src(filename, std::fstream::in);
    if (src.is_open()) {
      setlocale(LC_ALL, "en_US.UTF-8");
      unsigned num_group_settings(1), num_light_sources(1);
      std::string line{}, opt{}, val{};
      while (src) {
        std::getline(src, line);
        int pos = line.find(' ');
        if (pos != -1) {
          opt = line.substr(0, pos);
          val = line.substr(pos + 1);
          if (opt == "projection_") {
            set_projection(stoi(val));
          } else if (opt == "lightStatus_") {
            set_lightStatus(stoi(val));
          } else if (opt == "lightShade_") {
            set_lightShade(stoi(val));
          } else if (opt == "windowWidth_") {
            windowWidth_ = stoi(val);
          } else if (opt == "windowHeight_") {
            windowHeight_ = stoi(val);
          } else if (opt == "bgColor_") {
            set_bgColor(stoFArray(val));
          } else if (opt == "num_group_settings") {
            num_group_settings = stoi(val);  // проверки пределов?
          } else if (opt == "num_light_sourses") {
            num_light_sources = stoi(val);
          }
        }
      }
      src.close();
      for (unsigned i{}; i < num_group_settings && i < groupSettings_.size();
           i++)
        groupSettings_[i].load(i);
      for (unsigned i{}; i < num_light_sources && i < lightSourses_.size(); i++)
        lightSourses_[i].load(i);
    }
  }
}

void GroupSettings::set_default() {
  projection_ = kDefaultProjection;
  shadding_ = kDefaultLightShade;
  lightStatus_ = kDefaultLightStatus;
  bgColor_ = kDefaultBgColor;
  windowWidth_ = screenGeometry.width() * kDefaultWidthScreen;
  windowHeight_ = screenGeometry.height() * kDefaultHeightScreen;
  groupSettings_.append(SettingObject());
  lightSourses_.append(LightSource());
}

/*----------------------------------------------------------*/

}  // namespace s21_3DViewer
