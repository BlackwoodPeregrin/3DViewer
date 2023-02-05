#include "mainwindow.h"

#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QQuaternion>
#include <QRect>
#include <QScreen>

#include "../controller/controller.h"
#include "ui_mainwindow.h"

namespace s21_3DViewer {

constexpr int kGifWidth = 640;
constexpr int kGifHeight = 480;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::viewerMainWindow),
      groupActionLower_(new QActionGroup(this)),
      groupActionUpper_(new QActionGroup(this)),
      gif_thread_(new QThread()),
      gif_maker_(new GifMaker()),
      gif_image_(nullptr) {
  ui->setupUi(this);

  // for gifs
  gif_maker_->moveToThread(gif_thread_);
  gif_prog_bar_ = new QProgressBar(this);
  gif_prog_bar_->setStyleSheet(
      "QProgressBar {\n"
      "border: 2px solid black;\n"
      "border-radius: 5px;\n"
      "\ntext-align: center;\n"
      "font-size: 15px;\n"
      "font-family: Comic Sans MS;\n"
      "}\n"
      "QProgressBar::chunk {\n"
      "background-color: rgba(210, 73, 182, 110);\n"
      "width: 20px;\n"
      "}");

  ui->statusBar->addPermanentWidget(gif_prog_bar_);

  gif_prog_bar_->setVisible(false);
  gif_prog_bar_->setMinimum(0);
  gif_prog_bar_->setMaximum(50);
  gif_prog_bar_->setMaximumWidth(kGifWidth / 2);

  /*---группировка кнопок отвечающих за тип вершин---*/
  groupingVertexFormButtons();
  /*---группировка кнопок отвечающих за тип линий---*/
  groupingLineFormButtons();
  /*---группировка actions находящихся на нижнем toolBar---*/
  groupingActionLowerToolBar();
  /*---группировка actions находящихся на верхнем toolBar---*/
  groupingActionUpperToolBar();
  /*-------------------------------------------------------*/
  installSettings(true);  // установка натсроек из конфиг файла
  setSlots();  // связывание сигналов со слотами
}

MainWindow::~MainWindow() {
  gif_maker_->Abort();
  gif_thread_->wait();
  delete gif_thread_;
  delete gif_maker_;
  delete gif_image_;

  delete ui;
  delete groupActionLower_;
  delete groupActionUpper_;
}

void MainWindow::groupingVertexFormButtons() {
  groupVertForm_.addButton(ui->checkBox_vert_form_none);
  groupVertForm_.setId(ui->checkBox_vert_form_none, vertType::None);
  groupVertForm_.addButton(ui->checkBox_vert_form_circle);
  groupVertForm_.setId(ui->checkBox_vert_form_circle, vertType::Circle);
  groupVertForm_.addButton(ui->checkBox_vert_form_square);
  groupVertForm_.setId(ui->checkBox_vert_form_square, vertType::Square);
}

void MainWindow::groupingLineFormButtons() {
  groupLineForm_.addButton(ui->checkBox_line_form_solid);
  groupLineForm_.setId(ui->checkBox_line_form_solid, lineType::Solid);
  groupLineForm_.addButton(ui->checkBox_line_form_dashed);
  groupLineForm_.setId(ui->checkBox_line_form_dashed, lineType::Dashed);
}

void MainWindow::groupingActionLowerToolBar() {
  groupActionLower_->addAction(ui->act_modelCamera);
  ui->act_modelCamera->setData(pages::FIRST_PAGE);
  groupActionLower_->addAction(ui->act_color);
  ui->act_color->setData(pages::SECOND_PAGE);
  groupActionLower_->addAction(ui->act_settings_model);
  ui->act_settings_model->setData(pages::THIRD_PAGE);
  groupActionLower_->addAction(ui->act_light_settings);
  ui->act_light_settings->setData(pages::FOURTH_PAGE);
  groupActionLower_->addAction(ui->act_settings_screen);
  ui->act_settings_screen->setData(pages::FIFTH_PAGE);
  groupActionLower_->addAction(ui->act_backup);
  ui->act_backup->setData(pages::SIXTH_PAGE);
}

void MainWindow::groupingActionUpperToolBar() {
  groupActionUpper_->addAction(ui->act_folder);
  groupActionUpper_->addAction(ui->act_make_gif);
  groupActionUpper_->addAction(ui->act_gif_360);
  groupActionUpper_->addAction(ui->act_screenShot);
  groupActionUpper_->addAction(ui->act_info);
  groupActionUpper_->addAction(ui->act_texture);
  groupActionUpper_->addAction(ui->act_light_on_off);
  groupActionUpper_->addAction(ui->act_shade);
  groupActionUpper_->addAction(ui->act_projection);
  groupActionUpper_->addAction(ui->act_axis_rotate);
  groupActionUpper_->addAction(ui->act_delete_models);
}

