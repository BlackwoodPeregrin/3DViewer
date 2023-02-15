#include "groupSetting.h"

namespace s21_3DViewer
{
GroupSettings::GroupSettings()
{
  setDefault();
}

GroupSettings::GroupSettings(const GroupSettings& other)
{
  *this = other;
}

void GroupSettings::operator=(const GroupSettings& other)
{
  m_projection = other.m_projection;
  m_lightStatus = other.m_lightStatus;
  m_shadding = other.m_shadding;

  for (int i = RGBA::RED; i < RGBA::N; ++i)
    m_bgColor[i] = other.m_bgColor[i];

  m_wScreen = other.m_wScreen;
  m_hScreen = other.m_hScreen;
  m_drawSetting = other.m_drawSetting;
  m_lightSetting = other.m_lightSetting;
}

void GroupSettings::setDefault()
{
  m_projection = DefaultMainSetting::projection;
  m_lightStatus = DefaultMainSetting::lightStatus;
  m_shadding = DefaultMainSetting::shadding;

  for (int i = RGBA::RED; i < RGBA::N; ++i)
    m_bgColor[i] = DefaultMainSetting::bgColor[i];

  m_wScreen = QGuiApplication::primaryScreen()->geometry().width() * DefaultMainSetting::wScreen;
  m_hScreen = QGuiApplication::primaryScreen()->geometry().height() * DefaultMainSetting::hScreen;

  // по дефолту изначально есть по одной настройки для отрисовки модели и одного ичтояника света
  m_drawSetting.clear();
  m_drawSetting.push_back(DrawSetting());
  m_lightSetting.clear();
  m_lightSetting.push_back(LightSetting());
}

void GroupSettings::addDrawSettingToGroup()
{
  m_drawSetting.push_back(DrawSetting());
}

void GroupSettings::addLightSettingToGroup()
{
  m_lightSetting.push_back(LightSetting());
}

bool GroupSettings::lineType_index(unsigned index) const
{
  return m_drawSetting[index].lineType();
}

float GroupSettings::lineSize_index(unsigned index) const
{
  return m_drawSetting[index].lineSize();
}

const float* GroupSettings::lineColor_index(unsigned index) const
{
  return m_drawSetting[index].lineColor();
}

float GroupSettings::lineColorRed_index(unsigned index) const
{
  return m_drawSetting[index].lineColorRed();
}

float GroupSettings::lineColorGreen_index(unsigned index) const
{
  return m_drawSetting[index].lineColorGreen();
}

float GroupSettings::lineColorBlueindex(unsigned index) const
{
  return m_drawSetting[index].lineColorRed();
}

float GroupSettings::lineColorAlpha_index(unsigned index) const
{
  return m_drawSetting[index].lineColorAlpha();
}

unsigned GroupSettings::vertType_index(unsigned index) const
{
  return m_drawSetting[index].vertType();
}

float GroupSettings::vertSize_index(unsigned index) const
{
  return m_drawSetting[index].vertSize();
}

const float* GroupSettings::vertColor_index(unsigned index) const
{
  return m_drawSetting[index].vertColor();
}

float GroupSettings::vertColorRed_index(unsigned index) const
{
  return m_drawSetting[index].vertColorRed();
}

float GroupSettings::vertColorGreen_index(unsigned index) const
{
  return m_drawSetting[index].vertColorGreen();
}

float GroupSettings::vertColorBlue_index(unsigned index) const
{
  return m_drawSetting[index].vertColorBlue();
}

float GroupSettings::vertColorAlpha_index(unsigned index) const
{
  return m_drawSetting[index].vertColorAlpha();
}

const float* GroupSettings::surfacesColor_index(unsigned index) const
{
  return m_drawSetting[index].surfacesColor();
}

float GroupSettings::surfacesColorRed_index(unsigned index) const
{
  return m_drawSetting[index].surfacesColorRed();
}

float GroupSettings::surfacesColorGreen_index(unsigned index) const
{
  return m_drawSetting[index].surfacesColorGreen();
}

float GroupSettings::surfacesColorBlue_index(unsigned index) const
{
  return m_drawSetting[index].surfacesColorBlue();
}

float GroupSettings::surfacesColorAlpha_index(unsigned index) const
{
  return m_drawSetting[index].surfacesColorAlpha();
}

unsigned GroupSettings::drawType_index(unsigned index) const
{
  return m_drawSetting[index].drawType();
}

void GroupSettings::setLineType_index(bool lineType, unsigned index)
{
  m_drawSetting[index].setLineType(lineType);
}

void GroupSettings::setLineSize_index(float lineSize, unsigned index)
{
  m_drawSetting[index].setLineSize(lineSize);
}

void GroupSettings::setLineColor_index(float r, float g, float b, float a, unsigned index)
{
  m_drawSetting[index].setLineColor(r, g, b, a);
}

void GroupSettings::setLineColor_index(const float color[], unsigned index)
{
  m_drawSetting[index].setLineColor(color);
}

void GroupSettings::setVertType_index(unsigned vertType, unsigned index)
{
  m_drawSetting[index].setVertType(vertType);
}

void GroupSettings::setVertSize_index(float vertSize, unsigned index)
{
  m_drawSetting[index].setVertSize(vertSize);
}

void GroupSettings::setVertColor_index(float r, float g, float b, float a, unsigned index)
{
  m_drawSetting[index].setVertColor(r, g, b, a);
}

void GroupSettings::setVertColor_index(const float color[], unsigned index)
{
  m_drawSetting[index].setVertColor(color);
}

void GroupSettings::setSurfaceColor_index(float r, float g, float b, float a, unsigned index)
{
  m_drawSetting[index].setSurfacesColor(r, g, b, a);
}

void GroupSettings::setSurfaceColor_index(const float color[], unsigned index)
{
  m_drawSetting[index].setSurfacesColor(color);
}

void GroupSettings::setDrawType_index(unsigned drawType, unsigned index)
{
  m_drawSetting[index].setDrawType(drawType);
}

const float* GroupSettings::lightPosition_index(unsigned index) const
{
  return m_lightSetting[index].lightPosition();
}

float GroupSettings::lightPositionX_index(unsigned index) const
{
  return m_lightSetting[index].lightPosX();
}

float GroupSettings::lightPosY_index(unsigned index) const
{
  return m_lightSetting[index].lightPosY();
}

float GroupSettings::lightPosZ_index(unsigned index) const
{
  return m_lightSetting[index].lightPosZ();
}

float GroupSettings::lightPower_index(unsigned index) const
{
  return m_lightSetting[index].lightPower();
}

float GroupSettings::lightSpecularFactor_index(unsigned index) const
{
  return m_lightSetting[index].lightSpecularFactor();
}

float GroupSettings::lightAmbientFactor_index(unsigned index) const
{
  return m_lightSetting[index].lightAmbientFactor();
}

const float* GroupSettings::lightSpecularColor_index(unsigned index) const
{
  return m_lightSetting[index].lightSpecularColor();
}

float GroupSettings::lightSpecularColorRed_index(unsigned index) const
{
  return m_lightSetting[index].lightSpecularColorRed();
}

float GroupSettings::lightSpecularColorGreen_index(unsigned index) const
{
  return m_lightSetting[index].lightSpecularColorGreen();
}

float GroupSettings::lightSpecularColorBlue_index(unsigned index) const
{
  return m_lightSetting[index].lightSpecularColorBlue();
}

float GroupSettings::lightSpecularColorAlpha_index(unsigned index) const
{
  return m_lightSetting[index].lightSpecularColorAlpha();
}

const float* GroupSettings::lightColor_index(unsigned index) const
{
  return m_lightSetting[index].lightColor();
}

float GroupSettings::lightColorRed_index(unsigned index) const
{
  return m_lightSetting[index].lightColorRed();
}

float GroupSettings::lightColorGreen_index(unsigned index) const
{
  return m_lightSetting[index].lightColorGreen();
}

float GroupSettings::lightColorBlue_index(unsigned index) const
{
  return m_lightSetting[index].lightColorBlue();
}

float GroupSettings::lightColorAlpha_index(unsigned index) const
{
  return m_lightSetting[index].lightColorAlpha();
}

void GroupSettings::setLightPosition_index(float x, float y, float z, unsigned index)
{
  m_lightSetting[index].setLightPos(x, y, z);
}

void GroupSettings::setLightPosition_index(const float position[], unsigned index)
{
  m_lightSetting[index].setLightPos(position);
}

void GroupSettings::setLightPositionX_index(float x, unsigned index)
{
  m_lightSetting[index].setlightPosX(x);
}

void GroupSettings::setLightPositionY_index(float y, unsigned index)
{
  m_lightSetting[index].setlightPosY(y);
}

void GroupSettings::setLightPositionZ_index(float z, unsigned index)
{
  m_lightSetting[index].setlightPosZ(z);
}

void GroupSettings::setLightPower_index(float p, unsigned index)
{
  m_lightSetting[index].setLightPower(p);
}

void GroupSettings::setLightSpecularFactor_index(float sF, unsigned index)
{
  m_lightSetting[index].setLightSpecularFactor(sF);
}

void GroupSettings::setLightAmbientFactor_index(float aF, unsigned index)
{
  m_lightSetting[index].setLightAmbientFactor(aF);
}

void GroupSettings::setLightSpecularColor_index(float r, float g, float b, float a, unsigned index)
{
  m_lightSetting[index].setLightSpecularColor(r, g, b, a);
}

void GroupSettings::setLightSpecularColor_index(const float color[], unsigned index)
{
  m_lightSetting[index].setLightSpecularColor(color);
}

void GroupSettings::setLightSpecularColorRed_index(float r, unsigned index)
{
  m_lightSetting[index].setLightSpecularColorRed(r);
}

void GroupSettings::setLightSpecularColorGreen_index(float g, unsigned index)
{
  m_lightSetting[index].setLightSpecularColorGreen(g);
}

void GroupSettings::setLightSpecularColorBlue_index(float b, unsigned index)
{
  m_lightSetting[index].setLightSpecularColorBlue(b);
}

void GroupSettings::setLightSpecularColorAlpha_index(float a, unsigned index)
{
  m_lightSetting[index].setLightSpecularColorAlpha(a);
}

void GroupSettings::setLightColor_index(float r, float g, float b, float a, unsigned index)
{
  m_lightSetting[index].setLightColor(r, g, b, a);
}

void GroupSettings::setLightColor_index(const float color[], unsigned index)
{
  m_lightSetting[index].setLightColor(color);
}

void GroupSettings::setLightColorRed_index(float r, unsigned index)
{
  m_lightSetting[index].setLightColorRed(r);
}

void GroupSettings::setLightColorGreen_index(float g, unsigned index)
{
  m_lightSetting[index].setLightColorGreen(g);
}

void GroupSettings::setLightColorBlue_index(float b, unsigned index)
{
  m_lightSetting[index].setLightColorBlue(b);
}

void GroupSettings::setLightColorAlpha_index(float a, unsigned index)
{
  m_lightSetting[index].setLightColorAlpha(a);
}

bool GroupSettings::projection() const
{
  return m_projection;
}

bool GroupSettings::lightStatus() const
{
  return m_lightStatus;
}

bool GroupSettings::lightShade() const
{
  return m_shadding;
}

const float* GroupSettings::bgColor() const
{
  return m_bgColor;
}

float GroupSettings::bgColorRed() const
{
  return m_bgColor[RGBA::RED];
}

float GroupSettings::bgColorGreen() const
{
  return m_bgColor[RGBA::GREEN];
}

float GroupSettings::bgColorBlue() const
{
  return m_bgColor[RGBA::BLUE];
}

float GroupSettings::bgColorAlpha() const
{
  return m_bgColor[RGBA::ALPHA];
}

float GroupSettings::wScreen() const
{
  return m_wScreen;
}

float GroupSettings::hScreen() const
{
  return m_hScreen;
}

void GroupSettings::setProjection(bool typeProjaction)
{
  m_projection = typeProjaction;
}

void GroupSettings::setLightStatus(bool lightStatus)
{
  m_lightStatus = lightStatus;
}

void GroupSettings::setLightShade(bool lightShade)
{
  m_shadding = lightShade;
}

void GroupSettings::setBgColor(float r, float g, float b, float a)
{
  m_bgColor[RGBA::RED] = r;
  m_bgColor[RGBA::GREEN] = g;
  m_bgColor[RGBA::BLUE] = b;
  m_bgColor[RGBA::ALPHA] = a;
}

void GroupSettings::setBgColor(const float color[])
{
  for (int i = RGBA::RED; i < RGBA::N; ++i)
    m_bgColor[i] = color[i];
}

void GroupSettings::setBgColorRed(float r)
{
  m_bgColor[RGBA::RED] = r;
}

void GroupSettings::setBgColorGreen(float g)
{
  m_bgColor[RGBA::GREEN] = g;
}

void GroupSettings::setBgColorBlue(float b)
{
  m_bgColor[RGBA::BLUE] = b;
}

void GroupSettings::setBgColorAlpha(float a)
{
  m_bgColor[RGBA::ALPHA] = a;
}

void GroupSettings::setWScreen(float w)
{
  m_wScreen = w;
}

void GroupSettings::setHScreen(float h)
{
  m_hScreen = h;
}

void GroupSettings::save()
{
  QString pathToConfigFile = QCoreApplication::applicationDirPath() + "/settings/";

  if (!QDir(pathToConfigFile).exists())
    QDir().mkdir(pathToConfigFile);

  QString filename = pathToConfigFile + QString("MainSetting.conf");

  std::ofstream tgt(filename.toStdString());

  if (!tgt.is_open())
    return;

  setlocale(LC_ALL, "en_US.UTF-8");

  tgt << TypeMainSetting::kProjection << " " << m_projection << std::endl;
  tgt << TypeMainSetting::kLightStatus << " " << m_lightStatus << std::endl;
  tgt << TypeMainSetting::kLightShade << " " << m_shadding << std::endl;

  tgt << TypeMainSetting::kBgColor;
  for (int i{}; i < RGBA::N; i++)
    tgt << " " << m_bgColor[i];
  tgt << std::endl;

  tgt << TypeMainSetting::kWScreen << m_wScreen << std::endl;
  tgt << TypeMainSetting::kHScreen << m_hScreen << std::endl;

  tgt << TypeMainSetting::kNumbersDrawSetting << " " << m_drawSetting.size() << std::endl;
  tgt << TypeMainSetting::kNumbersLightSetting << " " << m_lightSetting.size() << std::endl;

  for (unsigned i = 0; i < m_drawSetting.size(); i++)
    m_drawSetting[i].save(i);

  for (unsigned i = 0; i < m_lightSetting.size(); i++)
    m_lightSetting[i].save(i);
}

void GroupSettings::load()
{
  QString pathToConfigFile = QCoreApplication::applicationDirPath() + "/settings/";

  if (!QDir(pathToConfigFile).exists())
    return;

  QString filename = pathToConfigFile + "GroupSettings.conf";

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
      case TypeMainSetting::kProjection: {
        src >> m_projection;
        break;
      }

      case TypeMainSetting::kLightStatus: {
        src >> m_lightStatus;
        break;
      }

      case TypeMainSetting::kLightShade: {
        src >> m_shadding;
        break;
      }

      case TypeMainSetting::kBgColor: {
        for (int i = RGBA::RED; i < RGBA::N; ++i)
          src >> m_bgColor[i];
        break;
      }

      case TypeMainSetting::kWScreen: {
        src >> m_wScreen;
        break;
      }

      case TypeMainSetting::kHScreen: {
        src >> m_hScreen;
        break;
      }

      case TypeMainSetting::kNumbersDrawSetting: {
        unsigned nGroupDrawSets{};

        while (m_drawSetting.size() < nGroupDrawSets)
          m_drawSetting.push_back(DrawSetting());

        for (unsigned i = 0; i < nGroupDrawSets; ++i)
          m_drawSetting[i].load(i);

        break;
      }

      case TypeMainSetting::kNumbersLightSetting: {
        unsigned nGroupLightSets{};

        while (m_drawSetting.size() < nGroupLightSets)
          m_lightSetting.push_back(LightSetting());

        for (unsigned i = 0; i < nGroupLightSets; ++i)
          m_lightSetting[i].load(i);

        break;
      }

      default:
        break;
    }
  }
}

}  // namespace s21_3DViewer
