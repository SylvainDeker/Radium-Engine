#include <Gui/LightCreator.hpp>
#include <Gui/MainWindow.hpp>
#include <QPushButton>
#include <QColorDialog>
#include <QPalette>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QMessageBox>

#include <math.h>

namespace Ra {
namespace Gui {
LightCreator::LightCreator( QWidget* parent ) : QWidget( parent )    {
    setupUi( this );
    m_color = new QColor(255,255,255);
    m_name = new QString("");
    m_intensity_val = new double(0);
    m_angle_val = new double(0);
    m_falloff_val = new double(0);
    QPalette p;

    p.setColor(QPalette::Background,*m_color);
    m_result_color->setAutoFillBackground(true);
    m_result_color->setPalette(p);
    connect(m_button_color, &QPushButton::clicked,this,&LightCreator::open_dialogColor);

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

    connect(m_falloff_slider, &QSlider::valueChanged, this , &LightCreator::slot_falloff_slide_to_spin );
    connect(this,&LightCreator::sig_falloff_slide_to_spin,m_falloff_spinbox,&QDoubleSpinBox::setValue);

    connect(m_falloff_spinbox, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightCreator::slot_falloff_spin_to_slide );
    connect(this,&LightCreator::sig_falloff_spin_to_slide,m_falloff_slider,&QSlider::setValue);

    // Create Button
    connect(m_button_create,&QPushButton::clicked,this,&LightCreator::open_dialogueConfirm);
    connect(this,&LightCreator::sig_close_windows,this,&QWidget::close);

}

LightCreator::~LightCreator(){
  delete m_color;
  delete m_intensity_val;
  delete m_angle_val;
  delete m_falloff_val;
  delete m_name;
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
    QMessageBox::critical(this, "Light Crator","A new light must have a name !");
  else {
    emit sig_close_windows() ;
    // Create new Light TODO
  }
}

// Intensity
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

// Angle

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


// Falloff
void LightCreator::slot_falloff_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_falloff_val = tmp;
  emit sig_falloff_slide_to_spin(*m_falloff_val);
}

void LightCreator::slot_falloff_spin_to_slide(double val){
  *m_falloff_val = val;
  int tmp = (int) val;
  emit sig_falloff_spin_to_slide(tmp);
}





} // namespace Gui
} // namespace Ra
