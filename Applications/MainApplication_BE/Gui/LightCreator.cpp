#include <Gui/LightCreator.hpp>
#include <Gui/MainWindow.hpp>
#include <Engine/Renderer/Light/PointLight.hpp>
#include <Engine/ItemModel/ItemEntry.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Engine/Managers/EntityManager/EntityManager.hpp>
#include <Engine/Renderer/Light/DirLight.hpp>
#include <Engine/Renderer/Light/SpotLight.hpp>
#include <Engine/Renderer/Light/PointLight.hpp>
#include <Core/Asset/LightData.hpp>


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
    setWindowTitle("Light Creator");
    setWindowIcon(parent->windowIcon());
    m_color = new QColor(255,255,255);
    m_name = new QString("");
    m_intensity_val = new double(100);
    m_inner_angle_val = new double(0);
    m_outer_angle_val = new double(0);
    m_falloff_val_constant = new double(0);
    m_falloff_val_linear = new double(0);
    m_falloff_val_quadratic = new double(0);
    m_lightType = new int(0);
    m_position = new Core::Vector3(0,0,0);
    m_direction = new Core::Vector3(0,0,1);






    connect(m_button_color, &QPushButton::clicked,this,&LightCreator::open_dialogColor);

    // Selecter
    connect(m_kind_of_light,static_cast<void (QComboBox::*) (int)>(&QComboBox::currentIndexChanged),this,&LightCreator::slot_select_light);
    // Selecter Angle
