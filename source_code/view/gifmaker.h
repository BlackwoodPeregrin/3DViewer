#pragma once

#include <QDir>
#include <QEventLoop>
#include <QMutex>
#include <QObject>
#include <QThread>
#include <QTimer>

#include "openGLWidget.h"

namespace s21_3DViewer {

enum WorkMode { kGifMode, kRotateMode };

class GifMaker : public QObject {
  Q_OBJECT

 public:
  explicit GifMaker(QObject *parent = 0) : QObject(parent) {
    working_ = false;
    abort_ = false;
    mode_ = WorkMode::kGifMode;
  }

  void RequestWork() {
    QString pathToGif = QCoreApplication::applicationDirPath() + "/gifs/";
    if (!QDir(pathToGif).exists()) {
      QDir().mkdir(pathToGif);
    }
    mutex_.lock();
    working_ = true;
    abort_ = false;
    mode_ = WorkMode::kGifMode;
    mutex_.unlock();

    emit WorkRequested();
  }

  void RequestIdleRotate() {
    mutex_.lock();
    working_ = true;
    abort_ = false;
    mode_ = WorkMode::kRotateMode;
    mutex_.unlock();

    emit IdleRotateRequested();
  }

  void Abort() {
    mutex_.lock();
    if (working_) {
      abort_ = true;
    }
    mutex_.unlock();
  }

 private:
  bool abort_;
  bool working_;
  QMutex mutex_;
  unsigned mode_;

 signals:
  void WorkRequested();
  void IdleRotateRequested();
  void RequestTmpShot();
  void RequestIdleRotateStep();
  void SaveGif();
  void Finished();

 public slots:
  void DoWork() {
    mutex_.lock();
    unsigned mode = mode_;
    mutex_.unlock();
    if (mode == WorkMode::kGifMode)
      WorkMakeGif();
    else
      EndlessIdleRotate();
  }

 private:
  void WorkMakeGif() {
    for (int i{}; i < 50; i++) {
      mutex_.lock();
      bool abort = abort_;
      mutex_.unlock();

      if (abort) {
        break;
      }

      QEventLoop loop;
      QTimer::singleShot(100, &loop, SLOT(quit()));
      loop.exec();
      emit RequestTmpShot();
    }

    mutex_.lock();
    working_ = false;
    mutex_.unlock();
    emit SaveGif();
    emit Finished();
  }

  void EndlessIdleRotate() {
    bool abort(false);
    while (!abort) {
      mutex_.lock();
      abort = abort_;
      mutex_.unlock();

      QEventLoop loop;
      QTimer::singleShot(20, &loop, SLOT(quit()));
      loop.exec();
      emit RequestIdleRotateStep();
    }
    mutex_.lock();
    working_ = false;
    mutex_.unlock();
    emit Finished();
  }
};

}  // namespace s21_3DViewer
