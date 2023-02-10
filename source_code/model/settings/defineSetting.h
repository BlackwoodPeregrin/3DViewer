#ifndef DEFINESETTING_H
#define DEFINESETTING_H

namespace s21_3DViewer
{
enum RGBA
{
  RED,
  GREEN,
  BLUE,
  ALPHA,
  N
};

enum projType
{
  Parallel,
  Central
};

enum lineType
{
  Solid,
  Dashed
};

enum vertType
{
  None,
  Circle,
  Square
};

enum typeDraw
{
  Points,
  Lines,
  Line_Loop,
  Line_Strip,
  Triangles
};

enum lightStatus
{
  OFF,
  ON
};

enum shaddingType
{
  Flat,
  Soft
};

enum TypeDrawSetting
{
  klineType,
  kLineSize,
  kLineColor,
  kVertType,
  kVertSize,
  kVertColor,
  kSurfaceColor,
  kDrawType,
  kPathToTexture
};

enum TypeLightSetting
{
  kLightPos,
  kLightPower,
  kLightSpecularFactor,
  kLightSpecularColor,
  kLightColor
};

enum TypeMainSetting
{
  kProjection,
  kLightStatus,
  kLightShade,
  kBgColor,
  kWScreen,
  kHScreen,
  kNumbersDrawSetting,
  kNumbersLightSetting
};

}  // namespace s21_3DViewer

#endif  // DEFINESETTING_H
