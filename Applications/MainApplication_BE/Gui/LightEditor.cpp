#include <Gui/LightEditor.hpp>
#include <Gui/MainWindow.hpp>
#include <Engine/ItemModel/ItemEntry.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Renderer/Light/DirLight.hpp>
#include <Engine/Renderer/Light/SpotLight.hpp>

#include <QPushButton>
#include <QColorDialog>
#include <QPalette>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QMessageBox>

#include <math.h>
#define NB_DECIMAL 3
#define MAX_ANGLE 360
#define MAX_CONSTANT 100
#define MAX_LINEAR 100
#define MAX_QUADRA 100
#define MAX_COORD 10000000
#define STEP_SLIDER 100
#define INV_STEP 0.01


namespace Ra {
namespace Gui {
LightEditor::LightEditor( QWidget* parent ) : QWidget( nullptr ) {
    setupUi( this );
    setFixedSize(size());
    m_result_color->setAutoFillBackground(true);

    m_inner_angle_spinbox-> setDecimals (NB_DECIMAL);
    m_inner_angle_spinbox->setMaximum(MAX_ANGLE);
    m_inner_angle_slider->setMaximum(MAX_ANGLE*STEP_SLIDER);

    m_outer_angle_spinbox-> setDecimals (NB_DECIMAL);
    m_outer_angle_spinbox->setMaximum(MAX_ANGLE);
    m_outer_angle_slider->setMaximum(MAX_ANGLE*STEP_SLIDER);

    m_falloff_spinbox_constant->setDecimals (NB_DECIMAL);
    m_falloff_spinbox_constant->setMaximum(MAX_CONSTANT);
    m_falloff_slider_constant->setMaximum(MAX_CONSTANT*STEP_SLIDER);

    m_falloff_spinbox_linear->setDecimals (NB_DECIMAL);
    m_falloff_spinbox_linear->setMaximum(MAX_LINEAR);
    m_falloff_slider_linear->setMaximum(MAX_LINEAR*STEP_SLIDER);

    m_falloff_spinbox_quadratic->setDecimals (NB_DECIMAL);
    m_falloff_spinbox_quadratic->setMaximum(MAX_QUADRA);
    m_falloff_slider_quadratic->setMaximum(MAX_QUADRA*STEP_SLIDER);


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
    connect(m_button_color, &QPushButton::clicked,
            this, &LightEditor::open_dialogColor);

    // Angle
    connect(m_inner_angle_slider, &QSlider::valueChanged,
            this, &LightEditor::slot_inner_angle_slide_to_spin);
    connect(this, &LightEditor::sig_inner_angle_slide_to_spin,
            m_inner_angle_spinbox, &QDoubleSpinBox::setValue);

    connect(m_inner_angle_spinbox,
            static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged),
            this , &LightEditor::slot_inner_angle_spin_to_slide);
    connect(this, &LightEditor::sig_inner_angle_spin_to_slide,
            m_inner_angle_slider, &QSlider::setValue);

    connect(m_outer_angle_slider, &QSlider::valueChanged,
            this, &LightEditor::slot_outer_angle_slide_to_spin);
    connect(this, &LightEditor::sig_outer_angle_slide_to_spin,
            m_outer_angle_spinbox, &QDoubleSpinBox::setValue);

    connect(m_outer_angle_spinbox,
        static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged),
        this, &LightEditor::slot_outer_angle_spin_to_slide);
    connect(this, &LightEditor::sig_outer_angle_spin_to_slide,
        m_outer_angle_slider, &QSlider::setValue);

    // Falloff
    connect(m_falloff_slider_constant, &QSlider::valueChanged,
            this, &LightEditor::slot_falloff_constant_slide_to_spin);
    connect(this, &LightEditor::sig_falloff_constant_slide_to_spin,
            m_falloff_spinbox_constant, &QDoubleSpinBox::setValue);

    connect(m_falloff_spinbox_constant,
            static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged),
            this, &LightEditor::slot_falloff_constant_spin_to_slide);
    connect(this, &LightEditor::sig_falloff_constant_spin_to_slide,
            m_falloff_slider_constant, &QSlider::setValue);

    connect(m_falloff_slider_linear, &QSlider::valueChanged,
            this, &LightEditor::slot_falloff_linear_slide_to_spin);
    connect(this, &LightEditor::sig_falloff_linear_slide_to_spin,
            m_falloff_spinbox_linear, &QDoubleSpinBox::setValue);

    connect(m_falloff_spinbox_linear,
            static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged),
            this, &LightEditor::slot_falloff_linear_spin_to_slide);
    connect(this, &LightEditor::sig_falloff_linear_spin_to_slide,
            m_falloff_slider_linear, &QSlider::setValue);

    connect(m_falloff_slider_quadratic, &QSlider::valueChanged,
            this, &LightEditor::slot_falloff_quadratic_slide_to_spin);
    connect(this, &LightEditor::sig_falloff_quadratic_slide_to_spin,
            m_falloff_spinbox_quadratic, &QDoubleSpinBox::setValue);

    connect(m_falloff_spinbox_quadratic,
            static_cast<void (QDoubleSpinBox::*) (double)>(&QDoubleSpinBox::valueChanged),
            this, &LightEditor::slot_falloff_quadratic_spin_to_slide);
    connect(this, &LightEditor::sig_falloff_quadratic_spin_to_slide,
            m_falloff_slider_quadratic, &QSlider::setValue);