connect(this,&LightCreator::sig_show_angle,m_angle_lab,&QLabel::show);
connect(this,&LightCreator::sig_hide_angle,m_angle_lab,&QLabel::hide);
    connect(this,&LightCreator::sig_show_angle,m_inner_angle_slider,&QSlider::show);
    connect(this,&LightCreator::sig_show_angle,m_inner_angle_lab,&QLabel::show);
    connect(this,&LightCreator::sig_show_angle,m_inner_angle_spinbox,&QDoubleSpinBox::show);
    connect(this,&LightCreator::sig_show_angle,m_inner_angle_lab,&QLabel::show);

    connect(this,&LightCreator::sig_hide_angle,m_inner_angle_slider,&QSlider::hide);
    connect(this,&LightCreator::sig_hide_angle,m_inner_angle_lab,&QLabel::hide);
    connect(this,&LightCreator::sig_hide_angle,m_inner_angle_spinbox,&QDoubleSpinBox::hide);
    connect(this,&LightCreator::sig_hide_angle,m_inner_angle_lab,&QLabel::hide);

    connect(this,&LightCreator::sig_show_angle,m_outer_angle_slider,&QSlider::show);
    connect(this,&LightCreator::sig_show_angle,m_outer_angle_lab,&QLabel::show);
    connect(this,&LightCreator::sig_show_angle,m_outer_angle_spinbox,&QDoubleSpinBox::show);
    connect(this,&LightCreator::sig_show_angle,m_outer_angle_lab,&QLabel::show);

    connect(this,&LightCreator::sig_hide_angle,m_outer_angle_slider,&QSlider::hide);
    connect(this,&LightCreator::sig_hide_angle,m_outer_angle_lab,&QLabel::hide);
    connect(this,&LightCreator::sig_hide_angle,m_outer_angle_spinbox,&QDoubleSpinBox::hide);
    connect(this,&LightCreator::sig_hide_angle,m_outer_angle_lab,&QLabel::hide);


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

    // Selecter Falloff
    connect(this,&LightCreator::sig_hide_falloff,m_falloff_lab,&QLabel::hide);
    connect(this,&LightCreator::sig_hide_falloff,m_falloff_lab_quadratic,&QLabel::hide);
    connect(this,&LightCreator::sig_hide_falloff,m_falloff_lab_constant,&QLabel::hide);
    connect(this,&LightCreator::sig_hide_falloff,m_falloff_lab_linear,&QLabel::hide);
    connect(this,&LightCreator::sig_hide_falloff,m_falloff_spinbox_linear,&QDoubleSpinBox::hide);
    connect(this,&LightCreator::sig_hide_falloff,m_falloff_spinbox_constant,&QDoubleSpinBox::hide);
    connect(this,&LightCreator::sig_hide_falloff,m_falloff_spinbox_quadratic,&QDoubleSpinBox::hide);
    connect(this,&LightCreator::sig_hide_falloff,m_falloff_slider_linear,&QSlider::hide);
    connect(this,&LightCreator::sig_hide_falloff,m_falloff_slider_constant,&QSlider::hide);
    connect(this,&LightCreator::sig_hide_falloff,m_falloff_slider_quadratic,&QSlider::hide);

    connect(this,&LightCreator::sig_show_falloff,m_falloff_lab,&QLabel::show);
    connect(this,&LightCreator::sig_show_falloff,m_falloff_lab_quadratic,&QLabel::show);
    connect(this,&LightCreator::sig_show_falloff,m_falloff_lab_constant,&QLabel::show);
    connect(this,&LightCreator::sig_show_falloff,m_falloff_lab_linear,&QLabel::show);
    connect(this,&LightCreator::sig_show_falloff,m_falloff_spinbox_linear,&QDoubleSpinBox::show);
    connect(this,&LightCreator::sig_show_falloff,m_falloff_spinbox_constant,&QDoubleSpinBox::show);
    connect(this,&LightCreator::sig_show_falloff,m_falloff_spinbox_quadratic,&QDoubleSpinBox::show);
    connect(this,&LightCreator::sig_show_falloff,m_falloff_slider_linear,&QSlider::show);
    connect(this,&LightCreator::sig_show_falloff,m_falloff_slider_constant,&QSlider::show);
    connect(this,&LightCreator::sig_show_falloff,m_falloff_slider_quadratic,&QSlider::show);


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
    connect(m_inner_angle_slider, &QSlider::valueChanged, this , &LightCreator::slot_inner_angle_slide_to_spin );
    connect(this,&LightCreator::sig_inner_angle_slide_to_spin,m_inner_angle_spinbox,&QDoubleSpinBox::setValue);

    connect(m_inner_angle_spinbox, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightCreator::slot_inner_angle_spin_to_slide );
    connect(this,&LightCreator::sig_inner_angle_spin_to_slide,m_inner_angle_slider,&QSlider::setValue);

    connect(m_outer_angle_slider, &QSlider::valueChanged, this , &LightCreator::slot_outer_angle_slide_to_spin );
    connect(this,&LightCreator::sig_outer_angle_slide_to_spin,m_outer_angle_spinbox,&QDoubleSpinBox::setValue);

    connect(m_outer_angle_spinbox, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightCreator::slot_outer_angle_spin_to_slide );
    connect(this,&LightCreator::sig_outer_angle_spin_to_slide,m_outer_angle_slider,&QSlider::setValue);


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





    // Init with Directionnal selected by default
    m_angle_lab->setVisible(false);
    m_angle_lab->setVisible(false);
    m_inner_angle_spinbox->setVisible(false);
    m_inner_angle_slider->setVisible(false);
    m_inner_angle_lab->setVisible(false);
    m_outer_angle_spinbox->setVisible(false);
    m_outer_angle_slider->setVisible(false);
    m_outer_angle_lab->setVisible(false);


    m_pos_x_lab->setVisible(false);
    m_pos_y_lab->setVisible(false);
    m_pos_z_lab->setVisible(false);
    m_pos_x_spin->setVisible(false);
    m_pos_y_spin->setVisible(false);
    m_pos_z_spin->setVisible(false);
    m_coord_lab->setVisible(false);
    m_falloff_lab->setVisible(false);
    m_falloff_spinbox_linear->setVisible(false);
    m_falloff_spinbox_constant->setVisible(false);
    m_falloff_spinbox_quadratic->setVisible(false);
    m_falloff_slider_linear->setVisible(false);
    m_falloff_slider_constant->setVisible(false);
    m_falloff_slider_quadratic->setVisible(false);
    m_falloff_lab_linear->setVisible(false);
    m_falloff_lab_constant->setVisible(false);
    m_falloff_lab_quadratic->setVisible(false);

    m_lineEdit->setPlaceholderText(*m_name);

    m_dir_x_spin->setValue((double) m_direction->x());
    m_dir_y_spin->setValue((double) m_direction->y());
    m_dir_z_spin->setValue((double) m_direction->z());

    m_pos_x_spin->setValue((double) m_position->x());
    m_pos_y_spin->setValue((double) m_position->y());
    m_pos_z_spin->setValue((double) m_position->z());







    m_intensity_spinbox-> setDecimals (NB_DECIMAL);
    m_intensity_spinbox->setMaximum(MAX_INTENSITY);
    m_intensity_slider->setMaximum(MAX_INTENSITY);

    m_inner_angle_spinbox-> setDecimals (NB_DECIMAL);
    m_inner_angle_spinbox->setMaximum(MAX_ANGLE);
    m_inner_angle_slider->setMaximum(MAX_ANGLE);

    m_outer_angle_spinbox-> setDecimals (NB_DECIMAL);
    m_outer_angle_spinbox->setMaximum(MAX_ANGLE);
    m_outer_angle_slider->setMaximum(MAX_ANGLE);

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












    QPalette p;
    p.setColor(QPalette::Background,*m_color);
    m_result_color->setAutoFillBackground(true);
    m_result_color->setPalette(p);


    m_intensity_spinbox->setValue(MAX_INTENSITY);
    m_intensity_slider->setValue(MAX_INTENSITY);
}