void MainWindow::setSlots() {
  /*--------------QActionGroups-------------------*/
  // группа QAction нижнего toolBar
  connect(groupActionLower_, SIGNAL(triggered(QAction *)), this,
          SLOT(triggeredGroupActionLower(QAction *)));
  // группа QAction верхнего toolBar
  connect(groupActionUpper_, SIGNAL(triggered(QAction *)), this,
          SLOT(triggeredGroupActionUpper(QAction *)));
  /*----------------------------------------*/

  /*-------------QButtonGroups--------------*/
  // группа кнопок для изменения типа вершин
  connect(&groupVertForm_, SIGNAL(idClicked(int)), this,
          SLOT(clickedVertForm(int)));
  // группа кнопок для изменения типа линий
  connect(&groupLineForm_, SIGNAL(idClicked(int)), this,
          SLOT(clickedLineForm(int)));
  /*----------------------------------------*/

  /*-------------QComboBox--------------*/
  // комбобокс для изменения типа отрисовки
  connect(ui->comboBox_drawingType, SIGNAL(currentIndexChanged(int)), this,
          SLOT(comboBoxIndexChanged(int)));
  /*------------------------------------*/

  /*-----QToolButtons------*/
  // задний фон объекта
  connect(ui->backgroundColorButton, SIGNAL(clicked()), this,
          SLOT(colorsButtonClicked()));
  // поверхности объекта
  connect(ui->surfaceColorButton, SIGNAL(clicked()), this,
          SLOT(colorsButtonClicked()));
  // вершины объекта
  connect(ui->vertexColorButton, SIGNAL(clicked()), this,
          SLOT(colorsButtonClicked()));
  // линии объекта
  connect(ui->linesColorButton, SIGNAL(clicked()), this,
          SLOT(colorsButtonClicked()));
  // изменение размера окна
  connect(ui->toolButton_resize_screen, SIGNAL(clicked()), this,
          SLOT(buttonResizeWindowClicked()));
  // предыдущее сосотояние модели
  connect(ui->toolButton_prev_condition, SIGNAL(clicked()), this,
          SLOT(buttonPrevConditionClicked()));
  // следующее сосотояние модели
  connect(ui->toolButton_next_condition, SIGNAL(clicked()), this,
          SLOT(buttonNextConditionClicked()));
  // сохранение сосотояня модели
  connect(ui->toolButton_save_condition, SIGNAL(clicked()), this,
          SLOT(buttonSaveConditionClicked()));
  // очистка состояний модели
  connect(ui->toolButton_clear_conditions, SIGNAL(clicked()), this,
          SLOT(buttonClearConditionClicked()));
  // настройка краевых значений камеры модели
  connect(ui->toolButton_model_min_max_settings, SIGNAL(clicked()), this,
          SLOT(buttonSettingsMinMaxClicked()));
  // кнопка для возврата к изменению матрицы модели
  connect(ui->toolButto_back_to_modelCamera, SIGNAL(clicked()), this,
          SLOT(buttonBackToModelClicked()));
  // кнопка для сброса матрицы модели к дэфолтным
  connect(ui->toolButton_reset_matrix_model, SIGNAL(clicked()), this,
          SLOT(buttonResetModelClicked()));
  // кнопки для автоповоротов по осям
  connect(ui->toolButton_x_axis_rotate, SIGNAL(clicked()), this,
          SLOT(buttonsRotateAxisClicked()));
  connect(ui->toolButton_y_axis_rotate, SIGNAL(clicked()), this,
          SLOT(buttonsRotateAxisClicked()));
  connect(ui->toolButton_x_y_axis_rotate, SIGNAL(clicked()), this,
          SLOT(buttonsRotateAxisClicked()));
  connect(ui->toolButton_right_auto_rotate, SIGNAL(clicked()), this,
          SLOT(buttonsTurnRotateAxisClicked()));
  connect(ui->toolButton_left_auto_rotate, SIGNAL(clicked()), this,
          SLOT(buttonsTurnRotateAxisClicked()));
  connect(ui->toolButton_play_stop_rotate, SIGNAL(clicked()), this,
          SLOT(buttonsPlayStopRotateAxisClicked()));
  /*----------------------*/

  /*-----QPushButtons------*/
  // пятна блика освещения на объекте
  connect(ui->pushButton_specular_color, SIGNAL(clicked()), this,
          SLOT(colorsButtonClicked()));
  /*----------------------*/

  /*------------QSliders-----------------*/
  // слайдеры для изменения матрциы модели
  connect(ui->slider_M_RX, SIGNAL(valueChanged(int)), this,
          SLOT(slidersModelChanged(int)));
  connect(ui->slider_M_RY, SIGNAL(valueChanged(int)), this,
          SLOT(slidersModelChanged(int)));
  connect(ui->slider_M_RZ, SIGNAL(valueChanged(int)), this,
          SLOT(slidersModelChanged(int)));
  connect(ui->slider_M_TX, SIGNAL(valueChanged(int)), this,
          SLOT(slidersModelChanged(int)));
  connect(ui->slider_M_TY, SIGNAL(valueChanged(int)), this,
          SLOT(slidersModelChanged(int)));
  connect(ui->slider_M_TZ, SIGNAL(valueChanged(int)), this,
          SLOT(slidersModelChanged(int)));
  connect(ui->slider_M_Scale, SIGNAL(valueChanged(int)), this,
          SLOT(slidersModelChanged(int)));
  // слайдеры для изменения толщины линий и размера вершин
  connect(ui->slider_vertex_size, SIGNAL(valueChanged(int)), this,
          SLOT(slidersModelSettingsChanged(int)));
  connect(ui->slider_line_size, SIGNAL(valueChanged(int)), this,
          SLOT(slidersModelSettingsChanged(int)));
  // слайдер для изменения specular фактора
  connect(ui->slider_specular_factor, SIGNAL(valueChanged(int)), this,
          SLOT(slidersLightSettingsChanged(int)));
  // слайдер для изменения силы света
  connect(ui->slider_light_power, SIGNAL(valueChanged(int)), this,
          SLOT(slidersLightSettingsChanged(int)));
  // слайдеры для изменения rgb оснвоного освещения
  connect(ui->slider_light_color_red, SIGNAL(valueChanged(int)), this,
          SLOT(slidersLightSettingsChanged(int)));
  connect(ui->slider_light_color_green, SIGNAL(valueChanged(int)), this,
          SLOT(slidersLightSettingsChanged(int)));
  connect(ui->slider_light_color_blue, SIGNAL(valueChanged(int)), this,
          SLOT(slidersLightSettingsChanged(int)));
  // слайдер для изменения ширины экрана приложения
  connect(ui->slider_width_screen, SIGNAL(valueChanged(int)), this,
          SLOT(slidersSettingsScreenChanged(int)));
  // слайдер для изменения высоты экрана приложения
  connect(ui->slider_height_screen, SIGNAL(valueChanged(int)), this,
          SLOT(slidersSettingsScreenChanged(int)));
  /*------------------------------------*/

  /*------------QDoubleSpinBoxes-----------------*/
  // спинбоксы матрицы модели
  connect(ui->doubleSpinBox_M_RX, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinboxModelChanged(double)));
  connect(ui->doubleSpinBox_M_RY, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinboxModelChanged(double)));
  connect(ui->doubleSpinBox_M_RZ, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinboxModelChanged(double)));
  connect(ui->doubleSpinBox_M_TX, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinboxModelChanged(double)));
  connect(ui->doubleSpinBox_M_TY, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinboxModelChanged(double)));
  connect(ui->doubleSpinBox_M_TZ, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinboxModelChanged(double)));
  connect(ui->doubleSpinBox_M_Scale, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinboxModelChanged(double)));
  // спинбоксы освещения объекта
  connect(ui->doubleSpinBox_x, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinBoxLightChanged(double)));
  connect(ui->doubleSpinBox_y, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinBoxLightChanged(double)));
  connect(ui->doubleSpinBox_z, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinBoxLightChanged(double)));
  connect(ui->doubleSpinBox_ambient_factor, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinBoxLightChanged(double)));
  // спинбокс для изменения толщины линий объекта
  connect(ui->doubleSpinBox_line_size, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinBoxModelSettingsChanged(double)));
  // спинбокс для изменения толщины вершин объекта
  connect(ui->doubleSpinBox_vert_size, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinBoxModelSettingsChanged(double)));
  // спинбокс для изменения ширины экрана приложения
  connect(ui->doubleSpinBox_width_screen, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinBoxSettingsScreenChanged(double)));
  // спинбокс для изменения высоты экрана приложения
  connect(ui->doubleSpinBox_height_screen, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinBoxSettingsScreenChanged(double)));
  // спинбоксы для изменения максимальных и минимальных значений натсроек
  // матрицы модели
  connect(ui->doubleSpinBox_min_translate, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinBoxMinMaxChanged(double)));
  connect(ui->doubleSpinBox_max_translate, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinBoxMinMaxChanged(double)));
  connect(ui->doubleSpinBox_min_scale, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinBoxMinMaxChanged(double)));
  connect(ui->doubleSpinBox_max_scale, SIGNAL(valueChanged(double)), this,
          SLOT(doubleSpinBoxMinMaxChanged(double)));
  /*---------------------------------------------*/
  connect(ui->openGLWidget, SIGNAL(resized()), this,
          SLOT(set_doubleSpinBox_width_height()));

  // gifmaker
  connect(gif_maker_, SIGNAL(WorkRequested()), gif_thread_, SLOT(start()));
  connect(gif_thread_, SIGNAL(started()), gif_maker_, SLOT(DoWork()));
  connect(gif_maker_, SIGNAL(RequestTmpShot()), this, SLOT(MakeTmpShot()));
  connect(gif_maker_, SIGNAL(Finished()), gif_thread_, SLOT(quit()),
          Qt::DirectConnection);
  connect(gif_maker_, SIGNAL(SaveGif()), this, SLOT(SaveGifImage()));

  // endless camera rotation
  connect(gif_maker_, SIGNAL(IdleRotateRequested()), gif_thread_,
          SLOT(start()));
  connect(gif_maker_, SIGNAL(RequestIdleRotateStep()), this,
          SLOT(MakeIdleRotateStep()));
}

