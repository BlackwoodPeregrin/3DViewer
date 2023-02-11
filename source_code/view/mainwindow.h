#pragma once

#include <QActionGroup>
#include <QButtonGroup>
#include <QCheckBox>
#include <QMainWindow>
#include <QProgressBar>
#include <QRadioButton>

#include "../3rdparty/QtGifImage/src/gifimage/qgifimage.h"
#include "../controller/controller.h"
#include "gifmaker.h"

namespace Ui
{
class viewerMainWindow;
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
  void groupingVertexFormButtons();  // группировка кнопок отвечающих за тип вершин
  void groupingLineFormButtons();    // группировка кнопок отвечающих за тип линий
  void groupingActionLowerToolBar();  // группировка actions находящихся на
                                      // нижнем toolBar
  void groupingActionUpperToolBar();  // группировка actions находящихся на
                                      // верхнем toolBar
  void setSlots();                    // связывание сигналов со слотами
  void hideSetLines();                // скрыть натсройки линий на панели натсроек
  void showSetLines();  // показать натсройки линий на панели натсроек
  void installSettings(bool first_load);  // установка натсроек из конфиг файла

private slots:
  void triggeredGroupActionLower(QAction* action);
  void triggeredGroupActionUpper(QAction* action);

  void clickedVertForm(int idButton);
  void clickedLineForm(int idButton);

  void comboBoxIndexChanged(int drawType);

  void colorsButtonClicked();

  void slidersModelChanged(int value);
  void doubleSpinboxModelChanged(double value);

  void slidersModelSettingsChanged(int value);
  void doubleSpinBoxModelSettingsChanged(double value);

  void slidersLightSettingsChanged(int value);
  void doubleSpinBoxLightChanged(double value);

  void slidersSettingsScreenChanged(int value);
  void doubleSpinBoxSettingsScreenChanged(double value);

  void buttonResizeWindowClicked();
  void set_doubleSpinBox_width_height();

  void buttonPrevConditionClicked();
  void buttonNextConditionClicked();
  void buttonSaveConditionClicked();
  void buttonClearConditionClicked();

  void doubleSpinBoxMinMaxChanged(double value);

  void buttonSettingsMinMaxClicked();

  void buttonBackToModelClicked();

  void buttonResetModelClicked();

  void MakeTmpShot();
  void SaveGifImage();

  void MakeIdleRotateStep();

  void buttonsRotateAxisClicked();
  void buttonsPlayStopRotateAxisClicked();
  void buttonsTurnRotateAxisClicked();

private:
  void action_projection();
  void action_open_folder();
  void action_light_on_off();
  void action_texture_triggered();
  void action_info_triggered();
  void action_delete_models();
  void action_screenshot();
  void action_make_gif();
  void action_make_gif_360();
  void action_shade();
  void action_axis_rotate();

  void closeEvent(QCloseEvent* e)
  {
    controller.save_settings();
    controller.save_camera();
    e->accept();
  }

private:
  enum pages
  {
    HIDE = -1,
    FIRST_PAGE,
    SECOND_PAGE,
    THIRD_PAGE,
    FOURTH_PAGE,
    FIFTH_PAGE,
    SIXTH_PAGE,
    SEVENTH_PAGE,
    EIGHTH_PAGE,
  };
  Ui::viewerMainWindow* ui;
  Controller& controller = Controller::getInstance();
  int contentPage_;
  QButtonGroup groupVertForm_;
  QButtonGroup groupLineForm_;
  QActionGroup* groupActionLower_;
  QActionGroup* groupActionUpper_;

  QThread* gif_thread_;
  GifMaker* gif_maker_;
  QGifImage* gif_image_;
  QProgressBar* gif_prog_bar_;

  enum axisRotate
  {
    X_AXIS,
    Y_AXIS,
    X_Y_AXIS
  };
  int axis_auto_rotate;
  float x_rot = 0;
  float y_rot = 0;
  enum turnAutoRotate
  {
    LEFT,
    RIGHT
  };
  bool turnAutoRotate_;
};
}  // namespace s21_3DViewer