LightCreator::~LightCreator(){
  delete m_color;
  delete m_intensity_val;
  delete m_inner_angle_val;
  delete m_outer_angle_val;
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
  Ra::Engine::EntityManager *em = Ra::Engine::RadiumEngine::getInstance()->getEntityManager();
  Ra::Engine::Entity *entity = em->entityExists( "Lights" )  ? em->getEntity( "Lights" ) : em->createEntity( "Lights" );

  *m_name = m_lineEdit->text();
  if( m_name->isEmpty())
    QMessageBox::critical(this, "Watch out !","A new light must have a name !");
  else if( entity->getComponent( m_name->toStdString()) != nullptr) {
    QMessageBox::critical(this, "Watch out !","The name is already used !");
  }
  else if ( *m_lightType !=1 && m_dir_x_spin->value()== 0 && m_dir_y_spin->value()==0 && m_dir_z_spin->value() == 0 ){
    QMessageBox::critical(this, "Watch out !","Direction Vector cannot be null on each conponent (x,y,z) ! ");
  }
  else {

    save_light(entity); // private function

    emit sig_close_windows() ;
  }
}

void LightCreator::save_light(Ra::Engine::Entity *entity){
  double dr,dg,db;
  int ir,ig,ib;
  m_color->getRgb(&ir,&ig,&ib);
  dr=(double)ir;
  dg=(double)ig;
  db=(double)ib;
  dr/=255;
  dg/=255;
  db/=255;
  Core::Color c = Core::Color( dr, dg, db, *m_intensity_val/MAX_INTENSITY );



  switch (*m_lightType) {
    case 0:
    Ra::Engine::DirectionalLight * dir_light;
      dir_light = new Ra::Engine::DirectionalLight( entity,m_name->toStdString() );
      m_direction = new Core::Vector3(m_dir_x_spin->value(),m_dir_y_spin->value(),m_dir_z_spin->value());
      dir_light->setDirection(*m_direction);
      dir_light->setColor(c);
      // End

      break;
    case 1:
      Ra::Engine::PointLight * point_light;
      point_light = new Ra::Engine::PointLight( entity, m_name->toStdString() );
      m_position = new Core::Vector3(m_pos_x_spin->value(),m_pos_y_spin->value(),m_pos_z_spin->value());
      point_light->setPosition(*m_position);
      point_light->setAttenuation((Scalar)*m_falloff_val_constant,(Scalar)*m_falloff_val_linear,(Scalar)*m_falloff_val_quadratic);

        break;
    case 2:
      Ra::Engine::SpotLight * spot_light;
      spot_light = new Ra::Engine::SpotLight( entity, m_name->toStdString() );
      m_position = new Core::Vector3(m_pos_x_spin->value(),m_pos_y_spin->value(),m_pos_z_spin->value());
      spot_light->setPosition(*m_position);
      m_direction = new Core::Vector3(m_dir_x_spin->value(),m_dir_y_spin->value(),m_dir_z_spin->value());
      spot_light->setDirection(*m_direction);

      spot_light->setInnerAngleInDegrees((Scalar) *m_inner_angle_val );
      spot_light->setOuterAngleInDegrees((Scalar) *m_outer_angle_val );
      spot_light->setAttenuation((Scalar)*m_falloff_val_constant,(Scalar)*m_falloff_val_linear,(Scalar)*m_falloff_val_quadratic);

        break;

    default:
      assert(false);
  }

}



/// Selecter Combobox
void LightCreator::slot_select_light(int val){
    *m_lightType = val;
    /*
    usable in the switch  :

    emit sig_show_angle();
    emit sig_show_dir();
    emit sig_show_pos();


    emit sig_hide_angle();
    emit sig_hide_dir();
    emit sig_hide_pos();


    */

    switch (val) {
      case 0: // Directionnal
      emit sig_show_dir();
        emit sig_hide_pos();
        emit sig_hide_falloff();
        emit sig_hide_angle(); break;
      case 1: // Point

      emit sig_show_pos();
        emit sig_show_falloff();
        emit sig_hide_dir();
        emit sig_hide_angle(); break;

      case 2: // Spot
          emit sig_show_angle();
          emit sig_show_dir();
          emit sig_show_falloff();
          emit sig_show_pos();
                              break;


      // case 3: //Area
      //
      //
      //     emit sig_hide_dir();
      //     emit sig_hide_angle();
      //     emit sig_hide_pos(); break;

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

void LightCreator::slot_inner_angle_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_inner_angle_val = tmp;
  emit sig_inner_angle_slide_to_spin(tmp);
}

void LightCreator::slot_inner_angle_spin_to_slide(double val){
  *m_inner_angle_val = val;
  int tmp = (int) val;
  emit sig_inner_angle_spin_to_slide(tmp);
}

void LightCreator::slot_outer_angle_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_outer_angle_val = tmp;
  emit sig_outer_angle_slide_to_spin(tmp);
}

void LightCreator::slot_outer_angle_spin_to_slide(double val){
  *m_outer_angle_val = val;
  int tmp = (int) val;
  emit sig_outer_angle_spin_to_slide(tmp);
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
