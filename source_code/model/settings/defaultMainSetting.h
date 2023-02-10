#ifndef DEFAULTMAINSETTING_H
#define DEFAULTMAINSETTING_H

#include "defineSetting.h"

namespace s21_3DViewer
{
class DefaultMainSetting
{
public:
  static constexpr unsigned projection = projType::Central;
  static constexpr bool lightStatus = lightStatus::ON;
  static constexpr bool shadding = shaddingType::Flat;
  static constexpr float bgColor[RGBA::N] = { 0.0, 0.0, 0.0, 1.0 };
  static constexpr float wScreen = 0.8;
  static constexpr float hScreen = 0.9;
};

}  // namespace s21_3DViewer

#endif  // DEFAULTMAINSETTING_H