void MainWindow::hideSetLines() {
  ui->label_line_form->hide();
  ui->checkBox_line_form_solid->hide();
  ui->checkBox_line_form_dashed->hide();
  ui->label_line_size->hide();
  ui->slider_line_size->hide();
  ui->doubleSpinBox_line_size->hide();
}

void MainWindow::showSetLines() {
  ui->label_line_form->show();
  ui->checkBox_line_form_solid->show();
  ui->checkBox_line_form_dashed->show();
  ui->label_line_size->show();
  ui->slider_line_size->show();
  ui->doubleSpinBox_line_size->show();
}

void MainWindow::installSettings(bool first_load) {
  QVector4D color;

  /*---базовые натсройки автоповоротов по оси, содержаться в это классе---*/
  axis_auto_rotate = axisRotate::Y_AXIS;
  ui->toolButton_play_stop_rotate->setText("play");
  ui->toolButton_play_stop_rotate->setIcon(QIcon(":/icons_ui/play-button.png"));

  turnAutoRotate_ = turnAutoRotate::RIGHT;
  ui->toolButton_right_auto_rotate->setIcon(
      QIcon(":/icons_ui/auto_rotate_right_YES.png"));
  ui->toolButton_left_auto_rotate->setIcon(
      QIcon(":/icons_ui/auto_rotate_left_NO.png"));

  /*---подгружаем натсройки проекции из файла---*/
  unsigned projection = controller.get_projection_sets();
  if (projection == projType::Central) {
    ui->act_projection->setIcon(QIcon(":/icons_ui/perpectiveProj.png"));
  } else if (projection == projType::Parallel) {
    ui->act_projection->setIcon(QIcon(":/icons_ui/parallProj.png"));
  }

  /*---подгружаем тип освещения из файла---*/
  bool typeShade = controller.getLightShade();
  if (typeShade == shaddingType::Flat) {
    ui->act_shade->setIcon(QIcon(":/icons_ui/Flat_shade.png"));
  } else if (typeShade == shaddingType::Soft) {
    ui->act_shade->setIcon(QIcon(":/icons_ui/Soft_shade.png"));
  }

  /*---подгружаем путь текстуры из файла---*/
  QString texturePath = controller.get_texture_path_sets();
  if (texturePath.isEmpty()) {
    ui->act_texture->setIcon(QIcon(":/icons_ui/material_no.png"));
    ui->act_texture->setIconText("NO_texture");
  } else {
    ui->act_texture->setIcon(QIcon(":/icons_ui/material.png"));
    ui->act_texture->setIconText("HAVE_texture");
  }

  /*---подгружаем натсройки страницы натсроек модели---*/
  ui->slider_line_size->setValue(controller.get_line_size_sets());
  ui->doubleSpinBox_line_size->setValue(controller.get_line_size_sets());
  ui->slider_vertex_size->setValue(controller.get_vert_size_sets());
  ui->doubleSpinBox_vert_size->setValue(controller.get_vert_size_sets());

  unsigned drawType = controller.get_draw_type_sets();
  if (drawType == typeDraw::Points) {
    hideSetLines();
    ui->checkBox_vert_form_none->hide();
  } else if (drawType == typeDraw::Triangles) {
    hideSetLines();
  } else {
    showSetLines();
  }
  ui->comboBox_drawingType->setCurrentIndex(drawType);

  unsigned typeVertex = controller.get_vert_type_sets();
  if (typeVertex == vertType::None) {
    ui->checkBox_vert_form_none->setChecked(true);
  } else if (typeVertex == vertType::Circle) {
    ui->checkBox_vert_form_circle->setChecked(true);
  } else if (typeVertex == vertType::Square) {
    ui->checkBox_vert_form_square->setChecked(true);
  }

  unsigned typeLine = controller.get_line_type_sets();
  if (typeLine == lineType::Solid) {
    ui->checkBox_line_form_solid->setChecked(true);
  } else if (typeLine == lineType::Dashed) {
    ui->checkBox_line_form_dashed->setChecked(true);
  }

  /*---подгружаем натсройки страницы цветов---*/
  color = controller.get_bg_color_sets();
  QString css = QString("background-color: rgb(%1, %2, %3);")
                    .arg(color[RGBA::RED] * 255)
                    .arg(color[RGBA::GREEN] * 255)
                    .arg(color[RGBA::BLUE] * 255);
  ui->color_bg->setStyleSheet(css);

  color = controller.get_surfaces_color_sets();
  css = QString("background-color: rgb(%1, %2, %3);")
            .arg(color[RGBA::RED] * 255)
            .arg(color[RGBA::GREEN] * 255)
            .arg(color[RGBA::BLUE] * 255);
  ui->color_surface->setStyleSheet(css);

  color = controller.get_vert_color_sets();
  css = QString("background-color: rgb(%1, %2, %3);")
            .arg(color[RGBA::RED] * 255)
            .arg(color[RGBA::GREEN] * 255)
            .arg(color[RGBA::BLUE] * 255);
  ui->color_vertex->setStyleSheet(css);

  color = controller.get_line_color_sets();
  css = QString("background-color: rgb(%1, %2, %3);")
            .arg(color[RGBA::RED] * 255)
            .arg(color[RGBA::GREEN] * 255)
            .arg(color[RGBA::BLUE] * 255);
  ui->color_line->setStyleSheet(css);

  /*----------подгружаем натсройки света---------------*/
  bool lightStatus = controller.getLightStatus();
  if (lightStatus == lightStatus::ON) {
    ui->act_light_on_off->setIcon(QIcon(":/icons_ui/light_on.png"));
    ui->act_light_on_off->setIconText("ON_light");
  } else if (lightStatus == lightStatus::OFF) {
    ui->act_light_on_off->setIcon(QIcon(":/icons_ui/light_off.png"));
    ui->act_light_on_off->setIconText("OFF_light");
  }
  QVector4D lightPosition = controller.getLightPosition();
  ui->doubleSpinBox_x->setValue(lightPosition.x());
  ui->doubleSpinBox_y->setValue(lightPosition.y());
  ui->doubleSpinBox_z->setValue(lightPosition.z());
  ui->slider_light_power->setValue(controller.getLightPower() * 5);
  ui->slider_specular_factor->setValue(controller.getSpecularFactor());
  color = controller.getSpecularColor();
  css = QString("background-color: rgb(%1, %2, %3);")
            .arg(color[RGBA::RED] * 255)
            .arg(color[RGBA::GREEN] * 255)
            .arg(color[RGBA::BLUE] * 255);
  ui->color_specular_color->setStyleSheet(css);
  QVector4D lightColor = controller.getLightColor();
  ui->slider_light_color_red->setValue(lightColor.x() * 255);
  ui->slider_light_color_green->setValue(lightColor.y() * 255);
  ui->slider_light_color_blue->setValue(lightColor.z() * 255);
  ui->doubleSpinBox_ambient_factor->setValue(controller.getAmbientFactor());

  /*----------подгружаем натсройки разширеня экрана---------------*/

  float width = controller.get_windowWidth_sets();
  float height = controller.get_windowHeight_sets();
  ui->slider_width_screen->setValue(width);
  ui->doubleSpinBox_width_screen->setValue(width);
  ui->slider_height_screen->setValue(height);
  ui->doubleSpinBox_height_screen->setValue(height);
  resize(width, height);

  /*---панель инструментов по умолчанию скрыта---*/
  if (first_load == true) {
    ui->content->hide();
    contentPage_ = pages::HIDE;
  }
}

