#include <Gui/LightEditor.hpp>
#include <Gui/MainWindow.hpp>
#include <Engine/ItemModel/ItemEntry.hpp>
#include <Engine/Component/Component.hpp>

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
LightEditor::LightEditor( QWidget* parent ) : QWidget( nullptr )    {
    setupUi( this );
    m_color = QColor(255,255,255);
    m_inner_angle_val = new double(0);
    m_outer_angle_val = new double(0);
    m_falloff_val_constant = new double(0);
    m_falloff_val_linear = new double(0);
    m_falloff_val_quadratic = new double(0);


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



    setWindowTitle("Light Editor");
    QPalette p;
    p.setColor(QPalette::Background,m_color);
    m_result_color->setAutoFillBackground(true);
    m_result_color->setPalette(p);
    connect(m_button_color, &QPushButton::clicked,this,&LightEditor::open_dialogColor);


    // Angle
    connect(m_inner_angle_slider, &QSlider::valueChanged, this , &LightEditor::slot_inner_angle_slide_to_spin );
    connect(this,&LightEditor::sig_inner_angle_slide_to_spin,m_inner_angle_spinbox,&QDoubleSpinBox::setValue);

    connect(m_inner_angle_spinbox, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightEditor::slot_inner_angle_spin_to_slide );
    connect(this,&LightEditor::sig_inner_angle_spin_to_slide,m_inner_angle_slider,&QSlider::setValue);

    connect(m_outer_angle_slider, &QSlider::valueChanged, this , &LightEditor::slot_outer_angle_slide_to_spin );
    connect(this,&LightEditor::sig_outer_angle_slide_to_spin,m_outer_angle_spinbox,&QDoubleSpinBox::setValue);

    connect(m_outer_angle_spinbox, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightEditor::slot_outer_angle_spin_to_slide );
    connect(this,&LightEditor::sig_outer_angle_spin_to_slide,m_outer_angle_slider,&QSlider::setValue);

    // Falloff

    connect(m_falloff_slider_constant, &QSlider::valueChanged, this , &LightEditor::slot_falloff_constant_slide_to_spin );
    connect(this,&LightEditor::sig_falloff_constant_slide_to_spin,m_falloff_spinbox_constant,&QDoubleSpinBox::setValue);

    connect(m_falloff_spinbox_constant, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightEditor::slot_falloff_constant_spin_to_slide );
    connect(this,&LightEditor::sig_falloff_constant_spin_to_slide,m_falloff_slider_constant,&QSlider::setValue);

    connect(m_falloff_slider_linear, &QSlider::valueChanged, this , &LightEditor::slot_falloff_linear_slide_to_spin );
    connect(this,&LightEditor::sig_falloff_linear_slide_to_spin,m_falloff_spinbox_linear,&QDoubleSpinBox::setValue);

    connect(m_falloff_spinbox_linear, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightEditor::slot_falloff_linear_spin_to_slide );
    connect(this,&LightEditor::sig_falloff_linear_spin_to_slide,m_falloff_slider_linear,&QSlider::setValue);

    connect(m_falloff_slider_quadratic, &QSlider::valueChanged, this , &LightEditor::slot_falloff_quadratic_slide_to_spin );
    connect(this,&LightEditor::sig_falloff_quadratic_slide_to_spin,m_falloff_spinbox_quadratic,&QDoubleSpinBox::setValue);

    connect(m_falloff_spinbox_quadratic, static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged), this , &LightEditor::slot_falloff_quadratic_spin_to_slide );
    connect(this,&LightEditor::sig_falloff_quadratic_spin_to_slide,m_falloff_slider_quadratic,&QSlider::setValue);

// OK Button
    connect(m_button_create,&QPushButton::clicked,this,&LightEditor::edit_light);
    connect(this,&LightEditor::sig_close_window,this,&QWidget::close);

}

LightEditor::~LightEditor(){
  delete m_inner_angle_val;
  delete m_outer_angle_val;
  delete m_falloff_val_constant;
  delete m_falloff_val_linear;
  delete m_falloff_val_quadratic;
  delete m_name;
}

void LightEditor::open_dialogColor(){
  m_color = QColorDialog::getColor ();
  QPalette p;

  p.setColor(QPalette::Background,m_color);
  m_result_color->setPalette(p);

}

/// Angle

void LightEditor::slot_inner_angle_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_inner_angle_val = tmp;
  emit sig_inner_angle_slide_to_spin(tmp);
}

void LightEditor::slot_inner_angle_spin_to_slide(double val){
  *m_inner_angle_val = val;
  int tmp = (int) val;
  emit sig_inner_angle_spin_to_slide(tmp);
}

void LightEditor::slot_outer_angle_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_outer_angle_val = tmp;
  emit sig_outer_angle_slide_to_spin(tmp);
}

