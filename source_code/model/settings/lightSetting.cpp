#include "lightSetting.h"

namespace s21_3DViewer
{
LightSetting::LightSetting()
{
  setDefault();
}

LightSetting::LightSetting(const LightSetting& other)
{
  *this = other;
}

void LightSetting::operator=(const LightSetting& other)
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

void LightSetting::setDefault()
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

const float* LightSetting::lightPosition() const
{
  return m_lightPos;
}

float LightSetting::lightPosX() const
{
  return m_lightPos[0];
}

float LightSetting::lightPosY() const
{
  return m_lightPos[1];
}

float LightSetting::lightPosZ() const
{
  return m_lightPos[2];
}

float LightSetting::lightPower() const
{
  return m_lightPower;
}

float LightSetting::lightSpecularFactor() const
{
  return m_specularFactor;
}

float LightSetting::lightAmbientFactor() const
{
  return m_ambientFactor;
}

const float* LightSetting::lightSpecularColor() const
{
  return m_specularColor;
}

float LightSetting::lightSpecularColorRed() const
{
  return m_specularColor[RGBA::GREEN];
}

float LightSetting::lightSpecularColorGreen() const
{
  return m_specularColor[RGBA::GREEN];
}

float LightSetting::lightSpecularColorBlue() const
{
  return m_specularColor[RGBA::BLUE];
}

float LightSetting::lightSpecularColorAlpha() const
{
  return m_specularColor[RGBA::ALPHA];
}

const float* LightSetting::lightColor() const
{
  return m_lightColor;
}

float LightSetting::lightColorRed() const
{
  return m_lightColor[RGBA::RED];
}

float LightSetting::lightColorGreen() const
{
  return m_lightColor[RGBA::GREEN];
}

float LightSetting::lightColorBlue() const
{
  return m_lightColor[RGBA::BLUE];
}

float LightSetting::lightColorAlpha() const
{
  return m_lightColor[RGBA::ALPHA];
}

void LightSetting::setLightPos(float x, float y, float z)
{
  m_lightPos[0] = x;
  m_lightPos[1] = y;
  m_lightPos[2] = z;
}

void LightSetting::setLightPos(const float position[])
{
  for (int i = 0; i < 3; ++i)
    m_lightPos[i] = position[i];
}

float LightSetting::setlightPosX(float x)
{
  m_lightPos[0] = x;
}

float LightSetting::setlightPosY(float y)
{
  m_lightPos[1] = y;
}

float LightSetting::setlightPosZ(float z)
{
  m_lightPos[2] = z;
}

void LightSetting::setLightPower(float p)
{
  m_lightPower = p;
}

void LightSetting::setLightSpecularFactor(float sF)
{
  m_specularFactor = sF;
}

void LightSetting::setLightAmbientFactor(float aF)
{
  m_ambientFactor = aF;
}

void LightSetting::setLightSpecularColor(float r, float g, float b, float a)
{
  m_specularColor[RGBA::RED] = r;
  m_specularColor[RGBA::GREEN] = g;
  m_specularColor[RGBA::BLUE] = b;
  m_specularColor[RGBA::ALPHA] = a;
}

void LightSetting::setLightSpecularColor(const float color[])
{
  for (int i = 0; i < RGBA::N; ++i)
    m_specularColor[i] = color[i];
}

void LightSetting::setLightSpecularColorRed(float r)
{
  m_specularColor[RGBA::RED] = r;
}

void LightSetting::setLightSpecularColorGreen(float g)
{
  m_specularColor[RGBA::GREEN] = g;
}

void LightSetting::setLightSpecularColorBlue(float b)
{
  m_specularColor[RGBA::BLUE] = b;
}

void LightSetting::setLightSpecularColorAlpha(float a)
{
  m_specularColor[RGBA::ALPHA] = a;
}

void LightSetting::setLightColor(float r, float g, float b, float a)
{
  m_lightColor[RGBA::RED] = r;
  m_lightColor[RGBA::GREEN] = g;
  m_lightColor[RGBA::BLUE] = b;
  m_lightColor[RGBA::ALPHA] = a;
}

void LightSetting::setLightColor(const float color[])
{
  for (int i = 0; i < RGBA::N; ++i)
    m_lightColor[i] = color[i];
}

void LightSetting::setLightColorRed(float r)
{
  m_lightColor[RGBA::RED] = r;
}

void LightSetting::setLightColorGreen(float g)
{
  m_lightColor[RGBA::GREEN] = g;
}

void LightSetting::setLightColorBlue(float b)
{
  m_lightColor[RGBA::BLUE] = b;
}

void LightSetting::setLightColorAlpha(float a)
{
  m_lightColor[RGBA::ALPHA] = a;
}

void LightSetting::save(unsigned num)
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

void LightSetting::load(unsigned num)
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

}  // namespace s21_3DViewer