void MainWindow::triggeredGroupActionLower(QAction *action) {
  if (action->data() == contentPage_) {
    contentPage_ = pages::HIDE;
    action->setChecked(false);
    ui->content->hide();
  } else {
    if (action->data().toInt() == pages::FIRST_PAGE) {
      if (controller.have_objects()) {
        contentPage_ = action->data().toInt();
        ui->content->setCurrentIndex(contentPage_);
        ui->content->show();
      } else {
        ui->act_modelCamera->setChecked(false);
        if (contentPage_ == ui->act_color->data()) {
          ui->act_color->setChecked(true);
        } else if (contentPage_ == ui->act_settings_model->data()) {
          ui->act_settings_model->setChecked(true);
        } else if (contentPage_ == ui->act_light_settings->data()) {
          ui->act_light_settings->setChecked(true);
        } else if (contentPage_ == ui->act_settings_screen->data()) {
          ui->act_settings_screen->setChecked(true);
        } else if (contentPage_ == ui->act_backup->data()) {
          ui->act_backup->setChecked(true);
        }
      }
    } else {
      contentPage_ = action->data().toInt();
      ui->content->setCurrentIndex(contentPage_);
      ui->content->show();
    }
  }
}

void MainWindow::triggeredGroupActionUpper(QAction *action) {
  if (action == ui->act_projection) {
    action_projection();
  } else if (action == ui->act_folder) {
    action_open_folder();
  } else if (action == ui->act_light_on_off) {
    action_light_on_off();
  } else if (action == ui->act_texture) {
    action_texture_triggered();
  } else if (action == ui->act_info) {
    action_info_triggered();
  } else if (action == ui->act_delete_models) {
    action_delete_models();
  } else if (action == ui->act_screenShot) {
    action_screenshot();
  } else if (action == ui->act_make_gif) {
    action_make_gif();
  } else if (action == ui->act_gif_360) {
    action_make_gif_360();
  } else if (action == ui->act_shade) {
    action_shade();
  } else if (action == ui->act_axis_rotate) {
    action_axis_rotate();
  }
}

void MainWindow::action_projection() {
  if (controller.get_projection_sets() == projType::Central) {
    controller.set_projection_sets(projType::Parallel);
    ui->act_projection->setIcon(QIcon(":/icons_ui/parallProj.png"));
  } else if (controller.get_projection_sets() == projType::Parallel) {
    controller.set_projection_sets(s21_3DViewer::projType::Central);
    ui->act_projection->setIcon(QIcon(":/icons_ui/perpectiveProj.png"));
  }
  ui->openGLWidget->resizeGL(ui->openGLWidget->geometry().width(),
                             ui->openGLWidget->geometry().height());
  ui->openGLWidget->update();
}

void MainWindow::action_open_folder() {
  QString filePath = QFileDialog::getOpenFileName(
      this, "Select a file to open...", QDir::homePath(), "*.obj");
  if (!filePath.isEmpty()) {
    bool loading_flag = controller.add_object(filePath);
    if (loading_flag == false) {
      QMessageBox::warning(this, "Information",
                           "Incorrect obj. File. Please retry load another!");
    } else {
      buttonResetModelClicked();  // если были какие-то натсройки модели,
                                  // скидываем до дэфолтных
      buttonClearConditionClicked();  // если были сохранены каке-то состояния
                                      // скидываем до 0
      ui->act_modelCamera->setIcon(
          QIcon(":/icons_ui/model_camera.png"));  // изменение иконки для модели
                                                  // камеры
      ui->openGLWidget->update();  // отрисовка выбранного объекта
    }
  }
}

