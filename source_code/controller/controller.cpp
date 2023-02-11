#include "controller.h"

namespace s21_3DViewer
{
unsigned Controller::lineType_sets(unsigned indexSetting) const
{
  return m_setting.lineType_index(indexSetting);
}

float Controller::lineSize_sets(unsigned indexSetting) const
{
  return m_setting.lineSize_index(indexSetting);
}

QVector4D Controller::lineColor_sets(unsigned indexSetting) const
{
  const float* buf = m_setting.lineColor_index(indexSetting);
  return QVector4D(buf[RGBA::RED], buf[RGBA::GREEN], buf[RGBA::BLUE], buf[RGBA::ALPHA]);
}

float Controller::lineColorRed_sets(unsigned indexSetting) const
{
  return m_setting.lineColorRed_index(indexSetting);
}

float Controller::lineColorGreen_sets(unsigned indexSetting) const
{
  return m_setting.lineColorGreen_index(indexSetting);
}

float Controller::lineColorBlue_sets(unsigned indexSetting) const
{
  return m_setting.lineColorBlueindex(indexSetting);
}

float Controller::lineColorAlpha_sets(unsigned indexSetting) const
{
  return m_setting.lineColorAlpha_index(indexSetting);
}

unsigned Controller::vertType_sets(unsigned indexSetting) const
{
  return m_setting.vertType_index(indexSetting);
}

float Controller::vertSize_sets(unsigned indexSetting) const
{
  return m_setting.vertSize_index(indexSetting);
}

QVector4D Controller::vertColor_sets(unsigned indexSetting) const
{
  const float* buf = m_setting.vertColor_index(indexSetting);
  return QVector4D(buf[RGBA::RED], buf[RGBA::GREEN], buf[RGBA::BLUE], buf[RGBA::ALPHA]);
}

float Controller::vertColorRed_sets(unsigned indexSetting) const
{
  return m_setting.vertColorRed_index(indexSetting);
}

float Controller::vertColorGreen_sets(unsigned indexSetting) const
{
  return m_setting.vertColorGreen_index(indexSetting);
}

float Controller::vertColorBlue_sets(unsigned indexSetting) const
{
  return m_setting.vertColorBlue_index(indexSetting);
}

float Controller::vertColorAlpha_sets(unsigned indexSetting) const
{
  return m_setting.vertColorAlpha_index(indexSetting);
}

QVector4D Controller::surfacesColor_sets(unsigned indexSetting) const
{
  const float* buf = m_setting.surfacesColor_index(indexSetting);
  return QVector4D(buf[RGBA::RED], buf[RGBA::GREEN], buf[RGBA::BLUE], buf[RGBA::ALPHA]);
}

float Controller::surfacesColorRed_sets(unsigned indexSetting) const
{
  return m_setting.surfacesColorRed_index(indexSetting);
}

float Controller::surfacesColorGreen_sets(unsigned indexSetting) const
{
  return m_setting.surfacesColorGreen_index(indexSetting);
}

float Controller::surfacesColorBlue_sets(unsigned indexSetting) const
{
  return m_setting.surfacesColorBlue_index(indexSetting);
}

float Controller::surfacesColorAlpha_sets(unsigned indexSetting) const
{
  return m_setting.surfacesColorAlpha_index(indexSetting);
}

unsigned Controller::drawType_sets(unsigned indexSetting) const
{
  return m_setting.drawType_index(indexSetting);
}

void Controller::setLineType_sets(unsigned lineType, unsigned indexSetting)
{
  m_setting.setLineType_index(lineType, indexSetting);
}

void Controller::setLineSize_sets(float lineSize, unsigned indexSetting)
{
  m_setting.setLineSize_index(lineSize, indexSetting);
}

void Controller::setLineColor_sets(float r, float g, float b, float a, unsigned indexSetting)
{
  m_setting.setLineColor_index(r, g, b, a, indexSetting);
}

void Controller::setLineColor_sets(const QVector4D& color, unsigned indexSetting)
{
  float buf[RGBA::N]{};

  for (int i = RGBA::RED; i < RGBA::N; ++i)
    buf[i] = color[i];

  m_setting.setLineColor_index(buf, indexSetting);
}

void Controller::setVertType_sets(unsigned vertType, unsigned indexSetting)
{
  m_setting.setVertType_index(vertType, indexSetting);
}

void Controller::setVertSize_sets(float vertSize, unsigned indexSetting)
{
  m_setting.setVertSize_index(vertSize, indexSetting);
}

void Controller::setVertColor_sets(float r, float g, float b, float a, unsigned indexSetting)
{
  m_setting.setVertColor_index(r, g, b, a, indexSetting);
}

void Controller::setVertColor_sets(const QVector4D& color, unsigned indexSetting)
{
  float buf[RGBA::N]{};

  for (int i = RGBA::RED; i < RGBA::N; ++i)
    buf[i] = color[i];

  m_setting.setVertColor_index(buf, indexSetting);
}

void Controller::setSurfaces_color_sets(float r, float g, float b, float a, unsigned indexSetting)
{
  m_setting.setSurfaceColor_index(r, g, b, a, indexSetting);
}

void Controller::setSurfaces_color_sets(const QVector4D& color, unsigned indexSetting)
{
  float buf[RGBA::N]{};

  for (int i = RGBA::RED; i < RGBA::N; ++i)
    buf[i] = color[i];

  m_setting.setSurfaceColor_index(buf, indexSetting);
}

void Controller::setDrawType_sets(unsigned drawType, unsigned indexSetting)
{
  m_setting.setDrawType_index(drawType, indexSetting);
}

QVector4D Controller::lightPosition_sets(unsigned indexSetting) const
{
  const float* buf = m_setting.lightPosition_index(indexSetting);
  return QVector4D(buf[RGBA::RED], buf[RGBA::GREEN], buf[RGBA::BLUE], buf[RGBA::ALPHA]);
}

float Controller::lightPositionX_sets(unsigned indexSetting) const
{
  return m_setting.lightPositionX_index(indexSetting);
}

float Controller::lightPositionY_sets(unsigned indexSetting) const
{
  return m_setting.lightPosY_index(indexSetting);
}

float Controller::lightPositionZ_sets(unsigned indexSetting) const
{
  return m_setting.lightPosZ_index(indexSetting);
}

float Controller::lightPower_sets(unsigned indexSetting) const
{
  return m_setting.lightPower_index(indexSetting);
}

float Controller::specularFactor_sets(unsigned indexSetting) const
{
  return m_setting.lightSpecularFactor_index(indexSetting);
}

float Controller::ambientFactor_sets(unsigned indexSetting) const
{
  return m_setting.lightAmbientFactor_index(indexSetting);
}

QVector4D Controller::specularColor(unsigned indexSetting) const
{
  const float* buf = m_setting.lightSpecularColor_index(indexSetting);
  return QVector4D(buf[RGBA::RED], buf[RGBA::GREEN], buf[RGBA::BLUE], buf[RGBA::ALPHA]);
}

float Controller::specularColorRed_sets(unsigned indexSetting) const
{
  return m_setting.vertColorRed_index(indexSetting);
}

float Controller::specularColorGreen_sets(unsigned indexSetting) const
{
  return m_setting.vertColorGreen_index(indexSetting);
}

float Controller::specularColorBlue_sets(unsigned indexSetting) const
{
  return m_setting.vertColorBlue_index(indexSetting);
}

float Controller::specularColorAlpha_sets(unsigned indexSetting) const
{
  return m_setting.vertColorAlpha_index(indexSetting);
}

QVector4D Controller::lightColor_sets(unsigned indexSetting) const
{
  const float* buf = m_setting.lightColor_index(indexSetting);
  return QVector4D(buf[RGBA::RED], buf[RGBA::GREEN], buf[RGBA::BLUE], buf[RGBA::ALPHA]);
}

float Controller::lightColorRed_sets(unsigned indexSetting) const
{
    return m_setting.lightColorRed_index(indexSetting);
}

float Controller::lightColorGreen_sets(unsigned indexSetting) const
{
    return m_setting.lightColorGreen_index(indexSetting);
}

float Controller::lightColorBlue_sets(unsigned indexSetting) const
{
    return m_setting.lightColorBlue_index(indexSetting);
}

float Controller::lightColorAlpha_sets(unsigned indexSetting) const
{
    return m_setting.lightColorAlpha_index(indexSetting);
}

void Controller::setLightPosition_sets(float x, float y, float z, unsigned indexSetting)
{
    m_setting.setLightPosition_index(x, y, z, indexSetting);
}

void Controller::setLightPosition_sets(const QVector3D &pos, unsigned indexSetting)
{
    m_setting.setLightPosition_index(pos[0], pos[1], pos[2], indexSetting);
}

void Controller::setLightPositionX_sets(float x, unsigned indexSetting)
{
    m_setting.setLightPositionX_index(x, indexSetting);
}

void Controller::setLightPositionY_sets(float y, unsigned indexSetting)
{
    m_setting.setLightPositionY_index(y, indexSetting);
}

void Controller::setLightPositionZ_sets(float z, unsigned indexSetting)
{
    m_setting.setLightPositionZ_index(z, indexSetting);
}

void Controller::setLightPower_sets(float power, unsigned indexSetting)
{
    m_setting.setLightPower_index(power, indexSetting);
}

void Controller::setSpecularFactor_sets(float sF, unsigned indexSetting)
{
    m_setting.setLightSpecularFactor_index(sF, indexSetting);
}

void Controller::setAmbientFactor_sets(float aF, unsigned indexSetting)
{
    m_setting.setLightAmbientFactor_index(aF, indexSetting);
}

void Controller::setLightSpecularColor_sets(float r, float g, float b, float a, unsigned indexSetting)
{
    m_setting.setLightSpecularColor_index(r, g, b, a, indexSetting);
}

void Controller::setLightSpecularColor_sets(const QVector4D &color, unsigned indexSetting)
{
    m_setting.setLightSpecularColor_index(color[RGBA::RED], color[RGBA::GREEN], color[RGBA::BLUE], color[RGBA::ALPHA],
            indexSetting);
}

void Controller::setLightSpecularColorRed_sets(float r, unsigned indexSetting)
{
    m_setting.setLightSpecularColorRed_index(r, indexSetting);
}

void Controller::setLightSpecularColorGreen_sets(float g, unsigned indexSetting)
{
    m_setting.setLightSpecularColorGreen_index(g, indexSetting);
}

void Controller::setLightSpecularColorBlue_sets(float b, unsigned indexSetting)
{
    m_setting.setLightSpecularColorBlue_index(b, indexSetting);
}

void Controller::setLightSpecularColorAlpha_sets(float a, unsigned indexSetting)
{
    m_setting.setLightSpecularColorAlpha_index(a, indexSetting);
}

void Controller::setLightColor_sets(float r, float g, float b, float a, unsigned indexSetting)
{
    m_setting.setLightColor_index(r, g, b, a, indexSetting);
}

void Controller::setLightColor_sets(const QVector4D &color, unsigned indexSetting)
{
    m_setting.setLightColor_index(color[RGBA::RED], color[RGBA::GREEN], color[RGBA::BLUE], color[RGBA::ALPHA],
            indexSetting);
}

void Controller::setLightColorRed_sets(float r, unsigned indexSetting)
{
    m_setting.setLightColorRed_index(r, indexSetting);
}

void Controller::setLightColorGreen_sets(float g, unsigned indexSetting)
{
    m_setting.setLightColorGreen_index(g, indexSetting);
}

void Controller::setLightColorBlue_sets(float b, unsigned indexSetting)
{
    m_setting.setLightColorBlue_index(b, indexSetting);
}

void Controller::setLightColorAlpha_sets(float a, unsigned indexSetting)
{
    m_setting.setLightColorAlpha_index(a, indexSetting);
}

unsigned Controller::projection_sets() const
{
    return m_setting.projection();
}

bool Controller::lightStatus_sets() const
{
    return m_setting.lightStatus();
}

bool Controller::lightShade() const
{
    return m_setting.lightShade();
}

QVector4D Controller::bgColor_sets() const
{
    const float* buf = m_setting.bgColor();
    return QVector4D(buf[RGBA::RED], buf[RGBA::GREEN], buf[RGBA::BLUE], buf[RGBA::ALPHA]);
}

float Controller::bgColorRed_sets() const
{
    return m_setting.bgColorRed();
}

float Controller::bgColorGreen_sets() const
{
    return m_setting.bgColorGreen();
}

float Controller::bgColorBlue_sets() const
{
    return m_setting.bgColorBlue();
}

float Controller::bgColorAlpha_sets() const
{
    return m_setting.bgColorAlpha();
}

float Controller::wScreen_sets() const
{
    return m_setting.wScreen();
}

float Controller::hScreent_sets() const
{
    return m_setting.hScreen();
}

void Controller::setProjection_sets(unsigned typeProjaction)
{
    m_setting.setProjection(typeProjaction);
}

void Controller::setLightStatus_sets(bool status)
{
    m_setting.setLightStatus(status);
}

void Controller::setLightShade_sets(bool shade)
{
    m_setting.setLightShade(shade);
}

void Controller::setBgColor_sets(float r, float g, float b, float a)
{
    m_setting.setBgColor(r, g, b, a);
}

void Controller::setBgColorRed_sets(float r)
{
    m_setting.setBgColorRed(r);
}

void Controller::setBgColorGreen_sets(float g)
{
    m_setting.setBgColorGreen(g);
}

void Controller::setBgColorBlue_sets(float b)
{
    m_setting.setBgColorBlue(b);
}

void Controller::setBgColorAlpha_sets(float a)
{
    m_setting.setBgColorAlpha(a);
}

void Controller::setWScreen_sets(float w)
{
    m_setting.setWScreen(w);
}

void Controller::setHScreen_sets(float h)
{
    m_setting.setHScreen(h);
}

void Controller::translateCamera(const QVector3D &t)
{
    m_camera.translate(t);
}

void Controller::rotateCamera(const QQuaternion &r)
{
    m_camera.rotate(r);
}

void Controller::scaleCamera(float s)
{
    m_camera.scale(s);
}

QMatrix4x4 Controller::view_matrix() const
{
    return m_camera.viewMatrix();
}

bool Controller::haveObjects() const
{
    return !m_object.isEmpty();
}

unsigned Controller::sumObjects() const
{
    return m_object.sumObjects();
}

bool Controller::add_object(const QString &filePath)
{
    //    QString texturePath = QString::fromUtf8(m_setting.texture_path_index_settings().c_str());
    //    if (texturePath.isEmpty())
    //    {
    //      return m_object.add_object(filePath);
    //    }
    //    else
    //    {
    //      bool res = m_object.add_object(filePath);
    //      if (res == true)
    //      {
    //        m_object.add_texture_to_object(texturePath);
    //      }
    //      return res;
    //    }
}

void Controller::delete_all_objects()
{
    m_object.deleteAllObjects();
}

void Controller::translateX_object(float x, unsigned indexObj)
{
    m_object.translateX_index(x / 20, indexObj);
}

void Controller::translateY_object(float y, unsigned indexObj)
{
    m_object.translateY_index(y / 20, indexObj);
}

void Controller::translateZ_object(float z, unsigned indexObj)
{
    m_object.translateZ_index(z / 20, indexObj);
}

void Controller::rotateX_object(float x, unsigned indexObj)
{
    m_object.rotateX_index(x, indexObj);
}

void Controller::rotateY_object(float y, unsigned indexObj)
{
    m_object.rotateY_index(y, indexObj);
}

void Controller::rotateZ_object(float z, unsigned indexObj)
{
    m_object.rotateZ_index(z, indexObj);
}

void Controller::scale_object(float s, unsigned indexObj)
{
    m_object.scale_index(s / 2, indexObj);
}

QMatrix4x4 Controller::modelMatrix_object(unsigned indexObj) const
{
    return m_object.modelMatrix_index(indexObj);
}

QOpenGLBuffer &Controller::vertexBuffer_object(unsigned indexObj)
{
    return m_object.vertexBuffer_index(indexObj);
}

QOpenGLBuffer &Controller::indexBuffer_object(unsigned indexObj)
{
    return m_object.indexBuffer_index(indexObj);
}

const InfoObject3D &Controller::info_object(unsigned indexObj) const
{
    return m_object.info_index(indexObj);
}

void Controller::addTexture_object(const QString &pathTexture, unsigned indexObj)
{
    m_object.addTexture_index(pathTexture, indexObj);
}

void Controller::deleteTextureFrom_object(unsigned indexObj)
{
    m_object.deleteTextureFrom_index(indexObj);
}

QOpenGLTexture *Controller::texture_object(unsigned indexObj)
{
    return m_object.texture_index(indexObj);
}

const QString &Controller::pathToTexture_object(unsigned indexObj) const
{
    m_object.pathToTexture_index(indexObj);
}

}  // namespace s21_3DViewer
