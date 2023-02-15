#include "drawSetting.h"

namespace s21_3DViewer
{
DrawSetting::DrawSetting()
{
    setDefault();
}

DrawSetting::DrawSetting(const DrawSetting &other)
{
    *this = other;
}

void DrawSetting::operator=(const DrawSetting &other)
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
}

void DrawSetting::setDefault()
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
}

bool DrawSetting::lineType() const
{
    return m_lineType;
}

float DrawSetting::lineSize() const
{
    return m_lineSize;
}

const float *DrawSetting::lineColor() const
{
    return m_lineColor;
}

float DrawSetting::lineColorRed() const
{
    return m_lineColor[RGBA::RED];
}

float DrawSetting::lineColorGreen() const
{
    return m_lineColor[RGBA::GREEN];
}

float DrawSetting::lineColorBlue() const
{
    return m_lineColor[RGBA::BLUE];
}

float DrawSetting::lineColorAlpha() const
{
    return m_lineColor[RGBA::ALPHA];
}

unsigned DrawSetting::vertType() const
{
    return m_vertType;
}

float DrawSetting::vertSize() const
{
    return m_vertSize;
}

const float *DrawSetting::vertColor() const
{
    return m_vertColor;
}

float DrawSetting::vertColorRed() const
{
    return m_vertColor[RGBA::RED];
}

float DrawSetting::vertColorGreen() const
{
    return m_vertColor[RGBA::GREEN];
}

float DrawSetting::vertColorBlue() const
{
    return m_vertColor[RGBA::BLUE];
}

float DrawSetting::vertColorAlpha() const
{
    return m_vertColor[RGBA::ALPHA];
}

const float *DrawSetting::surfacesColor() const
{
    return m_surfacesColor;
}

float DrawSetting::surfacesColorRed() const
{
    return m_surfacesColor[RGBA::RED];
}

float DrawSetting::surfacesColorGreen() const
{
    return m_surfacesColor[RGBA::GREEN];
}

float DrawSetting::surfacesColorBlue() const
{
    return m_surfacesColor[RGBA::BLUE];
}

float DrawSetting::surfacesColorAlpha() const
{
    return m_surfacesColor[RGBA::ALPHA];
}

unsigned DrawSetting::drawType() const
{
    return m_drawType;
}

void DrawSetting::setLineType(bool lineType)
{
    m_lineType = lineType;
}

void DrawSetting::setLineSize(float lineSize)
{
    m_lineSize = lineSize;
}

void DrawSetting::setLineColor(float r, float g, float b, float a)
{
    m_lineColor[RGBA::RED] = r;
    m_lineColor[RGBA::GREEN] = g;
    m_lineColor[RGBA::BLUE] = b;
    m_lineColor[RGBA::ALPHA] = a;
}

void DrawSetting::setLineColor(const float color[])
{
    for (int i = 0; i < RGBA::N; ++i)
        m_lineColor[i] = color[i];
}

void DrawSetting::setVertType(unsigned vertType)
{
    m_vertType = vertType;
}

void DrawSetting::setVertSize(float vertSize)
{
    m_vertSize = vertSize;
}

void DrawSetting::setVertColor(float r, float g, float b, float a)
{
    m_vertColor[RGBA::RED] = r;
    m_vertColor[RGBA::GREEN] = g;
    m_vertColor[RGBA::BLUE] = b;
    m_vertColor[RGBA::ALPHA] = a;
}

void DrawSetting::setVertColor(const float color[])
{
    for (int i = 0; i < RGBA::N; ++i)
        m_vertColor[i] = color[i];
}

void DrawSetting::setSurfacesColor(float r, float g, float b, float a)
{
    m_surfacesColor[RGBA::RED] = r;
    m_surfacesColor[RGBA::GREEN] = g;
    m_surfacesColor[RGBA::BLUE] = b;
    m_surfacesColor[RGBA::ALPHA] = a;
}

void DrawSetting::setSurfacesColor(const float color[])
{
    for (int i = 0; i < RGBA::N; ++i)
        m_surfacesColor[i] = color[i];
}

void DrawSetting::setDrawType(unsigned drawType)
{
    m_drawType = drawType;
}

void DrawSetting::save(unsigned numObject)
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
}

void DrawSetting::load(unsigned numObject)
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

        default:
            break;
        }
    }
}

}  // namespace s21_3DViewer
