#ifndef DEFAULTLIGHTSETTING_H
#define DEFAULTLIGHTSETTING_H

#include "defineSetting.h"

namespace s21_3DViewer
{
class DefaultLightSetting
{
public:
  static constexpr float lightPosition[3] = { 0.0, 0.0, 0.0 };
  static constexpr float lightPower = 1.0;
  static constexpr float specularFactor = 50.0;
  static constexpr float ambientFactor = 0.0;
  static constexpr float specularColor[RGBA::N] = { 1.0, 1.0, 1.0, 1.0 };
  static constexpr float lightColor[RGBA::N] = { 1.0, 1.0, 1.0, 1.0 };
};

}  // namespace s21_3DViewer

#endif  // DEFAULTLIGHTSETTING_H
