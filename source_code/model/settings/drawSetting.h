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
  DrawSetting();

  ~DrawSetting() = default;

  DrawSetting(const DrawSetting& other);

  void operator=(const DrawSetting& other);

  void setDefault();

  // getters

  bool lineType() const;
  float lineSize() const;
  const float* lineColor() const;
  float lineColorRed() const;
  float lineColorGreen() const;
  float lineColorBlue() const;
  float lineColorAlpha() const;

  unsigned vertType() const;
  float vertSize() const;
  const float* vertColor() const;
  float vertColorRed() const;
  float vertColorGreen() const;
  float vertColorBlue() const;
  float vertColorAlpha() const;

  const float* surfacesColor() const;
  float surfacesColorRed() const;
  float surfacesColorGreen() const;
  float surfacesColorBlue() const;
  float surfacesColorAlpha() const;

  unsigned drawType() const;

  // setters

  void setLineType(bool lineType);
  void setLineSize(float lineSize);
  void setLineColor(float r, float g, float b, float a);
  void setLineColor(const float color[RGBA::N]);

  void setVertType(unsigned vertType);
  void setVertSize(float vertSize);
  void setVertColor(float r, float g, float b, float a);
  void setVertColor(const float color[RGBA::N]);

  void setSurfacesColor(float r, float g, float b, float a);
  void setSurfacesColor(const float color[RGBA::N]);
  void setDrawType(unsigned drawType);

  // сохранения в файл настроек
  void save(unsigned numObject);
  // загрузка из файла настроек
  void load(unsigned numObject);

private:
  bool m_lineType;
  float m_lineSize;
  float m_lineColor[RGBA::N];
  unsigned m_vertType;
  float m_vertSize;
  float m_vertColor[RGBA::N];
  float m_surfacesColor[RGBA::N];
  unsigned m_drawType;
};

}  // namespace s21_3DViewer
