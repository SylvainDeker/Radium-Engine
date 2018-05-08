#include <Gui/LightCreator.hpp>
#include <Gui/MainWindow.hpp>
#include <Engine/Renderer/Light/PointLight.hpp>
#include <Engine/ItemModel/ItemEntry.hpp>

#include <QPushButton>
#include <QColorDialog>
#include <QPalette>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QMessageBox>
#include <QCheckBox>

#include <math.h>
#define NB_DECIMAL 10
#define MAX_INTENSITY 100
#define MAX_ANGLE 360
#define MIN_CONSTANT -1000
#define MAX_CONSTANT 1000
#define MIN_LINEAR -100
#define MAX_LINEAR 100
#define MIN_QUADRA -100
#define MAX_QUADRA 100
#define MAX_COORD 10000000


namespace Ra {
namespace Gui {

LightCreator::LightCreator( QWidget* parent ) : QWidget( nullptr )    {
    setupUi( this );
    m_color = new QColor(255,255,255);
    m_name = new QString("");
    m_intensity_val = new double(0);
    m_angle_val = new double(0);
    m_falloff_val_constant = new double(0);
    m_falloff_val_linear = new double(0);
    m_falloff_val_quadratic = new double(0);
    m_lightType = new int(0);



    m_intensity_spinbox-> setDecimals (NB_DECIMAL);
    m_intensity_spinbox->setMaximum(MAX_INTENSITY);
    m_intensity_slider->setMaximum(MAX_INTENSITY);

    m_angle_spinbox-> setDecimals (NB_DECIMAL);
    m_angle_spinbox->setMaximum(MAX_ANGLE);
    m_angle_slider->setMaximum(MAX_ANGLE);

    m_falloff_spinbox_constant->setDecimals (NB_DECIMAL);
    m_falloff_spinbox_constant->setMaximum(MAX_CONSTANT);
    m_falloff_spinbox_constant->setMinimum(MIN_CONSTANT);
    m_falloff_slider_constant->setMaximum(MAX_CONSTANT);
    m_falloff_slider_constant->setMinimum(MIN_CONSTANT);



    m_falloff_spinbox_linear->setDecimals (NB_DECIMAL);
    m_falloff_spinbox_linear->setMaximum(MAX_LINEAR);
    m_falloff_spinbox_linear->setMinimum(MIN_LINEAR);
    m_falloff_slider_linear->setMaximum(MAX_LINEAR);
    m_falloff_slider_linear->setMinimum(MIN_LINEAR);


    m_falloff_spinbox_quadratic->setDecimals (NB_DECIMAL);
    m_falloff_spinbox_quadratic->setMaximum(MAX_QUADRA);
    m_falloff_spinbox_quadratic->setMinimum(MIN_QUADRA);
    m_falloff_slider_quadratic->setMaximum(MAX_QUADRA);
    m_falloff_slider_quadratic->setMinimum(MIN_QUADRA);





    m_pos_x_spin->setDecimals (NB_DECIMAL);
    m_pos_x_spin->setMaximum(MAX_COORD);
    m_pos_x_spin->setMinimum(-MAX_COORD);

    m_pos_y_spin->setDecimals (NB_DECIMAL);
    m_pos_y_spin->setMaximum(MAX_COORD);
    m_pos_y_spin->setMinimum(-MAX_COORD);

    m_pos_z_spin->setDecimals (NB_DECIMAL);
    m_pos_z_spin->setMaximum(MAX_COORD);
    m_pos_z_spin->setMinimum(-MAX_COORD);

    m_dir_x_spin->setDecimals (NB_DECIMAL);
    m_dir_x_spin->setMaximum(MAX_COORD);
    m_dir_x_spin->setMinimum(-MAX_COORD);


    m_dir_y_spin->setDecimals (NB_DECIMAL);
    m_dir_y_spin->setMaximum(MAX_COORD);
    m_dir_y_spin->setMinimum(-MAX_COORD);


    m_dir_z_spin->setDecimals (NB_DECIMAL);
    m_dir_z_spin->setMaximum(MAX_COORD);
    m_dir_z_spin->setMinimum(-MAX_COORD);


    // Init with Directionnal selected by default
    m_angle_lab->setVisible(false);
    m_angle_spinbox->setVisible(false);
    m_angle_slider->setVisible(false);









    setWindowTitle("Light Creator");
    QPalette p;
    p.setColor(QPalette::Background,*m_color);
    m_result_color->setAutoFillBackground(true);
    m_result_color->setPalette(p);
    connect(m_button_color, &QPushButton::clicked,this,&LightCreator::open_dialogColor);

    // Selecter
    connect(m_kind_of_light,static_cast<void (QComboBox::*) (int)>(&QComboBox::currentIndexChanged),this,&LightCreator::slot_select_light);
    // Selecter Angle

    connect(this,&LightCreator::sig_show_angle,m_angle_slider,&QSlider::show);
    connect(this,&LightCreator::sig_show_angle,m_angle_lab,&QLabel::show);
    connect(this,&LightCreator::sig_show_angle,m_angle_spinbox,&QDoubleSpinBox::show);

    connect(this,&LightCreator::sig_hide_angle,m_angle_slider,&QSlider::hide);
    connect(this,&LightCreator::sig_hide_angle,m_angle_lab,&QLabel::hide);
    connect(this,&LightCreator::sig_hide_angle,m_angle_spinbox,&QDoubleSpinBox::hide);

    // Selecter dir
    connect(this,&LightCreator::sig_hide_dir,m_dir_x_spin,&QDoubleSpinBox::hide);
    connect(this,&LightCreator::sig_hide_dir,m_dir_y_spin,&QDoubleSpinBox::hide);
    connect(this,&LightCreator::sig_hide_dir,m_dir_z_spin,&QDoubleSpinBox::hide);
    connect(this,&LightCreator::sig_hide_dir,m_dir_x_lab,&QLabel::hide);
    connect(this,&LightCreator::sig_hide_dir,m_dir_y_lab,&QLabel::hide);
    connect(this,&LightCreator::sig_hide_dir,m_dir_z_lab,&QLabel::hide);

    connect(this,&LightCreator::sig_show_dir,m_dir_x_spin,&QDoubleSpinBox::show);
    connect(this,&LightCreator::sig_show_dir,m_dir_y_spin,&QDoubleSpinBox::show);
    connect(this,&LightCreator::sig_show_dir,m_dir_z_spin,&QDoubleSpinBox::show);
    connect(this,&LightCreator::sig_show_dir,m_dir_x_lab,&QLabel::show);
    connect(this,&LightCreator::sig_show_dir,m_dir_y_lab,&QLabel::show);
    connect(this,&LightCreator::sig_show_dir,m_dir_z_lab,&QLabel::show);

    connect(this,&LightCreator::sig_hide_dir,m_direction_lab,&QLabel::hide);
    connect(this,&LightCreator::sig_show_dir,m_direction_lab,&QLabel::show);

    //Selecter Position

    connect(this,&LightCreator::sig_hide_pos,m_pos_x_spin,&QDoubleSpinBox::hide);
    connect(this,&LightCreator::sig_hide_pos,m_pos_y_spin,&QDoubleSpinBox::hide);
    connect(this,&LightCreator::sig_hide_pos,m_pos_z_spin,&QDoubleSpinBox::hide);
    connect(this,&LightCreator::sig_hide_pos,m_pos_x_lab,&QLabel::hide);
    connect(this,&LightCreator::sig_hide_pos,m_pos_y_lab,&QLabel::hide);
    connect(this,&LightCreator::sig_hide_pos,m_pos_z_lab,&QLabel::hide);

    connect(this,&LightCreator::sig_show_pos,m_pos_x_spin,&QDoubleSpinBox::show);
    connect(this,&LightCreator::sig_show_pos,m_pos_y_spin,&QDoubleSpinBox::show);
    connect(this,&LightCreator::sig_show_pos,m_pos_z_spin,&QDoubleSpinBox::show);
    connect(this,&LightCreator::sig_show_pos,m_pos_x_lab,&QLabel::show);
    connect(this,&LightCreator::sig_show_pos,m_pos_y_lab,&QLabel::show);
    connect(this,&LightCreator::sig_show_pos,m_pos_z_lab,&QLabel::show);

    connect(this,&LightCreator::sig_hide_pos,m_coord_lab,&QLabel::hide);
    connect(this,&LightCreator::sig_show_pos,m_coord_lab,&QLabel::show);



    // Intensity
    connect(m_intensity_slider, &QSlider::valueChanged, this , &LightCreator::slot_intensity_slide_to_spin );
    connect(this,&LightCreator::sig_intensity_slide_to_spin,m_intensity_spinbox,&QDoubleSpinBox::setValue);

    connect(m_intensity_spinbox, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightCreator::slot_intensity_spin_to_slide );
    connect(this,&LightCreator::sig_intensity_spin_to_slide,m_intensity_slider,&QSlider::setValue);

    // Angle
    connect(m_angle_slider, &QSlider::valueChanged, this , &LightCreator::slot_angle_slide_to_spin );
    connect(this,&LightCreator::sig_angle_slide_to_spin,m_angle_spinbox,&QDoubleSpinBox::setValue);

    connect(m_angle_spinbox, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightCreator::slot_angle_spin_to_slide );
    connect(this,&LightCreator::sig_angle_spin_to_slide,m_angle_slider,&QSlider::setValue);

    // Falloff

    connect(m_falloff_slider_constant, &QSlider::valueChanged, this , &LightCreator::slot_falloff_constant_slide_to_spin );
    connect(this,&LightCreator::sig_falloff_constant_slide_to_spin,m_falloff_spinbox_constant,&QDoubleSpinBox::setValue);

    connect(m_falloff_spinbox_constant, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightCreator::slot_falloff_constant_spin_to_slide );
    connect(this,&LightCreator::sig_falloff_constant_spin_to_slide,m_falloff_slider_constant,&QSlider::setValue);

    connect(m_falloff_slider_linear, &QSlider::valueChanged, this , &LightCreator::slot_falloff_linear_slide_to_spin );
    connect(this,&LightCreator::sig_falloff_linear_slide_to_spin,m_falloff_spinbox_linear,&QDoubleSpinBox::setValue);

    connect(m_falloff_spinbox_linear, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightCreator::slot_falloff_linear_spin_to_slide );
    connect(this,&LightCreator::sig_falloff_linear_spin_to_slide,m_falloff_slider_linear,&QSlider::setValue);

    connect(m_falloff_slider_quadratic, &QSlider::valueChanged, this , &LightCreator::slot_falloff_quadratic_slide_to_spin );
    connect(this,&LightCreator::sig_falloff_quadratic_slide_to_spin,m_falloff_spinbox_quadratic,&QDoubleSpinBox::setValue);

    connect(m_falloff_spinbox_quadratic, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightCreator::slot_falloff_quadratic_spin_to_slide );
    connect(this,&LightCreator::sig_falloff_quadratic_spin_to_slide,m_falloff_slider_quadratic,&QSlider::setValue);


    // OK Button
    connect(m_button_create,&QPushButton::clicked,this,&LightCreator::open_dialogueConfirm);
    connect(this,&LightCreator::sig_close_windows,this,&QWidget::close);

}

LightCreator::~LightCreator(){
  delete m_color;
  delete m_intensity_val;
  delete m_angle_val;
  delete m_falloff_val_constant;
  delete m_falloff_val_linear;
  delete m_falloff_val_quadratic;
  delete m_name;
  delete m_lightType;
}


void LightCreator::open_dialogColor(){
  *m_color = QColorDialog::getColor ();
  QPalette p;

  p.setColor(QPalette::Background,*m_color);
  m_result_color->setPalette(p);

}

void LightCreator::open_dialogueConfirm(){
  *m_name = m_lineEdit->text();
  if( m_name->isEmpty())
    QMessageBox::critical(this, "Watch out !","A new light must have a name !");
  else {
    // Ra::Engine::Entity *e=new Ra::Engine::Entity("Entity_Test");
    // Ra::Engine::PointLight *p = new Ra::Engine::PointLight(e,"PointLight_Test");
    // Ra::Engine::ItemEntry *m = new Ra::Engine::ItemEntry(e, p);
    // emit sig_onItemAdded(*m);
    emit sig_close_windows() ;
  }
}




/// Selecter Combobox
void LightCreator::slot_select_light(int val){
    *m_lightType = val;
    /*
    emit sig_show_angle();
    emit sig_show_dir();
    emit sig_show_pos();
    emit sig_show_falloff();
    */

    switch (val) {
      case 0: // Directionnal
      emit sig_show_dir();
      emit sig_show_pos();

        emit sig_hide_angle(); break;
      case 1: // Spot
          emit sig_show_angle();
          emit sig_show_dir();
          emit sig_show_pos();
                              break;
      case 2: // Point

      emit sig_show_pos();
      // emit sig_show_falloff();

        emit sig_hide_dir();
        emit sig_hide_angle(); break;

      case 3: //Area
      // emit sig_hide_falloff();

          emit sig_hide_dir();
          emit sig_hide_angle();
          emit sig_hide_pos(); break;

      default:
        assert(false);

    }
}

/// Intensity
void LightCreator::slot_intensity_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_intensity_val = tmp;
  emit sig_intensity_slide_to_spin(tmp);
}

void LightCreator::slot_intensity_spin_to_slide(double val){
  *m_intensity_val = val;
  int tmp = (int) val;
  emit sig_intensity_spin_to_slide(tmp);
}

/// Angle

void LightCreator::slot_angle_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_angle_val = tmp;
  emit sig_angle_slide_to_spin(tmp);
}

