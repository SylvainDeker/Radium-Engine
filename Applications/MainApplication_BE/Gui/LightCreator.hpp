/*!
   \file LightCreator.hpp
   \brief The Class LightCreator is associated with its ./ui/LightCreator.ui and ./LightCreator.cpp to design GUI to add Lights in RadiumEngine
   \author Sylvain
   \date 16/05/2018
*/
#ifndef RADIUMENGINE_LIGHTCREATOR_HPP
#define RADIUMENGINE_LIGHTCREATOR_HPP

#include <QWidget>
#include <QColor>
#include <memory>

#include <Core/Container/Index.hpp>
#include <Engine/ItemModel/ItemEntry.hpp>
#include <Core/Math/Math.hpp>
#include <Engine/Renderer/Light/Light.hpp>
#include <GuiBase/Viewer/Viewer.hpp>

#include <ui_LightCreator.h>
#define _DIR_LIGHT 0
#define _POINT_LIGHT 1
#define _SPOT_LIGHT 2

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
    /*!
       \brief Constructor (call only once)
       \param QWidget* parent only used for the icon
       \param Ra::Gui::Viewer *viewer to add new Lights to the Viewer
    */
    LightCreator( QWidget* parent ,Ra::Gui::Viewer *viewer );
    /*!
       \brief Destructor
    */
    ~LightCreator();

  private slots:
    /*!
       \brief Select a color
    */
    void open_dialogColor();

    /*!
       \brief Slot that check data and save
    */
    void open_dialogueConfirm();

    /*!
       \brief Slot that hides elements that are not required
       \param _DIR_LIGHT or _POINT_LIGHT or _SPOT_LIGHT define in LightCreator.hpp
       \return void
    */
    void slot_select_light(int type);


    /////////////////////////////////////////   INTENSITY  SLOTS///////////////////
    /*!
       \brief Slot that sync QDoubleSpinBox from QSlider of Intensity options
    */
    void slot_intensity_slide_to_spin(int val);

    /*!
       \brief Slot that sync QSlider from QDoubleSpinBox  of Intensity options
    */
    void slot_intensity_spin_to_slide(double val);

    /////////////////////////////////////////   ANGLES  SLOTS///////////////////
    /*!
       \brief Slot that sync QDoubleSpinBox from QSlider of Inner Angles options
    */
    void slot_inner_angle_slide_to_spin(int val);

    /*!
       \brief Slot that sync QSlider from QDoubleSpinBox of Inner Angles options
    */
    void slot_inner_angle_spin_to_slide(double val);

    /*!
       \brief Slot that sync QDoubleSpinBox from QSlider of Outer Angles options
    */
    void slot_outer_angle_slide_to_spin(int val);

    /*!
       \brief Slot that sync QSlider from QDoubleSpinBox of Outer Angles options
    */
    void slot_outer_angle_spin_to_slide(double val);

    /////////////////////////////////////////   FALLOFF  SLOTS///////////////////
    /*!
       \brief Slot that sync QDoubleSpinBox from QSlider of falloff options
    */
    void slot_falloff_constant_slide_to_spin(int val);

    /*!
       \brief Slot that sync QSlider from QDoubleSpinBox  of falloff options
    */
    void slot_falloff_constant_spin_to_slide(double val);

    /*!
       \brief Slot that sync QDoubleSpinBox from QSlider of falloff options
    */
    void slot_falloff_linear_slide_to_spin(int val);

    /*!
       \brief Slot that sync QSlider from QDoubleSpinBox of falloff options
    */
    void slot_falloff_linear_spin_to_slide(double val);

    /*!
       \brief Slot that sync QDoubleSpinBox from QSlider of falloff options
    */
    void slot_falloff_quadratic_slide_to_spin(int val);

    /*!
       \brief Slot that sync QSlider from QDoubleSpinBox of falloff options
    */
    void slot_falloff_quadratic_spin_to_slide(double val);





  signals:
    void sig_intensity_slide_to_spin(double);
    void sig_intensity_spin_to_slide(int);
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

    void sig_hide_angle();
    void sig_hide_dir();
    void sig_hide_pos();
    void sig_hide_falloff();

    void sig_show_angle();
    void sig_show_dir();
    void sig_show_pos();
    void sig_show_falloff();


    void sig_addLight( Ra::Engine::Light * light );


    void sig_close_windows();


  protected:

  private:

    int * m_lightType;
    QColor *m_color;
    double *m_intensity_val;
    double *m_inner_angle_val;
    double *m_outer_angle_val;
    double *m_falloff_val_constant;
    double *m_falloff_val_linear;
    double *m_falloff_val_quadratic;
    QString *m_name;
    Core::Vector3 *m_position;
    Core::Vector3 *m_direction;
    Gui::Viewer * m_viewer;

    /*!
       \brief Private function that save config light parameters
       \param Ra::Engine::Entity *entity because Lights are components and need to be attached to an entity
       \return void
    */
    void save_light(Ra::Engine::Entity *entity);
};
} // namespace Gui
} // namespace Ra

#endif // RADIUMENGINE_LightCreator_HPP
