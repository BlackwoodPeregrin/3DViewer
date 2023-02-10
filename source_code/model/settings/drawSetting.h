#pragma once

#include <QGuiApplication>
#include <QScreen>
#include <array>
#include <fstream>
#include <string>
#include <QDir>

#include "defaultDrawSetting.h"

namespace s21_3DViewer
{
class DrawSetting
{
public:
  DrawSetting()
  {
    setDefault();
  }

  ~DrawSetting() = default;

  DrawSetting(const DrawSetting& other)
  {
    *this = other;
  }

  void operator=(const DrawSetting& other)
  {
    m_lineType = other.m_lineType;
    m_lineSize = other.m_lineSize;

    for (int i = 0; i < RGBA::N; ++i)
      m_lineColor[i] = other.m_lineColor[i];

    m_vertType = other.m_vertType;
    m_vertSize = other.m_vertSize;

    for (int i = 0; i < RGBA::N; ++i)
      m_vertColor[i] = other.m_vertColor[i];

    for (int i = 0; i < RGBA::N; ++i)
      m_surfacesColor[i] = other.m_surfacesColor[i];

    m_drawType = other.m_drawType;
    m_pathToTexture = other.m_pathToTexture;
  }

  void setDefault()
  {
    m_lineType = DefaultDrawSetting::lineType;
    m_lineSize = DefaultDrawSetting::lineSize;

    for (int i = 0; i < RGBA::N; ++i)
      m_lineColor[i] = DefaultDrawSetting::lineColor[i];

    m_vertType = DefaultDrawSetting::vertType;
    m_vertSize = DefaultDrawSetting::vertSize;

    for (int i = 0; i < RGBA::N; ++i)
      m_vertColor[i] = DefaultDrawSetting::vertColor[i];

    for (int i = 0; i < RGBA::N; ++i)
      m_surfacesColor[i] = DefaultDrawSetting::surfacesColor[i];

    m_drawType = DefaultDrawSetting::drawType;
    m_pathToTexture = "";
  }

  bool lineType() const
  {
    return m_lineType;
  }

  float lineSize() const
  {
    return m_lineSize;
  }

  const float* lineColor() const
  {
    return m_lineColor;
  }

  float lineColorRed() const
  {
    return m_lineColor[RGBA::RED];
  }

  float lineColorGreen() const
  {
    return m_lineColor[RGBA::GREEN];
  }

  float lineColorBlue() const
  {
    return m_lineColor[RGBA::BLUE];
  }

  float lineColorAlpha() const
  {
    return m_lineColor[RGBA::ALPHA];
  }

  unsigned vertType() const
  {
    return m_vertType;
  }

  float vertSize() const
  {
    return m_vertSize;
  }

  const float* vertColor() const
  {
    return m_vertColor;
  }

  float vertColorRed() const
  {
    return m_vertColor[RGBA::RED];
  }

  float vertColorGreen() const
  {
    return m_vertColor[RGBA::GREEN];
  }

  float vertColorBlue() const
  {
    return m_vertColor[RGBA::BLUE];
  }

  float vertColorAlpha() const
  {
    return m_vertColor[RGBA::ALPHA];
  }

  const float* surfacesColor() const
  {
    return m_surfacesColor;
  }

  float surfacesColorRed() const
  {
    return m_surfacesColor[RGBA::RED];
  }

  float surfacesColorGreen() const
  {
    return m_surfacesColor[RGBA::GREEN];
  }

  float surfacesColorBlue() const
  {
    return m_surfacesColor[RGBA::BLUE];
  }

  float surfacesColorAlpha() const
  {
    return m_surfacesColor[RGBA::ALPHA];
  }

  unsigned drawType() const
  {
    return m_drawType;
  }

  const std::string& texturePath() const
  {
    return m_pathToTexture;
  }

  void setLineType(bool lineType)
  {
    m_lineType = lineType;
  }

  void setLineSize(float lineSize)
  {
    m_lineSize = lineSize;
  }

  void setLineColor(float r, float g, float b, float a)
  {
    m_lineColor[RGBA::RED] = r;
    m_lineColor[RGBA::GREEN] = g;
    m_lineColor[RGBA::BLUE] = b;
    m_lineColor[RGBA::ALPHA] = a;
  }

  void setLineColor(const float color[RGBA::N])
  {
    for (int i = 0; i < RGBA::N; ++i)
      m_lineColor[i] = color[i];
  }

  void setVertType(unsigned vertType)
  {
    m_vertType = vertType;
  }

  void setVertSize(float vertSize)
  {
    m_vertSize = vertSize;
  }

  void setVertColor(float r, float g, float b, float a)
  {
    m_vertColor[RGBA::RED] = r;
    m_vertColor[RGBA::GREEN] = g;
    m_vertColor[RGBA::BLUE] = b;
    m_vertColor[RGBA::ALPHA] = a;
  }

