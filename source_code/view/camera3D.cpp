#include "camera3D.h"

namespace s21_3DViewer
{

Camera3D::Camera3D()
{
    setDefaultCamera();
}

Camera3D::Camera3D(const Camera3D &other)
{
    *this = other;
}

void Camera3D::operator=(const Camera3D &other)
{
    m_rotate = other.m_rotate;
    m_translate = other.m_translate;
    m_scale = other.m_scale;
}

void Camera3D::translate(const QVector3D &t)
{
    m_translate += t;
}

void Camera3D::rotate(const QQuaternion &r)
{
    m_rotate = r * m_rotate;
}

void Camera3D::scale(float s)
{
    m_scale += s;
}

QMatrix4x4 Camera3D::viewMatrix() const
{
    QMatrix4x4 viewMatrix;
    viewMatrix.setToIdentity();
    viewMatrix.translate(m_translate);
    viewMatrix.rotate(m_rotate);
    viewMatrix.scale(m_scale);
    return viewMatrix;
}

void Camera3D::setDefaultCamera()
{
    m_rotate = QQuaternion();
    m_translate = QVector3D(0.0, 0.0, -5.0);
    m_scale = 1.0;
}

void Camera3D::load_camera()
{
    QString pathToConfig = QCoreApplication::applicationDirPath() + "/settings/";

    if (!QDir(pathToConfig).exists())
        return;

    QString filename = pathToConfig + "CameraSettings.conf";

    std::fstream src(filename.toStdString(), std::fstream::in);

    if (!src.is_open())
        return;

    setlocale(LC_ALL, "en_US.UTF-8");

    while (src)
    {
        int type;
        float val;

        src >> type >> val;

        switch (type)
        {
        case kScalar:
            m_rotate.setScalar(val);
            break;
        case kRotateX:
            m_rotate.setX(val);
            break;
        case kRotateY:
            m_rotate.setY(val);
            break;
        case kRotateZ:
            m_rotate.setZ(val);
            break;
        case kTransalteX:
            m_translate.setX(val);
            break;
        case kTransalteY:
            m_translate.setY(val);
            break;
        case kTransalteZ:
            m_translate.setZ(val);
            break;
        case kScale:
            m_scale = val;
            break;
        default:
            break;
        }

        if (m_scale == 0.0)
            m_scale = 1.0;
    }
}

void Camera3D::save_camera()
{
    QString pathToConfig = QCoreApplication::applicationDirPath() + "/settings/";

    if (!QDir(pathToConfig).exists())
        QDir().mkdir(pathToConfig);

    QString filename = pathToConfig + "CameraSettings.conf";
    std::fstream tgt(filename.toStdString(), std::fstream::out | std::fstream::trunc);

    if (!tgt.is_open())
        return;

    setlocale(LC_ALL, "en_US.UTF-8");

    tgt << kScalar << " " << m_rotate.scalar() << std::endl;
    tgt << kRotateX << " " << m_rotate.vector().x() << std::endl;
    tgt << kRotateY << " " << m_rotate.vector().y() << std::endl;
    tgt << kRotateZ << " " << m_rotate.vector().z() << std::endl;
    tgt << kTransalteX << " " << m_translate.x() << std::endl;
    tgt << kTransalteY << " " << m_translate.y() << std::endl;
    tgt << kTransalteZ << " " << m_translate.z() << std::endl;
    tgt << kScale << " " << m_scale << std::endl;
}

}