void MainWindow::action_light_on_off() {
  if (ui->act_light_on_off->iconText() == "ON_light") {
    ui->act_light_on_off->setIcon(QIcon(":/icons_ui/light_off.png"));
    ui->act_light_on_off->setIconText("OFF_light");
    controller.setLightStatus(lightStatus::OFF);
  } else {
    ui->act_light_on_off->setIcon(QIcon(":/icons_ui/light_on.png"));
    ui->act_light_on_off->setIconText("ON_light");
    controller.setLightStatus(lightStatus::ON);
  }
  ui->openGLWidget->update();  // перерисовка объекта
}

void MainWindow::action_texture_triggered() {
  if (controller.have_objects() == true) {
    if (ui->act_texture->iconText() == "NO_texture") {
      QString filePath = QFileDialog::getOpenFileName(
          this, "Select a file to open...", QDir::homePath(), "*.png");
      if (!filePath.isEmpty()) {
        controller.set_texture_path_sets(filePath);
        controller.add_texture_to_object();
        ui->act_texture->setIcon(QIcon(":/icons_ui/material.png"));
        ui->act_texture->setIconText("HAVE_texture");
      }
    } else {
      controller.delete_texture_from_object();
      ui->act_texture->setIcon(QIcon(":/icons_ui/material_no.png"));
      ui->act_texture->setIconText("NO_texture");
    }
    ui->openGLWidget->update();  // перерисовка объекта
  }
}

void MainWindow::action_info_triggered() {
  QString info;
  if (controller.have_objects() == true) {
    Object3D::InfoObject3D info_object = controller.get_info_object();
    QString nameObjFile = info_object.getPathToObj().split("/").back();
    QString nameTextureObj =
        info_object.getPathToTextureObj().split("/").back();
    QString YesNo = nameTextureObj.isEmpty() ? "No" : "Yes";
    info = QString("Name model = %1").arg(nameObjFile);
    info += QString("\n\nSum vertext model = %1").arg(info_object.getSumVert());
    info += QString("\n\nSum faces model = %1").arg(info_object.getSumFaces());
    info += QString("\n\nFile path model = %1").arg(info_object.getPathToObj());
    info += QString("\n\nTexture = %1").arg(YesNo);
    info += YesNo == "No"
                ? QString("")
                : QString("\n\nName texture file = %1").arg(nameTextureObj);
    info += YesNo == "No" ? QString("")
                          : QString("\n\nTexture path model = %1")
                                .arg(info_object.getPathToTextureObj());
  } else {
    info = "Load Object for get info about them";
  }
  QMessageBox::information(this, "Information", info);
}

void MainWindow::action_delete_models() {
  if (ui->act_modelCamera->isChecked()) {
    ui->act_modelCamera->setChecked(false);
    ui->content->hide();
  }
  buttonClearConditionClicked();  // очистить состояния, если были
  controller.delete_all_objects();  // удаляем все объекты с канваса
  ui->act_modelCamera->setIcon(QIcon(
      ":/icons_ui/unActiveModel.png"));  // изменение иконки для модели камеры
  ui->openGLWidget->update();  // перерисовка объекта
}

void MainWindow::clickedVertForm(int idButton) {
  controller.set_vert_type_sets(idButton);
  ui->openGLWidget->update();  // перерисовка объекта
}

void MainWindow::clickedLineForm(int idButton) {
  controller.set_line_type_sets(idButton);
  ui->openGLWidget->update();  // перерисовка объекта
}

void MainWindow::comboBoxIndexChanged(int drawType) {
  if (drawType == typeDraw::Points) {
    ui->checkBox_vert_form_none->hide();
    hideSetLines();
    if (controller.get_vert_type_sets() == vertType::None) {
      ui->checkBox_vert_form_circle->setChecked(true);
      controller.set_vert_type_sets(vertType::Circle);
    }
  } else if (drawType >= typeDraw::Lines && drawType <= typeDraw::Line_Strip) {
    ui->checkBox_vert_form_none->show();
    showSetLines();
  } else if (drawType == typeDraw::Triangles) {
    ui->checkBox_vert_form_none->show();
    hideSetLines();
  }
  controller.set_draw_type_sets(drawType);
  ui->openGLWidget->update();
}

void MainWindow::colorsButtonClicked() {
  QColorDialog colorWindow;
  colorWindow.open();
  QColor color = colorWindow.getColor();
  if (color != QColor::Invalid) {
    QWidget *currentBut = (QWidget *)sender();
    QString css = QString("background-color: %1;").arg(color.name());
    if (currentBut ==
        ui->backgroundColorButton) {  //  изменения цвета заднего фона
      controller.set_bg_color_sets(color.redF(), color.greenF(), color.blueF(),
                                   color.alphaF());
      ui->color_bg->setStyleSheet(css);
    } else if (currentBut == ui->surfaceColorButton) {  // изменение цвета
                                                        // поверхностей объекта
      controller.set_surfaces_color_sets(color.redF(), color.greenF(),
                                         color.blueF(), color.alphaF());
      ui->color_surface->setStyleSheet(css);
    } else if (currentBut ==
               ui->vertexColorButton) {  // изменение цвета вершин объекта
      controller.set_vert_color_sets(color.redF(), color.greenF(),
                                     color.blueF(), color.alphaF());
      ui->color_vertex->setStyleSheet(css);
    } else if (currentBut ==
               ui->linesColorButton) {  // изменение цвета линий объекта
      controller.set_line_color_sets(color.redF(), color.greenF(),
                                     color.blueF(), color.alphaF());
      ui->color_line->setStyleSheet(css);
    } else if (currentBut ==
               ui->pushButton_specular_color) {  // изменение цвета пятна блика
                                                 // освещения
      controller.setSpecularColor(color.redF(), color.greenF(), color.blueF(),
                                  color.alphaF());
      ui->color_specular_color->setStyleSheet(css);
    }
    ui->openGLWidget->update();  // перерисовка объекта
  }
}

void MainWindow::slidersModelSettingsChanged(int value) {
  QSlider *slider = (QSlider *)sender();
  if (slider == ui->slider_vertex_size) {
    ui->doubleSpinBox_vert_size->setValue(value);
  } else if (slider == ui->slider_line_size) {
    ui->doubleSpinBox_line_size->setValue(value);
  }
}

void MainWindow::doubleSpinBoxModelSettingsChanged(double value) {
  QDoubleSpinBox *current = (QDoubleSpinBox *)sender();
  if (current == ui->doubleSpinBox_vert_size) {
    ui->slider_vertex_size->setValue(value);
    controller.set_vert_size_sets(value);
  } else if (current == ui->doubleSpinBox_line_size) {
    ui->slider_line_size->setValue(value);
    controller.set_line_size_sets(value);
  }
  ui->openGLWidget->update();  // перерисовка объекта
}

