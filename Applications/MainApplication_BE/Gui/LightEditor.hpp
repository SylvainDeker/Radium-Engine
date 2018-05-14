#ifndef RADIUMENGINE_LIGHTEDITOR_HPP
#define RADIUMENGINE_LIGHTEDITOR_HPP

#include <QWidget>
#include <QColor>
#include <memory>

#include <Core/Container/Index.hpp>
//#include <Engine/Renderer/RenderObject/RenderObject.hpp>

#include <ui_LightEditor.h>

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
class LightEditor : public QWidget, private Ui::LightEditor {

  Q_OBJECT

  public:
    LightEditor( QWidget* parent = nullptr );

  private slots:
    void open_dialogColor();
    void slot_intensity_slide_to_spin(int val);
    void slot_intensity_spin_to_slide(double val);
    void slot_angle_slide_to_spin(int val);
    void slot_angle_spin_to_slide(double val);
    void slot_falloff_slide_to_spin(int val);
    void slot_falloff_spin_to_slide(double val);

  signals:
    void sig_intensity_slide_to_spin(double);
    void sig_intensity_spin_to_slide(int);
    void sig_angle_slide_to_spin(double);
    void sig_angle_spin_to_slide(int);
    void sig_falloff_slide_to_spin(double);
    void sig_falloff_spin_to_slide(int);



  protected:


  private:


  private:
    QColor m_color;
    double m_intensity_val;
    double m_angle_val;
    double m_falloff_val;


};
} // namespace Gui
} // namespace Ra

#endif // RADIUMENGINE_LIGHTEDITOR_HPP
