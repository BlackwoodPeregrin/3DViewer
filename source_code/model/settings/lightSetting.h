#ifndef LIGHTSETTING_H
#define LIGHTSETTING_H

#include "defaultLightSetting.h"

#include <QCoreApplication>
#include <QString>
#include <QDir>
#include <fstream>

namespace s21_3DViewer
{
class LightSetting
{
public:
  LightSetting();

  LightSetting(const LightSetting& other);

  void operator=(const LightSetting& other);

  void setDefault();

  // setters
  const float* lightPosition() const;
  float lightPosX() const;
  float lightPosY() const;
  float lightPosZ() const;
  float lightPower() const;
  float lightSpecularFactor() const;
  float lightAmbientFactor() const;
  const float* lightSpecularColor() const;
  float lightSpecularColorRed() const;
  float lightSpecularColorGreen() const;
  float lightSpecularColorBlue() const;
  float lightSpecularColorAlpha() const;
  const float* lightColor() const;
  float lightColorRed() const;
  float lightColorGreen() const;
  float lightColorBlue() const;
  float lightColorAlpha() const;

  // getters
  void setLightPos(float x, float y, float z);
  void setLightPos(const float position[3]);
  float setlightPosX(float x);
  float setlightPosY(float y);
  float setlightPosZ(float z);
  void setLightPower(float p);
  void setLightSpecularFactor(float sF);
  void setLightAmbientFactor(float aF);
  void setLightSpecularColor(float r, float g, float b, float a);
  void setLightSpecularColor(const float color[RGBA::N]);
  void setLightSpecularColorRed(float r);
  void setLightSpecularColorGreen(float g);
  void setLightSpecularColorBlue(float b);
  void setLightSpecularColorAlpha(float a);
  void setLightColor(float r, float g, float b, float a);
  void setLightColor(const float color[RGBA::N]);
  void setLightColorRed(float r);
  void setLightColorGreen(float g);
  void setLightColorBlue(float b);
  void setLightColorAlpha(float a);

  // save setting to config file
  void save(unsigned num);

  // load setting from config file
  void load(unsigned num);

private:
  float m_lightPos[3];
  float m_lightPower;
  float m_specularFactor;
  float m_ambientFactor;
  float m_specularColor[RGBA::N];
  float m_lightColor[RGBA::N];
};

}  // namespace s21_3DViewer

#endif  // LIGHTSETTING_H
