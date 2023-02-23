#pragma once

#include <QActionGroup>
#include <QButtonGroup>
#include <QCheckBox>
#include <QMainWindow>
#include <QProgressBar>
#include <QRadioButton>
#include <QSlider>

#include "../3rdparty/QtGifImage/src/gifimage/qgifimage.h"
#include "../controller/controller.h"
#include "gifmaker.h"

namespace Ui
{
class Viewer3D;
}

namespace s21_3DViewer
{
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

private:
  void groupVertexFormButtons();
  void groupLineFormButtons();

  //    void creatGroupToolBarMainAction();
  //  void creatGroupToolBarModelAction();
  //  void creatGroupToolBarLightAction();

  void setSlots();  // связывание сигналов со слотами

private slots:

  void on_tB_reset_rts_model_clicked();

  void on_slider_model_rotate_x_valueChanged(int value);
  void on_slider_model_rotate_y_valueChanged(int value);
  void on_slider_model_rotate_z_valueChanged(int value);

  void on_slider_model_translate_x_valueChanged(int value);
  void on_slider_model_translate_y_valueChanged(int value);
  void on_slider_model_translate_z_valueChanged(int value);

  void on_slider_model_scale_valueChanged(int value);

  void on_sB_min_translate_valueChanged(int arg1);
  void on_sB_max_translate_valueChanged(int arg1);

  void on_sB_min_scale_valueChanged(int arg1);
  void on_sB_max_scale_valueChanged(int arg1);

  void on_act_add_new_model_triggered(bool checked);
  void on_act_add_light_source_triggered(bool checked);
  void on_act_model_rtc_triggered(bool checked);

  void on_tB_model_min_max_rts_clicked();
  void on_tB_back_to_rts_model_clicked();

  void on_act_color_setting_model_triggered(bool checked);
  void on_act_settings_model_triggered(bool checked);
  void on_act_axis_rotate_triggered(bool checked);
  void on_act_light_position_triggered(bool checked);

  void on_tB_min_max_pos_light_pressed();
  void on_tB_back_to_pos_light_clicked();

  void on_act_light_color_triggered(bool checked);
  void on_act_light_settings_triggered(bool checked);

  void on_tB_min_max_light_setting_clicked();
  void on_tB_back_to_setting_light_clicked();

  void on_act_backup_triggered(bool checked);

private:
  void act_triggered(QAction* triggered, int page, bool checked);
  //  void action_projection();
  //  void action_open_folder();
  //  void action_light_on_off();
  //  void action_texture_triggered();
  //  void action_info_triggered();
  //  void action_delete_models();
  //  void action_screenshot();
  //  void action_make_gif();
  //  void action_make_gif_360();
  //  void action_shade();
  //  void action_axis_rotate();

  //  void closeEvent(QCloseEvent* e)
  //  {
  //    controller.save_settings();
  //    controller.save_camera();
  //    e->accept();
  //  }

private:
  enum pages
  {
    ADD_NEW_MODEL,
    ADD_NEW_LIGHT_SOURCE,
    BACKUP,
    MODEL_RTS,
    MODEL_MIN_MAX_RTS,
    MODEL_RGB_SETTING,
    MODEL_SETTING,
    MODEL_AUTO_ROTATE,
    LIGHT_POSITION,
    LIGHT_MIN_MAX_POSITION,
    LIGHT_RGB_SETTING,
    LIGHT_SETTING,
    LIGHT_SETTING_MIN_MAX
  };

  Ui::Viewer3D* ui;

  //  Controller& controller = Controller::getInstance();

  QButtonGroup m_groupVertForm;
  QButtonGroup m_groupLineForm;

  QAction* m_pressedAction;

  //  QThread* gif_thread_;
  //  GifMaker* gif_maker_;
  //  QGifImage* gif_image_;
  //  QProgressBar* gif_prog_bar_;

  //  enum axisRotate
  //  {
  //    X_AXIS,
  //    Y_AXIS,
  //    X_Y_AXIS
  //  };

  //  int axis_auto_rotate;
  //  float x_rot = 0;
  //  float y_rot = 0;
  //  enum turnAutoRotate
  //  {
  //    LEFT,
  //    RIGHT
  //  };
  //  bool turnAutoRotate_;
};
}  // namespace s21_3DViewer
