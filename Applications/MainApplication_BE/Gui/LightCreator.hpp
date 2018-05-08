#ifndef RADIUMENGINE_LIGHTCREATOR_HPP
#define RADIUMENGINE_LIGHTCREATOR_HPP

#include <QWidget>
#include <QColor>
#include <memory>

#include <Core/Container/Index.hpp>
#include <Engine/ItemModel/ItemEntry.hpp>

#include <ui_LightCreator.h>

class QCloseEvent;
class QShowEvent;

namespace Ra {
namespace Engine {
class RadiumEngine;
class RenderObjectManager;
class RenderObject;
class Material;
class BlinnPhongMaterial;
} // namespace Engine
} // namespace Ra

namespace Ra {
namespace Gui {
class LightCreator : public QWidget, private Ui::LightCreator {

  Q_OBJECT

  public:
    LightCreator( QWidget* parent = nullptr );

  private slots:
    /// Dialog to select a color
    void open_dialogColor();
    /// Used to change value of the QDoubleSpinBox when you move the QSlider (and conversaly)
    void slot_intensity_slide_to_spin(int val);
    void slot_intensity_spin_to_slide(double val);
    void slot_angle_slide_to_spin(int val);
    void slot_angle_spin_to_slide(double val);

    void slot_falloff_constant_slide_to_spin(int val);
    void slot_falloff_constant_spin_to_slide(double val);
    void slot_falloff_linear_slide_to_spin(int val);
    void slot_falloff_linear_spin_to_slide(double val);
    void slot_falloff_quadratic_slide_to_spin(int val);
    void slot_falloff_quadratic_spin_to_slide(double val);
    void slot_select_light(int val);
    /// Used to check if the name is not empty
    void open_dialogueConfirm();

  signals:
    void sig_intensity_slide_to_spin(double);
    void sig_intensity_spin_to_slide(int);
    void sig_angle_slide_to_spin(double);
    void sig_angle_spin_to_slide(int);
    void sig_falloff_constant_slide_to_spin(double);
    void sig_falloff_constant_spin_to_slide(int);
    void sig_falloff_linear_slide_to_spin(double);
    void sig_falloff_linear_spin_to_slide(int);
    void sig_falloff_quadratic_slide_to_spin(double);
    void sig_falloff_quadratic_spin_to_slide(int);

    void sig_hide_angle();
    void sig_hide_dir();
    void sig_hide_pos();
    // void sig_hide_falloff();

    void sig_show_angle();
    void sig_show_dir();
    void sig_show_pos();
    // void sig_show_falloff();


    void sig_onItemAdded( const Engine::ItemEntry& ent );


    void sig_close_windows();


  protected:

  private:

    int * m_lightType;
    QColor *m_color;
    double *m_intensity_val;
    double *m_angle_val;
    double *m_falloff_val_constant;
    double *m_falloff_val_linear;
    double *m_falloff_val_quadratic;
    QString *m_name;

};
} // namespace Gui
} // namespace Ra

#endif // RADIUMENGINE_LightCreator_HPP