void MainWindow::slidersModelChanged(int value) {
  QSlider *current = (QSlider *)sender();
  if (current == ui->slider_M_RX) {
    ui->doubleSpinBox_M_RX->setValue(value);
  } else if (current == ui->slider_M_RY) {
    ui->doubleSpinBox_M_RY->setValue(value);
  } else if (current == ui->slider_M_RZ) {
    ui->doubleSpinBox_M_RZ->setValue(value);
  } else if (current == ui->slider_M_TX) {
    ui->doubleSpinBox_M_TX->setValue(value);
  } else if (current == ui->slider_M_TY) {
    ui->doubleSpinBox_M_TY->setValue(value);
  } else if (current == ui->slider_M_TZ) {
    ui->doubleSpinBox_M_TZ->setValue(value);
  } else if (current == ui->slider_M_Scale) {
    ui->doubleSpinBox_M_Scale->setValue(value);
  }
}

void MainWindow::doubleSpinboxModelChanged(double value) {
  QDoubleSpinBox *current = (QDoubleSpinBox *)sender();
  if (current == ui->doubleSpinBox_M_RX) {
    ui->slider_M_RX->setValue(value);
    x_rot = value;
    controller.x_rotate_object(value);
  } else if (current == ui->doubleSpinBox_M_RY) {
    ui->slider_M_RY->setValue(value);
    y_rot = value;
    controller.y_rotate_object(value);
  } else if (current == ui->doubleSpinBox_M_RZ) {
    ui->slider_M_RZ->setValue(value);
    controller.z_rotate_object(value);
  } else if (current == ui->doubleSpinBox_M_TX) {
    ui->slider_M_TX->setValue(value);
    controller.x_translate_object(value);
  } else if (current == ui->doubleSpinBox_M_TY) {
    ui->slider_M_TY->setValue(value);
    controller.y_translate_object(value);
  } else if (current == ui->doubleSpinBox_M_TZ) {
    ui->slider_M_TZ->setValue(value);
    controller.z_translate_object(value);
  } else if (current == ui->doubleSpinBox_M_Scale) {
    ui->slider_M_Scale->setValue(value);
    controller.scale_object(value / 3.0);
  }
  ui->openGLWidget->update();  // перерисовка модели
}

void MainWindow::slidersLightSettingsChanged(int value) {
  QSlider *current = (QSlider *)sender();
  if (current == ui->slider_light_power) {
    controller.setLightPower((float)value / 5);
  } else if (current == ui->slider_light_color_red) {
    controller.setLightColorRed((float)value / 255);
  } else if (current == ui->slider_light_color_green) {
    controller.setLightColorGreen((float)value / 255);
  } else if (current == ui->slider_light_color_blue) {
    controller.setLightColorBlue((float)value / 255);
  } else if (current == ui->slider_specular_factor) {
    controller.setSpecularFactor((float)value);
  }
  ui->openGLWidget->update();  // перерисовка объекта
}

void MainWindow::doubleSpinBoxLightChanged(double value) {
  QDoubleSpinBox *current = (QDoubleSpinBox *)sender();
  if (current == ui->doubleSpinBox_x) {
    controller.setLightPosition(value, ui->doubleSpinBox_y->value(),
                                ui->doubleSpinBox_z->value());
  } else if (current == ui->doubleSpinBox_y) {
    controller.setLightPosition(ui->doubleSpinBox_x->value(), value,
                                ui->doubleSpinBox_z->value());
  } else if (current == ui->doubleSpinBox_z) {
    controller.setLightPosition(ui->doubleSpinBox_x->value(),
                                ui->doubleSpinBox_y->value(), value);
  } else if (current == ui->doubleSpinBox_ambient_factor) {
    controller.setAmbientFactor(value);
  }
  ui->openGLWidget->update();  // перерисовка объекта
}

void MainWindow::slidersSettingsScreenChanged(int value) {
  QSlider *current = (QSlider *)sender();
  if (current == ui->slider_width_screen) {
    ui->doubleSpinBox_width_screen->setValue(value);
  } else if (current == ui->slider_height_screen) {
    ui->doubleSpinBox_height_screen->setValue(value);
  }
}

void MainWindow::doubleSpinBoxSettingsScreenChanged(double value) {
  QDoubleSpinBox *current = (QDoubleSpinBox *)sender();
  if (current == ui->doubleSpinBox_width_screen) {
    ui->slider_width_screen->setValue(value);
  } else if (current == ui->doubleSpinBox_height_screen) {
    ui->slider_height_screen->setValue(value);
  }
}

void MainWindow::buttonResizeWindowClicked() {
  float newWidth = ui->doubleSpinBox_width_screen->value();
  float newHeight = ui->doubleSpinBox_height_screen->value();

  float maxWidthScreen = QGuiApplication::primaryScreen()->geometry().width();
  float maxHeight = QGuiApplication::primaryScreen()->geometry().height();
  if (newWidth > maxWidthScreen || newHeight > maxHeight) {
    QMessageBox messageBox;
    messageBox.information(this, "Information",
                           QString("Sorry, you can install:\nmax"
                                   "width = %1\nmax height = %2")
                               .arg(maxWidthScreen)
                               .arg(maxHeight));
  } else {
    controller.set_windowWidth_sets(newWidth);
    controller.set_windowHeight_sets(newHeight);
    resize(newWidth, newHeight);
  }
}

void MainWindow::set_doubleSpinBox_width_height() {
  int width = geometry().width();
  int height = geometry().height();
  ui->doubleSpinBox_width_screen->setValue(width);
  controller.set_windowWidth_sets(width);
  ui->doubleSpinBox_height_screen->setValue(height);
  controller.set_windowHeight_sets(height);
}

void MainWindow::buttonPrevConditionClicked() {
  int num_condition = ui->label_cloud_condition->text().toInt();
  if (num_condition != 0) {
    controller.backupNext();
    controller.getStateMementoPrev();
    ui->openGLWidget->update();
    installSettings(false);
    ui->label_cloud_condition->setNum(num_condition - 1);
  }
}

void MainWindow::buttonNextConditionClicked() {
  controller.backupPrev();
  controller.getStateMementoNext();
  ui->openGLWidget->update();
  installSettings(false);
}

void MainWindow::buttonSaveConditionClicked() {
  int num_condition = ui->label_cloud_condition->text().toInt();
  if (controller.have_objects()) {
    if (num_condition < 100) {
      controller.backupPrev();
      ui->label_cloud_condition->setNum(num_condition + 1);
    } else {
      QMessageBox::information(this, "Information",
                               "Sorry, you can save only 100 Conditions!");
    }
  }
}