// OK/Cancel Buttons
    connect(m_button_create, &QPushButton::clicked,
            this, &LightEditor::edit_light);
    connect(this, &LightEditor::sig_close_window, this, &QWidget::close);
    connect(m_button_cancel, &QPushButton::clicked, this, &QWidget::close);
}

LightEditor::~LightEditor() {
}

void LightEditor::open_dialogColor() {
    QColor tmp_col;
    tmp_col = QColorDialog::getColor ();
    if (tmp_col == QColor(0,0,0))
        QMessageBox::warning(this,"Watch out !",
            "Selected color : No effect on renderer.");
    if (tmp_col.isValid())
        m_color = tmp_col;
    m_pal.setColor(QPalette::Background, m_color);
    m_result_color->setPalette(m_pal);
}

/// Angle
void LightEditor::slot_inner_angle_slide_to_spin(int val) {
    emit sig_inner_angle_slide_to_spin(((double) val)*INV_STEP);
}

void LightEditor::slot_inner_angle_spin_to_slide(double val) {
    emit sig_inner_angle_spin_to_slide((int) (val*STEP_SLIDER));
}

void LightEditor::slot_outer_angle_slide_to_spin(int val) {
    emit sig_outer_angle_slide_to_spin(((double) val)*INV_STEP);
}

void LightEditor::slot_outer_angle_spin_to_slide(double val) {
    emit sig_outer_angle_spin_to_slide((int) (val*STEP_SLIDER));
}

/// Falloff
void LightEditor::slot_falloff_constant_slide_to_spin(int val) {
    emit sig_falloff_constant_slide_to_spin(((double) val)*INV_STEP);
}

void LightEditor::slot_falloff_constant_spin_to_slide(double val) {
    emit sig_falloff_constant_spin_to_slide((int) (val*STEP_SLIDER));
}

void LightEditor::slot_falloff_linear_slide_to_spin(int val) {
    emit sig_falloff_linear_slide_to_spin(((double) val)*INV_STEP);
}

void LightEditor::slot_falloff_linear_spin_to_slide(double val) {
    emit sig_falloff_linear_spin_to_slide((int) (val*STEP_SLIDER));
}
void LightEditor::slot_falloff_quadratic_slide_to_spin(int val) {
    emit sig_falloff_quadratic_slide_to_spin(((double) val)*INV_STEP);
}

void LightEditor::slot_falloff_quadratic_spin_to_slide(double val) {
    emit sig_falloff_quadratic_spin_to_slide((int) (val*STEP_SLIDER));
}