void LightCreator::slot_angle_spin_to_slide(double val){
  *m_angle_val = val;
  int tmp = (int) val;
  emit sig_angle_spin_to_slide(tmp);
}


/// Falloff
void LightCreator::slot_falloff_constant_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_falloff_val_constant = tmp;
  emit sig_falloff_constant_slide_to_spin(*m_falloff_val_constant);
}

void LightCreator::slot_falloff_constant_spin_to_slide(double val){
  *m_falloff_val_constant = val;
  int tmp = (int) val;
  emit sig_falloff_constant_spin_to_slide(tmp);
}

void LightCreator::slot_falloff_linear_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_falloff_val_linear = tmp;
  emit sig_falloff_linear_slide_to_spin(*m_falloff_val_linear);
}

void LightCreator::slot_falloff_linear_spin_to_slide(double val){
  *m_falloff_val_linear = val;
  int tmp = (int) val;
  emit sig_falloff_linear_spin_to_slide(tmp);
}
void LightCreator::slot_falloff_quadratic_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_falloff_val_quadratic = tmp;
  emit sig_falloff_quadratic_slide_to_spin(*m_falloff_val_quadratic);
}

void LightCreator::slot_falloff_quadratic_spin_to_slide(double val){
  *m_falloff_val_quadratic = val;
  int tmp = (int) val;
  emit sig_falloff_quadratic_spin_to_slide(tmp);
}




} // namespace Gui
} // namespace Ra