  void setVertColor(const float color[RGBA::N])
  {
    for (int i = 0; i < RGBA::N; ++i)
      m_vertColor[i] = color[i];
  }

  void setSurfacesColor(float r, float g, float b, float a)
  {
    m_surfacesColor[RGBA::RED] = r;
    m_surfacesColor[RGBA::GREEN] = g;
    m_surfacesColor[RGBA::BLUE] = b;
    m_surfacesColor[RGBA::ALPHA] = a;
  }

  void setSurfacesColor(const float color[RGBA::N])
  {
    for (int i = 0; i < RGBA::N; ++i)
      m_surfacesColor[i] = color[i];
  }

  void setDrawType(unsigned drawType)
  {
    m_drawType = drawType;
  }

  void setTexturePath(const std::string& pathToTexture)
  {
    m_pathToTexture = pathToTexture;
  }

  // сохранения в файл настроек
  void save(unsigned numObject)
  {
    QString pathToConfig = QCoreApplication::applicationDirPath() + "/settings/";

    if (!QDir(pathToConfig).exists())
      QDir().mkdir(pathToConfig);

    QString filename = pathToConfig + QString("DrawSetting") + QString::number(numObject) + QString(".conf");

    std::fstream tgt(filename.toStdString(), std::fstream::out | std::fstream::trunc);

    if (!tgt.is_open())
      return;

    setlocale(LC_ALL, "en_US.UTF-8");

    tgt << TypeDrawSetting::klineType << " " << m_lineType << std::endl;
    tgt << TypeDrawSetting::kLineSize << " " << m_lineSize << std::endl;

    tgt << TypeDrawSetting::kLineColor;
    for (int i = 0; i < RGBA::N; i++)
      tgt << " " << m_lineColor[i];
    tgt << std::endl;

    tgt << TypeDrawSetting::kVertType << " " << m_vertType << std::endl;
    tgt << TypeDrawSetting::kVertSize << " " << m_vertSize << std::endl;

    tgt << TypeDrawSetting::kVertColor;
    for (int i = 0; i < RGBA::N; i++)
      tgt << " " << m_vertColor[i];
    tgt << std::endl;

    tgt << TypeDrawSetting::kSurfaceColor;
    for (int i = 0; i < RGBA::N; i++)
      tgt << " " << m_surfacesColor[i];
    tgt << std::endl;

    tgt << TypeDrawSetting::kDrawType << " " << m_drawType << std::endl;
    tgt << TypeDrawSetting::kPathToTexture << " " << m_pathToTexture << std::endl;
  }

  // загрузка из файла настроек
  void load(unsigned numObject)
  {
    QString pathToConfig = QCoreApplication::applicationDirPath() + "/settings/";

    if (!QDir(pathToConfig).exists())
      return;

    QString filename = pathToConfig + QString("DrawSetting") + QString::number(numObject) + QString(".conf");

    std::fstream src(filename.toStdString(), std::fstream::in);

    if (!src.is_open())
      return;

    setlocale(LC_ALL, "en_US.UTF-8");

    while (src)
    {
      int type;
      src >> type;

      switch (type)
      {
        case TypeDrawSetting::klineType: {
          src >> m_lineType;
          break;
        }

        case TypeDrawSetting::kLineSize: {
          src >> m_lineSize;
          break;
        }

        case TypeDrawSetting::kLineColor: {
          for (int i = RGBA::RED; i < RGBA::N; i++)
            src >> m_lineColor[i];
          break;
        }

        case TypeDrawSetting::kVertType: {
          src >> m_vertType;
          break;
        }

        case TypeDrawSetting::kVertSize: {
          src >> m_vertSize;
          break;
        }

        case TypeDrawSetting::kVertColor: {
          for (int i = RGBA::RED; i < RGBA::N; i++)
            src >> m_vertColor[i];
          break;
        }

        case TypeDrawSetting::kSurfaceColor: {
          for (int i = RGBA::RED; i < RGBA::N; i++)
            src >> m_surfacesColor[i];
          break;
        }

        case TypeDrawSetting::kDrawType: {
          src >> m_drawType;
          break;
        }

        case TypeDrawSetting::kPathToTexture: {
          src >> m_pathToTexture;
          break;
        }

        default:
          break;
      }
    }
  }

private:
  bool m_lineType;
  float m_lineSize;
  float m_lineColor[RGBA::N];
  unsigned m_vertType;
  float m_vertSize;
  float m_vertColor[RGBA::N];
  float m_surfacesColor[RGBA::N];
  unsigned m_drawType;
  std::string m_pathToTexture;
};

}  // namespace s21_3DViewer
