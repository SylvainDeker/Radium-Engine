#ifndef RADIUMENGINE_LIGHTEDITOR_HPP
#define RADIUMENGINE_LIGHTEDITOR_HPP

#include <QWidget>
#include <QColor>
#include <memory>

#include <Engine/ItemModel/ItemEntry.hpp>
#include <Core/Container/Index.hpp>

#include <ui_LightCreator.h>

class QCloseEvent;
class QShowEvent;

namespace Ra {
namespace Engine {
class RadiumEngine;
class RenderObjectManager;
class RenderObject;
} // namespace Engine
} // namespace Ra

namespace Ra {
namespace Gui {
class LightEditor : public QWidget, private Ui::LightCreator {

  Q_OBJECT

  public:
    LightEditor( QWidget* parent = nullptr );
    ~LightEditor();
    void init(Ra::Engine::ItemEntry item);

  private slots:
    /// Dialog to select a color
    void open_dialogColor();
    /// Used to change value of the QDoubleSpinBox when you move the QSlider (and conversaly)
    void slot_intensity_slide_to_spin(int val);
    void slot_intensity_spin_to_slide(double val);
    void slot_inner_angle_slide_to_spin(int val);
    void slot_inner_angle_spin_to_slide(double val);
    void slot_outter_angle_slide_to_spin(int val);
    void slot_outter_angle_spin_to_slide(double val);

    void slot_falloff_constant_slide_to_spin(int val);
    void slot_falloff_constant_spin_to_slide(double val);
    void slot_falloff_linear_slide_to_spin(int val);
    void slot_falloff_linear_spin_to_slide(double val);
    void slot_falloff_quadratic_slide_to_spin(int val);
    void slot_falloff_quadratic_spin_to_slide(double val);
    /// Used to check if the name is not empty
    void open_dialogueConfirm();

  signals:
    void sig_intensity_slide_to_spin(double);
    void sig_intensity_spin_to_slide(int);
    void sig_inner_angle_slide_to_spin(double);
    void sig_inner_angle_spin_to_slide(int);
    void sig_outter_angle_slide_to_spin(double);
    void sig_outter_angle_spin_to_slide(int);
    void sig_falloff_constant_slide_to_spin(double);
    void sig_falloff_constant_spin_to_slide(int);
    void sig_falloff_linear_slide_to_spin(double);
    void sig_falloff_linear_spin_to_slide(int);
    void sig_falloff_quadratic_slide_to_spin(double);
    void sig_falloff_quadratic_spin_to_slide(int);



    void sig_onItemAdded( const Engine::ItemEntry& ent );


    void sig_close_windows();
    protected:


    private:


    private:
        QColor *m_color;
        double *m_intensity_val;
        double *m_inner_angle_val;
        double *m_outter_angle_val;
        double *m_falloff_val_constant;
        double *m_falloff_val_linear;
        double *m_falloff_val_quadratic;
        QString *m_name;

};
} // namespace Gui
} // namespace Ra

#endif // RADIUMENGINE_LIGHTEDITOR_HPP
