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
  LightSetting()
  {
    setDefault();
  }

  LightSetting(const LightSetting& other)
  {
    *this = other;
  }

  void operator=(const LightSetting& other)
  {
    for (int i = 0; i < 3; ++i)
      m_lightPos[i] = other.m_lightPos[i];

    m_lightPower = other.m_lightPower;
    m_specularFactor = other.m_specularFactor;
    m_ambientFactor = other.m_ambientFactor;

    for (int i = RGBA::RED; i < RGBA::N; ++i)
      m_specularColor[i] = other.m_specularColor[i];

    for (int i = RGBA::RED; i < RGBA::N; ++i)
      m_lightColor[i] = other.m_lightColor[i];
  }

  void setDefault()
  {
    for (int i = 0; i < 3; ++i)
      m_lightPos[i] = DefaultLightSetting::lightPosition[i];

    m_lightPower = DefaultLightSetting::lightPower;
    m_specularFactor = DefaultLightSetting::specularFactor;
    m_ambientFactor = DefaultLightSetting::ambientFactor;

    for (int i = RGBA::RED; i < RGBA::N; ++i)
      m_specularColor[i] = DefaultLightSetting::specularColor[i];

    for (int i = RGBA::RED; i < RGBA::N; ++i)
      m_lightColor[i] = DefaultLightSetting::lightColor[i];
  }

  const float* lightPosition() const
  {
    return m_lightPos;
  }

  float lightPosX() const
  {
    return m_lightPos[0];
  }

  float lightPosY() const
  {
    return m_lightPos[1];
  }

  float lightPosZ() const
  {
    return m_lightPos[2];
  }

  float lightPower() const
  {
    return m_lightPower;
  }

  float lightSpecularFactor() const
  {
    return m_specularFactor;
  }

  float lightAmbientFactor() const
  {
    return m_ambientFactor;
  }

  const float* lightSpecularColor() const
  {
    return m_specularColor;
  }

  float lightSpecularColorRed() const
  {
    return m_specularColor[RGBA::GREEN];
  }

  float lightSpecularColorGreen() const
  {
    return m_specularColor[RGBA::GREEN];
  }

  float lightSpecularColorBlue() const
  {
    return m_specularColor[RGBA::BLUE];
  }

  float lightSpecularColorAlpha() const
  {
    return m_specularColor[RGBA::ALPHA];
  }

  const float* lightColor() const
  {
    return m_lightColor;
  }

  float lightColorRed() const
  {
    return m_lightColor[RGBA::RED];
  }

  float lightColorGreen() const
  {
    return m_lightColor[RGBA::GREEN];
  }

  float lightColorBlue() const
  {
    return m_lightColor[RGBA::BLUE];
  }

  float lightColorAlpha() const
  {
    return m_lightColor[RGBA::ALPHA];
  }

  void setLightPos(float x, float y, float z)
  {
    m_lightPos[0] = x;
    m_lightPos[1] = y;
    m_lightPos[2] = z;
  }

  void setLightPos(const float position[3])
  {
    for (int i = 0; i < 3; ++i)
      m_lightPos[i] = position[i];
  }

  float setlightPosX(float x)
  {
    m_lightPos[0] = x;
  }

  float setlightPosY(float y)
  {
    m_lightPos[1] = y;
  }

  float setlightPosZ(float z)
  {
    m_lightPos[2] = z;
  }

  void setLightPower(float p)
  {
    m_lightPower = p;
  }

  void setLightSpecularFactor(float sF)
  {
    m_specularFactor = sF;
  }

  void setLightAmbientFactor(float aF)
  {
    m_ambientFactor = aF;
  }

  void setLightSpecularColor(float r, float g, float b, float a)
  {
    m_specularColor[RGBA::RED] = r;
    m_specularColor[RGBA::GREEN] = g;
    m_specularColor[RGBA::BLUE] = b;
    m_specularColor[RGBA::ALPHA] = a;
  }

  void setLightSpecularColor(const float color[RGBA::N])
  {
    for (int i = 0; i < RGBA::N; ++i)
      m_specularColor[i] = color[i];
  }

  void setLightSpecularColorRed(float r)
  {
    m_specularColor[RGBA::RED] = r;
  }

  void setLightSpecularColorGreen(float g)
  {
    m_specularColor[RGBA::GREEN] = g;
  }

  void setLightSpecularColorBlue(float b)
  {
    m_specularColor[RGBA::BLUE] = b;
  }

  void setLightSpecularColorAlpha(float a)
  {
    m_specularColor[RGBA::ALPHA] = a;
  }

  void setLightColor(float r, float g, float b, float a)
  {
    m_lightColor[RGBA::RED] = r;
    m_lightColor[RGBA::GREEN] = g;
    m_lightColor[RGBA::BLUE] = b;
    m_lightColor[RGBA::ALPHA] = a;
  }

  void setLightColor(const float color[RGBA::N])
  {
    for (int i = 0; i < RGBA::N; ++i)
      m_lightColor[i] = color[i];
  }

  void setLightColorRed(float r)
  {
    m_lightColor[RGBA::RED] = r;
  }

  void setLightColorGreen(float g)
  {
    m_lightColor[RGBA::GREEN] = g;
  }

  void setLightColorBlue(float b)
  {
    m_lightColor[RGBA::BLUE] = b;
  }

  void setLightColorAlpha(float a)
  {
    m_lightColor[RGBA::ALPHA] = a;
  }

  // сохранения в файл настроек
  void save(unsigned num)
  {
    QString pathToConfigFile = QCoreApplication::applicationDirPath() + "/settings/";

    if (!QDir(pathToConfigFile).exists())
      QDir().mkdir(pathToConfigFile);

    QString filename = pathToConfigFile + QString("LightSetting") + QString::number(num) + QString(".conf");
    std::ofstream tgt(filename.toStdString());

    if (!tgt.is_open())
      return;

    setlocale(LC_ALL, "en_US.UTF-8");

    tgt << TypeLightSetting::kLightPos;
    for (int i = 0; i < 3; ++i)
      tgt << " " << m_lightPos[i];
    tgt << std::endl;

    tgt << TypeLightSetting::kLightPower << " " << m_lightPower << std::endl;
    tgt << TypeLightSetting::kLightSpecularFactor << " " << m_specularFactor << std::endl;
    tgt << TypeLightSetting::kLightAmbientFactor << " " << m_ambientFactor << std::endl;

    tgt << TypeLightSetting::kLightSpecularColor;
    for (int i = RGBA::RED; i < RGBA::N; ++i)
      tgt << " " << m_specularColor[i];
    tgt << std::endl;

    tgt << TypeLightSetting::kLightColor;
    for (int i = RGBA::RED; i < RGBA::N; ++i)
      tgt << " " << m_lightColor[i];
    tgt << std::endl;
  }

  // загрузка из файла настроек
  void load(unsigned num)
  {
    QString pathToConfigFile = QCoreApplication::applicationDirPath() + "/settings/";

    if (!QDir(pathToConfigFile).exists())
      return;

    QString filename = pathToConfigFile + QString("LightSetting") + QString::number(num) + QString(".conf");
    std::ifstream src(filename.toStdString());

    if (!src.is_open())
      return;

    setlocale(LC_ALL, "en_US.UTF-8");

    while (src)
    {
      int type{};
      src >> type;

      switch (type)
      {
        case TypeLightSetting::kLightPos: {
          for (int i = 0; i < 3; ++i)
            src >> m_lightPos[i];
          break;
        }

        case TypeLightSetting::kLightPower: {
          src >> m_lightPower;
          break;
        }

        case TypeLightSetting::kLightSpecularFactor: {
          src >> m_specularFactor;
          break;
        }

        case TypeLightSetting::kLightAmbientFactor: {
          src >> m_ambientFactor;
          break;
        }

        case TypeLightSetting::kLightSpecularColor: {
          for (int i = RGBA::RED; i < RGBA::N; ++i)
            src >> m_specularColor[i];
          break;
        }

        case TypeLightSetting::kLightColor: {
          for (int i = RGBA::RED; i < RGBA::N; ++i)
            src >> m_lightColor[i];
          break;
        }

        default:
          break;
      }
    }
  }

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