void MainWindow::buttonClearConditionClicked() {
  controller.clearConditions();
  ui->label_cloud_condition->setNum(0);
}

void MainWindow::doubleSpinBoxMinMaxChanged(double value) {
  QDoubleSpinBox *current = (QDoubleSpinBox *)sender();
  if (current == ui->doubleSpinBox_min_translate) {
    ui->doubleSpinBox_M_TX->setMinimum(value);
    ui->doubleSpinBox_M_TY->setMinimum(value);
    ui->doubleSpinBox_M_TZ->setMinimum(value);
    ui->slider_M_TX->setMinimum(value);
    ui->slider_M_TY->setMinimum(value);
    ui->slider_M_TZ->setMinimum(value);
  } else if (current == ui->doubleSpinBox_max_translate) {
    ui->doubleSpinBox_M_TX->setMaximum(value);
    ui->doubleSpinBox_M_TY->setMaximum(value);
    ui->doubleSpinBox_M_TZ->setMaximum(value);
    ui->slider_M_TX->setMaximum(value);
    ui->slider_M_TY->setMaximum(value);
    ui->slider_M_TZ->setMaximum(value);
  } else if (current == ui->doubleSpinBox_min_scale) {
    ui->doubleSpinBox_M_Scale->setMinimum(value);
    ui->slider_M_Scale->setMinimum(value);
  } else if (current == ui->doubleSpinBox_max_scale) {
    ui->doubleSpinBox_M_Scale->setMaximum(value);
    ui->slider_M_Scale->setMaximum(value);
  }
}

void MainWindow::buttonSettingsMinMaxClicked() {
  ui->content->setCurrentIndex(pages::EIGHTH_PAGE);
}

void MainWindow::buttonBackToModelClicked() {
  ui->content->setCurrentIndex(pages::FIRST_PAGE);
}

void MainWindow::buttonResetModelClicked() {
  controller.x_rotate_object(0);
  ui->doubleSpinBox_M_RX->setValue(0);
  ui->slider_M_RX->setValue(0);

  controller.y_rotate_object(0);
  ui->doubleSpinBox_M_RY->setValue(0);
  ui->slider_M_RY->setValue(0);

  controller.z_rotate_object(0);
  ui->doubleSpinBox_M_RZ->setValue(0);
  ui->slider_M_RZ->setValue(0);

  controller.x_translate_object(0);
  ui->doubleSpinBox_M_TX->setValue(0);
  ui->slider_M_TX->setValue(0);

  controller.y_translate_object(0);
  ui->doubleSpinBox_M_TY->setValue(0);
  ui->slider_M_TY->setValue(0);

  controller.z_translate_object(0);
  ui->doubleSpinBox_M_TZ->setValue(0);
  ui->slider_M_TZ->setValue(0);

  controller.scale_object(1.0);
  ui->doubleSpinBox_M_Scale->setValue(1.0);
  ui->slider_M_Scale->setValue(1.0);

  ui->openGLWidget->update();  // перерисовка модели
}

// gifmaker

void MainWindow::MakeTmpShot() {
  QImage shot(ui->openGLWidget->grabFramebuffer());
  if (shot.height() != kGifHeight || shot.width() != kGifWidth) {
    shot = shot.scaled(kGifWidth, kGifHeight, Qt::IgnoreAspectRatio,
                       Qt::SmoothTransformation);
  }
  gif_image_->addFrame(shot);
  gif_prog_bar_->setValue(gif_prog_bar_->value() + 1);
}

void MainWindow::action_screenshot() {
  QString screnshootsDirPath =
      QCoreApplication::applicationDirPath() + "/screenshots/";
  if (!QDir(screnshootsDirPath).exists()) {
    QDir().mkdir(screnshootsDirPath);
  }
  QString filename = screnshootsDirPath +
                     QDateTime::currentDateTime().toString("ddMMyy-hh-mm-ss");
  if (ui->openGLWidget->grabFramebuffer().save(filename + ".jpeg") &&
      ui->openGLWidget->grabFramebuffer().save(filename + ".bmp"))
    ui->statusBar->showMessage(
        "screenshots saved as: " + filename + "(.jpeg/.bmp)", 5000);
}

void MainWindow::action_make_gif() {
  gif_maker_->Abort();
  gif_thread_->wait();
  if (gif_image_) delete gif_image_;
  gif_image_ = new QGifImage(QSize(640, 480));
  gif_image_->setDefaultDelay(100);
  gif_prog_bar_->setValue(0);
  gif_prog_bar_->setVisible(true);
  gif_maker_->RequestWork();
}

void MainWindow::action_make_gif_360() {
  QString pathToGif = QCoreApplication::applicationDirPath() + "/gifs/";
  if (!QDir(pathToGif).exists()) {
    QDir().mkdir(pathToGif);
  }
  if (gif_image_) delete gif_image_;
  gif_image_ = new QGifImage(QSize(kGifWidth, kGifHeight));
  gif_image_->setDefaultDelay(100);
  for (int i{}; i < 50; i++) {
    for (int j{}; j < controller.get_sum_objects(); j++)
      controller.y_rotate_object((360.0 / 50.0) * i, j);
    ui->openGLWidget->update();
    QImage shot(ui->openGLWidget->grabFramebuffer());
    shot = shot.scaled(kGifWidth, kGifHeight, Qt::IgnoreAspectRatio,
                       Qt::SmoothTransformation);
    gif_image_->addFrame(shot);

    QEventLoop loop;
    QTimer::singleShot(20, &loop, SLOT(quit()));
    loop.exec();
  }
  SaveGifImage();
}

void MainWindow::action_shade() {
  if (controller.getLightShade() == shaddingType::Flat) {
    controller.setLightShade(shaddingType::Soft);
    ui->act_shade->setIcon(QIcon(":/icons_ui/Soft_shade.png"));
  } else if (controller.getLightShade() == shaddingType::Soft) {
    controller.setLightShade(shaddingType::Flat);
    ui->act_shade->setIcon(QIcon(":/icons_ui/Flat_shade.png"));
  }
  ui->openGLWidget->update();  // перерисовка модели
}

void MainWindow::action_axis_rotate() {
  if (controller.have_objects()) {
    if (contentPage_ == pages::SEVENTH_PAGE) {
      ui->content->hide();
      contentPage_ = pages::HIDE;
    } else {
      contentPage_ = pages::SEVENTH_PAGE;
      ui->content->setCurrentIndex(contentPage_);
      if (ui->content->isHidden()) {
        ui->content->show();
      }
    }
  }
}

