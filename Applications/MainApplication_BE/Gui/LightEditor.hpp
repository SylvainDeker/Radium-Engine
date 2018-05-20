#ifndef RADIUMENGINE_LIGHTEDITOR_HPP
#define RADIUMENGINE_LIGHTEDITOR_HPP

#include <QWidget>
#include <QColor>

#include <Engine/ItemModel/ItemEntry.hpp>
#include <Engine/Renderer/Light/Light.hpp>
#include <Engine/Renderer/Light/PointLight.hpp>
#include <Engine/Renderer/Light/SpotLight.hpp>

#include <ui_LightCreator.h>

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
    /// Links slides and spinboxes
    void slot_inner_angle_slide_to_spin(int val);
    void slot_inner_angle_spin_to_slide(double val);
    void slot_outer_angle_slide_to_spin(int val);
    void slot_outer_angle_spin_to_slide(double val);

    void slot_falloff_constant_slide_to_spin(int val);
    void slot_falloff_constant_spin_to_slide(double val);
    void slot_falloff_linear_slide_to_spin(int val);
    void slot_falloff_linear_spin_to_slide(double val);
    void slot_falloff_quadratic_slide_to_spin(int val);
    void slot_falloff_quadratic_spin_to_slide(double val);
    /// Applies changes to light
    void edit_light();

  signals:
    void sig_inner_angle_slide_to_spin(double);
    void sig_inner_angle_spin_to_slide(int);
    void sig_outer_angle_slide_to_spin(double);
    void sig_outer_angle_spin_to_slide(int);
    void sig_falloff_constant_slide_to_spin(double);
    void sig_falloff_constant_spin_to_slide(int);
    void sig_falloff_linear_slide_to_spin(double);
    void sig_falloff_linear_spin_to_slide(int);
    void sig_falloff_quadratic_slide_to_spin(double);
    void sig_falloff_quadratic_spin_to_slide(int);
    void sig_close_window();

    private:
        QColor m_color;
        QPalette m_pal;
        double m_inner_angle;
        double m_outer_angle;
        Ra::Engine::PointLight::Attenuation m_falloff_p;
        Ra::Engine::SpotLight::Attenuation m_falloff_s;
        Core::Math::Vector3 m_direction;
        Core::Math::Vector3 m_position;
        Ra::Engine::Light *m_light;
        Ra::Engine::Light::LightType m_type;
};
} // namespace Gui
} // namespace Ra

#endif // RADIUMENGINE_LIGHTEDITOR_HPP