void LightEditor::slot_outer_angle_spin_to_slide(double val){
  *m_outer_angle_val = val;
  int tmp = (int) val;
  emit sig_outer_angle_spin_to_slide(tmp);
}


/// Falloff
void LightEditor::slot_falloff_constant_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_falloff_val_constant = tmp;
  emit sig_falloff_constant_slide_to_spin(*m_falloff_val_constant);
}

void LightEditor::slot_falloff_constant_spin_to_slide(double val){
  *m_falloff_val_constant = val;
  int tmp = (int) val;
  emit sig_falloff_constant_spin_to_slide(tmp);
}

void LightEditor::slot_falloff_linear_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_falloff_val_linear = tmp;
  emit sig_falloff_linear_slide_to_spin(*m_falloff_val_linear);
}

void LightEditor::slot_falloff_linear_spin_to_slide(double val){
  *m_falloff_val_linear = val;
  int tmp = (int) val;
  emit sig_falloff_linear_spin_to_slide(tmp);
}
void LightEditor::slot_falloff_quadratic_slide_to_spin(int val){
  double tmp =  (double) val;
  *m_falloff_val_quadratic = tmp;
  emit sig_falloff_quadratic_slide_to_spin(*m_falloff_val_quadratic);
}

void LightEditor::slot_falloff_quadratic_spin_to_slide(double val){
  *m_falloff_val_quadratic = val;
  int tmp = (int) val;
  emit sig_falloff_quadratic_spin_to_slide(tmp);
}

void LightEditor::init(Ra::Engine::ItemEntry item){
    m_light = (Ra::Engine::Light *) item.m_component;
    m_lineEdit->setText(QString::fromStdString(m_light->getName()));
    m_lineEdit->setDisabled(true);
    m_type = m_light->getType();
    m_kind_of_light->setDisabled(true);
    m_kind_of_light->setCurrentIndex(m_type);
    
    m_angle_lab->setVisible(false);
    m_angle_lab->setVisible(false);
    m_inner_angle_spinbox->setVisible(false);
    m_inner_angle_slider->setVisible(false);
    m_inner_angle_lab->setVisible(false);
    m_outer_angle_spinbox->setVisible(false);
    m_outer_angle_slider->setVisible(false);
    m_outer_angle_lab->setVisible(false);

    m_pos_x_lab->setVisible(true);
    m_pos_y_lab->setVisible(true);
    m_pos_z_lab->setVisible(true);
    m_pos_x_spin->setVisible(true);
    m_pos_y_spin->setVisible(true);
    m_pos_z_spin->setVisible(true);
    m_coord_lab->setVisible(true);

    m_falloff_lab->setVisible(true);
    m_falloff_spinbox_linear->setVisible(true);
    m_falloff_spinbox_constant->setVisible(true);
    m_falloff_spinbox_quadratic->setVisible(true);
    m_falloff_slider_linear->setVisible(true);
    m_falloff_slider_constant->setVisible(true);
    m_falloff_slider_quadratic->setVisible(true);
    m_falloff_lab_linear->setVisible(true);
    m_falloff_lab_constant->setVisible(true);
    m_falloff_lab_quadratic->setVisible(true);

    m_dir_x_spin->setVisible(true);
    m_dir_y_spin->setVisible(true);
    m_dir_z_spin->setVisible(true);
    m_dir_x_lab->setVisible(true);
    m_dir_y_lab->setVisible(true);
    m_dir_z_lab->setVisible(true);
    m_direction_lab->setVisible(true);
    
    /*m_color = m_light->getColor();
    QPalette p;
    p.setColor(QPalette::Background,m_color);
    m_result_color->setPalette(p);*/


    switch (m_type) {
        case 0 : // Directional
            m_direction = ((Ra::Engine::DirectionalLight *) m_light)->getDirection();
            m_dir_x_spin->setValue((double) m_direction.x());
            m_dir_y_spin->setValue((double) m_direction.y());
            m_dir_z_spin->setValue((double) m_direction.z());

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
            break;
        case 1 : // Point
            m_dir_x_spin->setVisible(false);
            m_dir_y_spin->setVisible(false);
            m_dir_z_spin->setVisible(false);
            m_dir_x_lab->setVisible(false);
            m_dir_y_lab->setVisible(false);
            m_dir_z_lab->setVisible(false);
            m_direction_lab->setVisible(false);
            break;
        case 2 : // Spot
            m_angle_lab->setVisible(true);
            m_angle_lab->setVisible(true);
            m_inner_angle_spinbox->setVisible(true);
            m_inner_angle_slider->setVisible(true);
            m_inner_angle_lab->setVisible(true);
            m_outer_angle_spinbox->setVisible(true);
            m_outer_angle_slider->setVisible(true);
            m_outer_angle_lab->setVisible(true);
            break;
        default :
            return;
    }

    show();
}

void LightEditor::edit_light(){
    emit sig_close_window();
}

} // namespace Gui
} // namespace Ra
