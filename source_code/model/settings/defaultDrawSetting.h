#ifndef DEFAULTDRAWSETTING_H
#define DEFAULTDRAWSETTING_H

#include "defineSetting.h"

namespace s21_3DViewer
{
class DefaultDrawSetting
{
public:
  static constexpr unsigned lineType = lineType::Solid;
  static constexpr float lineSize = 1.0;
  static constexpr float lineColor[RGBA::N] = { 1.0, 1.0, 1.0, 1.0 };
  static constexpr unsigned vertType = vertType::Square;
  static constexpr float vertSize = 3.0;
  static constexpr float vertColor[RGBA::N] = { 0.0, 0.0, 0.0, 1.0 };
  static constexpr float surfacesColor[RGBA::N] = { 1.0, 1.0, 1.0, 1.0 };
  static constexpr unsigned drawType = typeDraw::Lines;
  static constexpr unsigned projection = projType::Central;
  static constexpr float bgColor[RGBA::N] = { 0.0, 0.0, 0.0, 1.0 };
  static constexpr float widthScreen = 0.8;
  static constexpr float heightScreen = 0.9;
};

}  // namespace s21_3DViewer

#endif  // DEFAULTDRAWSETTING_H