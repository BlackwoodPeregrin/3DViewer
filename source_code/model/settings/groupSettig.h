#ifndef GROUPSETTIG_H
#define GROUPSETTIG_H

#include "drawSetting.h"
#include "lightSetting.h"
#include "defaultMainSetting.h"

namespace s21_3DViewer
{
class GroupSettings
{
public:
  GroupSettings()
  {
    setDefault();
  }

  GroupSettings(const GroupSettings& other)
  {
    *this = other;
  }

  ~GroupSettings() = default;

  void operator=(const GroupSettings& other)
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

  void setDefault()
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

  void addDrawSettingToGroup()
  {
    m_drawSetting.push_back(DrawSetting());
  }

  void addLightSettingToGroup()
  {
    m_lightSetting.push_back(LightSetting());
  }

  /*--- Draw Setting Group ---*/

  bool lineType_index(unsigned index = 0) const
  {
    return m_drawSetting[index].lineType();
  }

  float lineSize_index(unsigned index = 0) const
  {
    return m_drawSetting[index].lineSize();
  }

  const float* lineColor_index(unsigned index = 0) const
  {
    return m_drawSetting[index].lineColor();
  }

  float lineColorRed_index(unsigned index = 0) const
  {
    return m_drawSetting[index].lineColorRed();
  }

  float lineColorGreen_index(unsigned index = 0) const
  {
    return m_drawSetting[index].lineColorGreen();
  }

  float lineColorBlueindex(unsigned index = 0) const
  {
    return m_drawSetting[index].lineColorRed();
  }

  float lineColorAlpha_index(unsigned index = 0) const
  {
    return m_drawSetting[index].lineColorAlpha();
  }

  unsigned vertType_index(unsigned index = 0) const
  {
    return m_drawSetting[index].vertType();
  }

  float vertSize_index(unsigned index = 0) const
  {
    return m_drawSetting[index].vertSize();
  }

  const float* vertColor_index(unsigned index = 0) const
  {
    return m_drawSetting[index].vertColor();
  }

  float vertColorRed_index(unsigned index = 0) const
  {
    return m_drawSetting[index].vertColorRed();
  }

  float vertColorGreen_index(unsigned index = 0) const
  {
    return m_drawSetting[index].vertColorGreen();
  }

  float vertColorBlue_index(unsigned index = 0) const
  {
    return m_drawSetting[index].vertColorBlue();
  }

  float vertColorAlpha_index(unsigned index = 0) const
  {
    return m_drawSetting[index].vertColorAlpha();
  }

  const float* surfacesColor_index(unsigned index = 0) const
  {
    return m_drawSetting[index].surfacesColor();
  }

  float surfacesColorRed_index(unsigned index = 0) const
  {
    return m_drawSetting[index].surfacesColorRed();
  }

  float surfacesColorGreen_index(unsigned index = 0) const
  {
    return m_drawSetting[index].surfacesColorGreen();
  }

  float surfacesColorBlue_index(unsigned index = 0) const
  {
    return m_drawSetting[index].surfacesColorBlue();
  }

  float surfacesColorAlpha_index(unsigned index = 0) const
  {
    return m_drawSetting[index].surfacesColorAlpha();
  }

  unsigned drawType_index(unsigned index = 0) const
  {
    return m_drawSetting[index].drawType();
  }

  void setLineType_index(bool lineType, unsigned index = 0)
  {
    m_drawSetting[index].setLineType(lineType);
  }

  void setLineSize_index(float lineSize, unsigned index = 0)
  {
    m_drawSetting[index].setLineSize(lineSize);
  }

  void setLineColor_index(float r, float g, float b, float a, unsigned index = 0)
  {
    m_drawSetting[index].setLineColor(r, g, b, a);
  }

  void setLineColor_index(const float color[RGBA::N], unsigned index = 0)
  {
    m_drawSetting[index].setLineColor(color);
  }

  void setVertType_index(unsigned vertType, unsigned index = 0)
  {
    m_drawSetting[index].setVertType(vertType);
  }

