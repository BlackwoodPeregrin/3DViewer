#ifndef GROUPSETTING_H
#define GROUPSETTING_H

#include "drawSetting.h"
#include "lightSetting.h"
#include "defaultMainSetting.h"

namespace s21_3DViewer
{
class GroupSettings
{
public:
  GroupSettings();
  GroupSettings(const GroupSettings& other);

  ~GroupSettings() = default;

  void operator=(const GroupSettings& other);

  void setDefault();

  void addDrawSettingToGroup();
  void addLightSettingToGroup();

  /*--- Draw Setting Group ---*/

  /*--- getters ---*/
  bool lineType_index(unsigned index = 0) const;
  float lineSize_index(unsigned index = 0) const;
  const float* lineColor_index(unsigned index = 0) const;
  float lineColorRed_index(unsigned index = 0) const;
  float lineColorGreen_index(unsigned index = 0) const;
  float lineColorBlueindex(unsigned index = 0) const;
  float lineColorAlpha_index(unsigned index = 0) const;
  unsigned vertType_index(unsigned index = 0) const;
  float vertSize_index(unsigned index = 0) const;
  const float* vertColor_index(unsigned index = 0) const;
  float vertColorRed_index(unsigned index = 0) const;
  float vertColorGreen_index(unsigned index = 0) const;
  float vertColorBlue_index(unsigned index = 0) const;
  float vertColorAlpha_index(unsigned index = 0) const;
  const float* surfacesColor_index(unsigned index = 0) const;
  float surfacesColorRed_index(unsigned index = 0) const;
  float surfacesColorGreen_index(unsigned index = 0) const;
  float surfacesColorBlue_index(unsigned index = 0) const;
  float surfacesColorAlpha_index(unsigned index = 0) const;
  unsigned drawType_index(unsigned index = 0) const;

  /*--- setters ---*/
  void setLineType_index(bool lineType, unsigned index = 0);
  void setLineSize_index(float lineSize, unsigned index = 0);
  void setLineColor_index(float r, float g, float b, float a, unsigned index = 0);
  void setLineColor_index(const float color[RGBA::N], unsigned index = 0);
  void setVertType_index(unsigned vertType, unsigned index = 0);
  void setVertSize_index(float vertSize, unsigned index = 0);
  void setVertColor_index(float r, float g, float b, float a, unsigned index = 0);
  void setVertColor_index(const float color[RGBA::N], unsigned index = 0);
  void setSurfaceColor_index(float r, float g, float b, float a, unsigned index = 0);
  void setSurfaceColor_index(const float color[RGBA::N], unsigned index = 0);
  void setDrawType_index(unsigned drawType, unsigned index = 0);

  /*--- Light Setting Group ---*/

  /*--- getters ---*/
  const float* lightPosition_index(unsigned index = 0) const;
  float lightPositionX_index(unsigned index = 0) const;
  float lightPosY_index(unsigned index = 0) const;
  float lightPosZ_index(unsigned index = 0) const;
  float lightPower_index(unsigned index = 0) const;
  float lightSpecularFactor_index(unsigned index = 0) const;
  float lightAmbientFactor_index(unsigned index = 0) const;
  const float* lightSpecularColor_index(unsigned index = 0) const;
  float lightSpecularColorRed_index(unsigned index = 0) const;
  float lightSpecularColorGreen_index(unsigned index = 0) const;
  float lightSpecularColorBlue_index(unsigned index = 0) const;
  float lightSpecularColorAlpha_index(unsigned index = 0) const;
  const float* lightColor_index(unsigned index = 0) const;
  float lightColorRed_index(unsigned index = 0) const;
  float lightColorGreen_index(unsigned index = 0) const;
  float lightColorBlue_index(unsigned index = 0) const;
  float lightColorAlpha_index(unsigned index = 0) const;

  /*--- setters ---*/
  void setLightPosition_index(float x, float y, float z, unsigned index = 0);
  void setLightPosition_index(const float position[3], unsigned index = 0);
  void setLightPositionX_index(float x, unsigned index = 0);
  void setLightPositionY_index(float y, unsigned index = 0);
  void setLightPositionZ_index(float z, unsigned index = 0);
  void setLightPower_index(float p, unsigned index = 0);
  void setLightSpecularFactor_index(float sF, unsigned index = 0);
  void setLightAmbientFactor_index(float aF, unsigned index = 0);
  void setLightSpecularColor_index(float r, float g, float b, float a, unsigned index = 0);
  void setLightSpecularColor_index(const float color[RGBA::N], unsigned index = 0);
  void setLightSpecularColorRed_index(float r, unsigned index = 0);
  void setLightSpecularColorGreen_index(float g, unsigned index = 0);
  void setLightSpecularColorBlue_index(float b, unsigned index = 0);
  void setLightSpecularColorAlpha_index(float a, unsigned index = 0);
  void setLightColor_index(float r, float g, float b, float a, unsigned index = 0);
  void setLightColor_index(const float color[RGBA::N], unsigned index = 0);
  void setLightColorRed_index(float r, unsigned index = 0);
  void setLightColorGreen_index(float g, unsigned index = 0);
  void setLightColorBlue_index(float b, unsigned index = 0);
  void setLightColorAlpha_index(float a, unsigned index = 0);

  /*--- Main Setting Group ---*/

  /*--- getters ---*/
  bool projection() const;
  bool lightStatus() const;
  bool lightShade() const;
  const float* bgColor() const;
  float bgColorRed() const;
  float bgColorGreen() const;
  float bgColorBlue() const;
  float bgColorAlpha() const;
  float wScreen() const;
  float hScreen() const;

  /*--- setters ---*/
  void setProjection(bool typeProjaction);
  void setLightStatus(bool lightStatus);
  void setLightShade(bool lightShade);
  void setBgColor(float r, float g, float b, float a);
  void setBgColor(const float color[RGBA::N]);
  void setBgColorRed(float r);
  void setBgColorGreen(float g);
  void setBgColorBlue(float b);
  void setBgColorAlpha(float a);
  void setWScreen(float w);
  void setHScreen(float h);

  /*--- save setting to config file---*/
  void save();

  /*--- load setting from config file---*/
  void load();

private:
  bool m_projection;
  bool m_lightStatus;
  bool m_shadding;
  float m_bgColor[RGBA::N];
  float m_wScreen;
  float m_hScreen;

  QVector<DrawSetting> m_drawSetting;
  QVector<LightSetting> m_lightSetting;
};

}  // namespace s21_3DViewer

#endif  // GROUPSETTING_H