void LightEditor::init(Ra::Engine::ItemEntry item) {
    m_light = (Ra::Engine::Light *) item.m_component;
    m_lineEdit->setText(QString::fromStdString(m_light->getName()));
    m_lineEdit->setDisabled(true);
    m_type = m_light->getType();
    m_kind_of_light->setDisabled(true);
    m_kind_of_light->setCurrentIndex(m_type);

    m_entity_group_box->setVisible(false);
    m_entity_lab->setVisible(false);

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

    m_falloff_tip->setVisible(true);
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

    m_dir_tip->setVisible(true);
    m_dir_x_spin->setVisible(true);
    m_dir_y_spin->setVisible(true);
    m_dir_z_spin->setVisible(true);
    m_dir_x_lab->setVisible(true);
    m_dir_y_lab->setVisible(true);
    m_dir_z_lab->setVisible(true);
    m_direction_lab->setVisible(true);

    // Color
    Core::Math::Color col =  m_light->getColor();
    double dr, dg, db;
    dr = col.x();
    dg = col.y();
    db = col.z();
    m_color = QColor((int) (dr*255), (int) (dg*255), (int) (db*255));
    m_pal.setColor(QPalette::Background,m_color);
    m_result_color->setPalette(m_pal);

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

            m_falloff_tip->setVisible(false);
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
            m_falloff_p = ((Ra::Engine::PointLight *) m_light)->getAttenuation();
            m_falloff_spinbox_linear->setValue((double) m_falloff_p.linear);
            m_falloff_spinbox_constant->setValue((double) m_falloff_p.constant);
            m_falloff_spinbox_quadratic->setValue((double) m_falloff_p.quadratic);

            m_position = ((Ra::Engine::PointLight *) m_light)->getPosition();
            m_pos_x_spin->setValue(m_position.x());
            m_pos_y_spin->setValue(m_position.y());
            m_pos_z_spin->setValue(m_position.z());

            m_dir_tip->setVisible(false);
            m_dir_x_spin->setVisible(false);
            m_dir_y_spin->setVisible(false);
            m_dir_z_spin->setVisible(false);
            m_dir_x_lab->setVisible(false);
            m_dir_y_lab->setVisible(false);
            m_dir_z_lab->setVisible(false);
            m_direction_lab->setVisible(false);
            break;
        case 2 : // Spot
            m_direction = ((Ra::Engine::SpotLight *) m_light)->getDirection();
            m_dir_x_spin->setValue((double) m_direction.x());
            m_dir_y_spin->setValue((double) m_direction.y());
            m_dir_z_spin->setValue((double) m_direction.z());

            m_position = ((Ra::Engine::SpotLight *) m_light)->getPosition();
            m_pos_x_spin->setValue(m_position.x());
            m_pos_y_spin->setValue(m_position.y());
            m_pos_z_spin->setValue(m_position.z());

            m_falloff_s = ((Ra::Engine::SpotLight *) m_light)->getAttenuation();
            m_falloff_spinbox_linear->setValue((double) m_falloff_s.linear);
            m_falloff_spinbox_constant->setValue((double) m_falloff_s.constant);
            m_falloff_spinbox_quadratic->setValue((double) m_falloff_s.quadratic);

            m_inner_angle = ((Ra::Engine::SpotLight *) m_light)->getInnerAngle();
            m_outer_angle = ((Ra::Engine::SpotLight *) m_light)->getOuterAngle();
            m_inner_angle_spinbox->setValue(Core::Math::toDegrees(m_inner_angle));
            m_outer_angle_spinbox->setValue(Core::Math::toDegrees(m_outer_angle));

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

void LightEditor::edit_light() {

    switch (m_type) {
        case 0 : // Directional Light
            m_direction = Core::Math::Vector3(m_dir_x_spin->value(),
                                              m_dir_y_spin->value(),
                                              m_dir_z_spin->value());
            if ((m_direction.x() == 0) &&
                (m_direction.y() == 0) &&
                (m_direction.z() == 0)) {
                
                QMessageBox::critical(this, "Watch out !",
                    "Direction Vector cannot be null on each conponent (x,y,z) ! ");
                return;
            }
            ((Ra::Engine::DirectionalLight *) m_light)->setDirection(m_direction);

            break;
        case 1 : // Point Light
            ((Ra::Engine::PointLight *) m_light)->setAttenuation(m_falloff_spinbox_constant->value(),
                                                                 m_falloff_spinbox_linear->value(),
                                                                 m_falloff_spinbox_quadratic->value());

            m_position = Core::Math::Vector3(m_pos_x_spin->value(),
                                             m_pos_y_spin->value(),
                                             m_pos_z_spin->value());
            ((Ra::Engine::PointLight *) m_light)->setPosition(m_position);

            break;
        case 2 : // Spot Light
            m_direction = Core::Math::Vector3(m_dir_x_spin->value(),
                                              m_dir_y_spin->value(),
                                              m_dir_z_spin->value());
            if ((m_direction.x() == 0) &&
                (m_direction.y() == 0) &&
                (m_direction.z() == 0)) {

                QMessageBox::critical(this, "Watch out !",
                    "Direction Vector cannot be null on each conponent (x,y,z) ! ");
                return;
            }
            ((Ra::Engine::SpotLight *) m_light)->setDirection(m_direction);

            ((Ra::Engine::SpotLight *) m_light)->setAttenuation(m_falloff_spinbox_constant->value(),
                                                                m_falloff_spinbox_linear->value(),
                                                                m_falloff_spinbox_quadratic->value());

            m_position = Core::Math::Vector3(m_pos_x_spin->value(),
                                             m_pos_y_spin->value(),
                                             m_pos_z_spin->value());
            ((Ra::Engine::SpotLight *) m_light)->setPosition(m_position);

            ((Ra::Engine::SpotLight *) m_light)->setInnerAngleInDegrees(m_inner_angle_spinbox->value());
            ((Ra::Engine::SpotLight *) m_light)->setOuterAngleInDegrees(m_outer_angle_spinbox->value());

            break;
        default :
            break;
    }
    // Color
    int ir, ig, ib;
    m_color.getRgb(&ir, &ig, &ib);
    m_light->setColor(Core::Math::Color(((double) ir)/255,
                                        ((double) ig)/255,
                                        ((double) ib)/255,0));

    emit sig_close_window();
}

} // namespace Gui
} // namespace Ra