  void setVertSize_index(float vertSize, unsigned index = 0)
  {
    m_drawSetting[index].setVertSize(vertSize);
  }

  void setVertColor_index(float r, float g, float b, float a, unsigned index = 0)
  {
    m_drawSetting[index].setVertColor(r, g, b, a);
  }

  void setVertColor_index(const float color[RGBA::N], unsigned index = 0)
  {
    m_drawSetting[index].setVertColor(color);
  }

  void setSurfaceColor_index(float r, float g, float b, float a, unsigned index = 0)
  {
    m_drawSetting[index].setSurfacesColor(r, g, b, a);
  }

  void setSurfaceColor_index(const float color[RGBA::N], unsigned index = 0)
  {
    m_drawSetting[index].setSurfacesColor(color);
  }

  void setDrawType_index(unsigned drawType, unsigned index = 0)
  {
    m_drawSetting[index].setDrawType(drawType);
  }

  /*--- Light Setting Group ---*/

  const float* lightPosition_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightPosition();
  }

  float lightPositionX_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightPosX();
  }

  float lightPosY_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightPosY();
  }

  float lightPosZ_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightPosZ();
  }

  float lightPower_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightPower();
  }

  float lightSpecularFactor_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightSpecularFactor();
  }

  float lightAmbientFactor_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightAmbientFactor();
  }

  const float* lightSpecularColor_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightSpecularColor();
  }

  float lightSpecularColorRed_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightSpecularColorRed();
  }

  float lightSpecularColorGreen_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightSpecularColorGreen();
  }

  float lightSpecularColorBlue_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightSpecularColorBlue();
  }

  float lightSpecularColorAlpha_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightSpecularColorAlpha();
  }

  const float* lightColor_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightColor();
  }

  float lightColorRed_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightColorRed();
  }

  float lightColorGreen_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightColorGreen();
  }

  float lightColorBlue_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightColorBlue();
  }

  float lightColorAlpha_index(unsigned index = 0) const
  {
    return m_lightSetting[index].lightColorAlpha();
  }

  void setLightPosition_index(float x, float y, float z, unsigned index = 0)
  {
    m_lightSetting[index].setLightPos(x, y, z);
  }

  void setLightPosition_index(const float position[3], unsigned index = 0)
  {
    m_lightSetting[index].setLightPos(position);
  }

  void setLightPositionX_index(float x, unsigned index = 0)
  {
    m_lightSetting[index].setlightPosX(x);
  }

  void setLightPositionY_index(float y, unsigned index = 0)
  {
    m_lightSetting[index].setlightPosY(y);
  }

  void setLightPositionZ_index(float z, unsigned index = 0)
  {
    m_lightSetting[index].setlightPosZ(z);
  }

  void setLightPower_index(float p, unsigned index = 0)
  {
    m_lightSetting[index].setLightPower(p);
  }

  void setLightSpecularFactor_index(float sF, unsigned index = 0)
  {
    m_lightSetting[index].setLightSpecularFactor(sF);
  }

  void setLightAmbientFactor_index(float aF, unsigned index = 0)
  {
    m_lightSetting[index].setLightAmbientFactor(aF);
  }

  void setLightSpecularColor_index(float r, float g, float b, float a, unsigned index = 0)
  {
    m_lightSetting[index].setLightSpecularColor(r, g, b, a);
  }

  void setLightSpecularColor_index(const float color[RGBA::N], unsigned index = 0)
  {
    m_lightSetting[index].setLightSpecularColor(color);
  }

  void setLightSpecularColorRed_index(float r, unsigned index = 0)
  {
    m_lightSetting[index].setLightSpecularColorRed(r);
  }

  void setLightSpecularColorGreen_index(float g, unsigned index = 0)
  {
    m_lightSetting[index].setLightSpecularColorGreen(g);
  }

  void setLightSpecularColorBlue_index(float b, unsigned index = 0)
  {
    m_lightSetting[index].setLightSpecularColorBlue(b);
  }

  void setLightSpecularColorAlpha_index(float a, unsigned index = 0)
  {
    m_lightSetting[index].setLightSpecularColorAlpha(a);
  }

  void setLightColor_index(float r, float g, float b, float a, unsigned index = 0)
  {
    m_lightSetting[index].setLightColor(r, g, b, a);
  }

  void setLightColor_index(const float color[RGBA::N], unsigned index = 0)
  {
    m_lightSetting[index].setLightColor(color);
  }

  void setLightColorRed_index(float r, unsigned index = 0)
  {
    m_lightSetting[index].setLightColorRed(r);
  }

  void setLightColorGreen_index(float g, unsigned index = 0)
  {
    m_lightSetting[index].setLightColorGreen(g);
  }

  void setLightColorBlue_index(float b, unsigned index = 0)
  {
    m_lightSetting[index].setLightColorBlue(b);
  }

  void setLightColorAlpha_index(float a, unsigned index = 0)
  {
    m_lightSetting[index].setLightColorAlpha(a);
  }

  /*--- Main Setting Group ---*/

  bool projection() const
  {
    return m_projection;
  }

  bool lightStatus() const
  {
    return m_lightStatus;
  }

  bool lightShade() const
  {
    return m_shadding;
  }

  const float* bgColor() const
  {
    return m_bgColor;
  }

  float bgColorRed() const
  {
    return m_bgColor[RGBA::RED];
  }

  float bgColorGreen() const
  {
    return m_bgColor[RGBA::GREEN];
  }

  float bgColorBlue() const
  {
    return m_bgColor[RGBA::BLUE];
  }

  float bgColorAlpha() const
  {
    return m_bgColor[RGBA::ALPHA];
  }

  float wScreen() const
  {
    return m_wScreen;
  }

  float hScreen() const
  {
    return m_hScreen;
  }

  void setProjection(bool typeProjaction)
  {
    m_projection = typeProjaction;
  }

  void setLightStatus(bool lightStatus)
  {
    m_lightStatus = lightStatus;
  }

  void setLightShade(bool lightShade)
  {
    m_shadding = lightShade;
  }

  void setBgColor(float r, float g, float b, float a)
  {
    m_bgColor[RGBA::RED] = r;
    m_bgColor[RGBA::GREEN] = g;
    m_bgColor[RGBA::BLUE] = b;
    m_bgColor[RGBA::ALPHA] = a;
  }

  void setBgColor(const float color[RGBA::N])
  {
    for (int i = RGBA::RED; i < RGBA::N; ++i)
      m_bgColor[i] = color[i];
  }

  void setBgColorRed(float r)
  {
    m_bgColor[RGBA::RED] = r;
  }

  void setBgColorGreen(float g)
  {
    m_bgColor[RGBA::GREEN] = g;
  }

  void setBgColorBlue(float b)
  {
    m_bgColor[RGBA::BLUE] = b;
  }

  void setBgColorAlpha(float a)
  {
    m_bgColor[RGBA::ALPHA] = a;
  }

  void setWScreen(float w)
  {
    m_wScreen = w;
  }

  void setHScreen(float h)
  {
    m_hScreen = h;
  }

  // сохранения в файл настроек
  void save()
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

  // загрузка из файла настроек
  void load()
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

private:
  /*---значение проекции---*/
  bool m_projection;
  /*---значение отвечающее за включен/выключен свет---*/
  bool m_lightStatus;
  /*---тип затенения---*/
  bool m_shadding;
  /*---значение данего фона---*/
  float m_bgColor[RGBA::N];
  /*---значение ширины экрана---*/
  float m_wScreen;
  /*---значение высоты экрана---*/
  float m_hScreen;

  QVector<DrawSetting> m_drawSetting;
  QVector<LightSetting> m_lightSetting;
};

}  // namespace s21_3DViewer

#endif  // GROUPSETTIG_H
