#include "camera3D.h"

namespace s21_3DViewer {
Camera3D::Camera3D() { load_camera(); }

Camera3D::Camera3D(const Camera3D &other) { *this = other; }

void Camera3D::operator=(const Camera3D &other) {
    viewMatrix_ = other.viewMatrix_;
    rotate_ = other.rotate_;
    translate_ = other.translate_;
    scale_ = other.scale_;
}

void Camera3D::translate(const QVector3D &t) { translate_ += t; }

void Camera3D::rotate(const QQuaternion &r) { rotate_ = r * rotate_; }

void Camera3D::scale(const float &s) { scale_ += s; }

const QMatrix4x4 &Camera3D::getViewMatrix() {
    viewMatrix_.setToIdentity();
    viewMatrix_.translate(translate_);
    viewMatrix_.rotate(rotate_);
    viewMatrix_.scale(scale_);
    return viewMatrix_;
}

void Camera3D::set_default_camera() {
    rotate_ = QQuaternion();
    translate_ = QVector3D(0.0, 0.0, -5.0);
    scale_ = 1.0;
}

void Camera3D::load_camera() {
    set_default_camera();
    QString config_file = QCoreApplication::applicationDirPath() + "/settings/";
    if (QDir(config_file).exists()) {
        std::string filename = config_file.toStdString() + "CameraSettings.conf";
        std::fstream src(filename, std::fstream::in);
        if (src.is_open()) {
            setlocale(LC_ALL, "en_US.UTF-8");
            std::string line{}, opt{}, val{};
            while (src) {
                std::getline(src, line);
                int pos = line.find(' ');
                if (pos != -1) {
                    opt = line.substr(0, pos);
                    val = line.substr(pos + 1);
                    if (opt == "rotate_scalar") {
                        rotate_.setScalar(stof(val));
                    } else if (opt == "rotate_vector_x") {
                        rotate_.setX(stof(val));
                    } else if (opt == "rotate_vector_y") {
                        rotate_.setY(stof(val));
                    } else if (opt == "rotate_vector_z") {
                        rotate_.setZ(stof(val));
                    } else if (opt == "translate_vector_x") {
                        translate_.setX(stof(val));
                    } else if (opt == "translate_vector_y") {
                        translate_.setY(stof(val));
                    } else if (opt == "translate_vector_z") {
                        translate_.setZ(stof(val));
                    } else if (opt == "scale") {
                        scale_ = stof(val);
                    }
                }
            }
            if (scale_ == 0.0) scale_ = 1.0;
            src.close();
        }
    }
}

void Camera3D::save_camera() {
    QString config_file = QCoreApplication::applicationDirPath() + "/settings/";
    if (!QDir(config_file).exists()) {
        QDir().mkdir(config_file);
    }
    std::string filename = config_file.toStdString() + "CameraSettings.conf";
    std::fstream tgt(filename, std::fstream::out | std::fstream::trunc);
    if (tgt.is_open()) {
        setlocale(LC_ALL, "en_US.UTF-8");
        tgt << "rotate_scalar " << rotate_.scalar() << std::endl;
        tgt << "rotate_vector_x " << rotate_.vector().x() << std::endl;
        tgt << "rotate_vector_y " << rotate_.vector().y() << std::endl;
        tgt << "rotate_vector_z " << rotate_.vector().z() << std::endl;
        tgt << "translate_vector_x " << translate_.x() << std::endl;
        tgt << "translate_vector_y " << translate_.y() << std::endl;
        tgt << "translate_vector_z " << translate_.z() << std::endl;
        tgt << "scale " << scale_ << std::endl;
    }
}
}