void MainWindow::SaveGifImage() {
  QString filename = QCoreApplication::applicationDirPath() + "/gifs/" +
                     QDateTime::currentDateTime().toString("ddMMyy-hh-mm-ss") +
                     ".gif";
  if (gif_image_->save(filename))
    ui->statusBar->showMessage("screencast saved as: " + filename, 5000);
  gif_prog_bar_->setVisible(false);
}

void MainWindow::MakeIdleRotateStep() {
  if (axis_auto_rotate == axisRotate::X_AXIS) {
    if (turnAutoRotate_ == turnAutoRotate::LEFT) {
      x_rot -= ((float)ui->slider_rotate_axis_degress->value() / 10.0);
      if (x_rot <= 0.0) {
        x_rot = 360.0 + x_rot;
      }
    } else if (turnAutoRotate_ == turnAutoRotate::RIGHT) {
      x_rot += ((float)ui->slider_rotate_axis_degress->value() / 10.0);
      if (x_rot >= 360.0) {
        x_rot = x_rot - 360.0;
      }
    }
    ui->doubleSpinBox_M_RX->setValue(x_rot);
  } else if (axis_auto_rotate == axisRotate::Y_AXIS) {
    if (turnAutoRotate_ == turnAutoRotate::LEFT) {
      y_rot -= ((float)ui->slider_rotate_axis_degress->value() / 10.0);
      if (y_rot <= 0.0) {
        y_rot = 360.0 + y_rot;
      }
    } else if (turnAutoRotate_ == turnAutoRotate::RIGHT) {
      y_rot += ((float)ui->slider_rotate_axis_degress->value() / 10.0);
      if (y_rot >= 360.0) {
        y_rot = y_rot - 360.0;
      }
    }
    ui->doubleSpinBox_M_RY->setValue(y_rot);
  } else if (axis_auto_rotate == axisRotate::X_Y_AXIS) {
    if (turnAutoRotate_ == turnAutoRotate::LEFT) {
      x_rot -= ((float)ui->slider_rotate_axis_degress->value() / 10.0);
      if (x_rot <= 0.0) {
        x_rot = 360.0 + x_rot;
      }
      y_rot -= ((float)ui->slider_rotate_axis_degress->value() / 10.0);
      if (y_rot <= 0.0) {
        y_rot = 360.0 + y_rot;
      }
    } else if (turnAutoRotate_ == turnAutoRotate::RIGHT) {
      x_rot += ((float)ui->slider_rotate_axis_degress->value() / 10.0);
      if (x_rot >= 360.0) {
        x_rot = x_rot - 360.0;
      }
      y_rot += ((float)ui->slider_rotate_axis_degress->value() / 10.0);
      if (y_rot >= 360.0) {
        y_rot = y_rot - 360.0;
      }
    }
    ui->doubleSpinBox_M_RX->setValue(x_rot);
    ui->doubleSpinBox_M_RY->setValue(y_rot);
  }
}

void MainWindow::buttonsRotateAxisClicked() {
  QToolButton *current = (QToolButton *)sender();
  if (current == ui->toolButton_x_axis_rotate) {
    if (axis_auto_rotate != axisRotate::X_AXIS) {
      ui->toolButton_y_axis_rotate->setIcon(QIcon(":/icons_ui/y_axis_OFF.png"));
      ui->toolButton_x_y_axis_rotate->setIcon(
          QIcon(":/icons_ui/x_y_axis_OFF.png"));
      ui->toolButton_x_axis_rotate->setIcon(QIcon(":/icons_ui/x_axis_ON.png"));
      axis_auto_rotate = axisRotate::X_AXIS;
    }
  } else if (current == ui->toolButton_y_axis_rotate) {
    if (axis_auto_rotate != axisRotate::Y_AXIS) {
      ui->toolButton_x_axis_rotate->setIcon(QIcon(":/icons_ui/x_axis_OFF.png"));
      ui->toolButton_x_y_axis_rotate->setIcon(
          QIcon(":/icons_ui/x_y_axis_OFF.png"));
      ui->toolButton_y_axis_rotate->setIcon(QIcon(":/icons_ui/y_axis_ON.png"));
      axis_auto_rotate = axisRotate::Y_AXIS;
    }
  } else if (current == ui->toolButton_x_y_axis_rotate) {
    if (axis_auto_rotate != axisRotate::X_Y_AXIS) {
      ui->toolButton_x_axis_rotate->setIcon(QIcon(":/icons_ui/x_axis_OFF.png"));
      ui->toolButton_y_axis_rotate->setIcon(QIcon(":/icons_ui/y_axis_OFF.png"));
      ui->toolButton_x_y_axis_rotate->setIcon(
          QIcon(":/icons_ui/x_y_axis_ON.png"));
      axis_auto_rotate = axisRotate::X_Y_AXIS;
    }
  }
}

void MainWindow::buttonsPlayStopRotateAxisClicked() {
  gif_maker_->Abort();
  gif_thread_->wait();
  if (ui->toolButton_play_stop_rotate->text() == "play") {
    ui->toolButton_play_stop_rotate->setText("stop");
    ui->toolButton_play_stop_rotate->setIcon(
        QIcon(":/icons_ui/pause-button.png"));

    gif_maker_->RequestIdleRotate();
  } else if (ui->toolButton_play_stop_rotate->text() == "stop") {
    ui->toolButton_play_stop_rotate->setText("play");
    ui->toolButton_play_stop_rotate->setIcon(
        QIcon(":/icons_ui/play-button.png"));
  }
}

void MainWindow::buttonsTurnRotateAxisClicked() {
  QToolButton *current = (QToolButton *)sender();
  if (current == ui->toolButton_right_auto_rotate) {
    if (turnAutoRotate_ != turnAutoRotate::RIGHT) {
      ui->toolButton_right_auto_rotate->setIcon(
          QIcon(":/icons_ui/auto_rotate_right_YES.png"));
      ui->toolButton_left_auto_rotate->setIcon(
          QIcon(":/icons_ui/auto_rotate_left_NO.png"));
      turnAutoRotate_ = turnAutoRotate::RIGHT;
    }
  } else if (current == ui->toolButton_left_auto_rotate) {
    if (turnAutoRotate_ != turnAutoRotate::LEFT) {
      ui->toolButton_left_auto_rotate->setIcon(
          QIcon(":/icons_ui/auto_rotate_left_YES.png"));
      ui->toolButton_right_auto_rotate->setIcon(
          QIcon(":/icons_ui/auto_rotate_right_NO.png"));
      turnAutoRotate_ = turnAutoRotate::LEFT;
    }
  }
}

}  // namespace s21_3DViewer
