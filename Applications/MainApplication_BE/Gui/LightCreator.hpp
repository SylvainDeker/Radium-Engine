/*!
   \file LightCreator.hpp
   \brief The Class LightCreator is associated with its ./ui/LightCreator.ui and ./LightCreator.cpp to design GUI to add Lights in RadiumEngine
   \author Sylvain
   \date 16/05/2018
*/
#ifndef RADIUMENGINE_LIGHTCREATOR_HPP_
#define RADIUMENGINE_LIGHTCREATOR_HPP_

#include <QWidget>
#include <QColor>
#include <memory>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <Core/Container/Index.hpp>
#include <Engine/ItemModel/ItemEntry.hpp>
#include <Core/Math/Math.hpp>
#include <Engine/Renderer/Light/Light.hpp>
#include <GuiBase/Viewer/Viewer.hpp>
#include <Engine/Managers/EntityManager/EntityManager.hpp>
#include <Engine/Entity/Entity.hpp>
#include <Core/Container/IndexMap.hpp>
#include <Engine/Managers/SystemDisplay/SystemDisplay.hpp>

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
class Entity;
} // namespace Engine
} // namespace Ra

namespace Ra {
namespace Gui {
class LightCreator : public QWidget, private Ui::LightCreator {

  Q_OBJECT

  public:
    RA_CORE_ALIGNED_NEW

    /*!
       \brief Constructor (call only once)
       \param QWidget* parent only used for the icon
       \param Ra::Gui::Viewer *viewer to add new Lights to the Viewer
    */
    LightCreator( QWidget* parent ,const Ra::Gui::Viewer *viewer );
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
      \brief Cancel the dialog and reset data
    */
    void close_dialogueConfirm();

    /*!
       \brief Slot that hides elements that are not required
       \param _DIR_LIGHT or _POINT_LIGHT or _SPOT_LIGHT define in LightCreator.hpp
       \return void
    */
    void slot_select_light(const int type);

    /////////////////////////////////////////   ANGLES  SLOTS//////////////////
    /*!
       \brief Slot that sync QDoubleSpinBox from QSlider of Inner Angles options
    */
    void slot_inner_angle_slide_to_spin(const int val);

    /*!
       \brief Slot that sync QSlider from QDoubleSpinBox of Inner Angles options
    */
    void slot_inner_angle_spin_to_slide(const double val);

    /*!
       \brief Slot that sync QDoubleSpinBox from QSlider of Outer Angles options
    */
    void slot_outer_angle_slide_to_spin(const int val);

    /*!
       \brief Slot that sync QSlider from QDoubleSpinBox of Outer Angles options
    */
    void slot_outer_angle_spin_to_slide(const double val);

    /////////////////////////////////////////   FALLOFF  SLOTS/////////////////
    /*!
       \brief Slot that sync QDoubleSpinBox from QSlider of falloff options
    */
    void slot_falloff_constant_slide_to_spin(const int val);

    /*!
       \brief Slot that sync QSlider from QDoubleSpinBox  of falloff options
    */
    void slot_falloff_constant_spin_to_slide(const double val);

    /*!
       \brief Slot that sync QDoubleSpinBox from QSlider of falloff options
    */
    void slot_falloff_linear_slide_to_spin(const int val);

    /*!
       \brief Slot that sync QSlider from QDoubleSpinBox of falloff options
    */
    void slot_falloff_linear_spin_to_slide(const double val);

    /*!
       \brief Slot that sync QDoubleSpinBox from QSlider of falloff options
    */
    void slot_falloff_quadratic_slide_to_spin(const int val);

    /*!
       \brief Slot that sync QSlider from QDoubleSpinBox of falloff options
    */
    void slot_falloff_quadratic_spin_to_slide(const double val);

    /*!
      \biref Slot to get selected entity
    */
    void slot_selected_entity(const QString &m_name_entity);

public slots:

    /*!
      \biref Slot that update entities when Entity's Combobox is clicked
    */
    void slot_start();



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

    void sig_hide_angle();
    void sig_hide_dir();
    void sig_hide_pos();
    void sig_hide_falloff();

    void sig_show_angle();
    void sig_show_dir();
    void sig_show_pos();
    void sig_show_falloff();

    void sig_addLight( Ra::Engine::Light * light );

    void sig_show();
    void sig_close_windows();


  protected:

  private:

    Core::Math::Vector3 m_position;
    Core::Math::Vector3 m_direction;
    QColor m_color;
    QString m_name;
    double m_falloff_val_constant;
    double m_falloff_val_linear;
    double m_falloff_val_quadratic;
    double m_outer_angle_val;
    double m_inner_angle_val;
    const Gui::Viewer * m_viewer;
    Core::Container::IndexMap<std::unique_ptr<Ra::Engine::Entity>> m_entities;
    std::vector<Ra::Engine::Entity *> m_entities_vector;
    std::map<std::string, Core::Container::Index> m_entitiesName;
    Ra::Engine::Entity *m_entity_selected;
    int m_lightType;

    /*!
     \brief Private function that save config light parameters
     \param Ra::Engine::Entity *entity because Lights are components and need to be attached to an entity
     \return void
     */
    void save_light();

    /*!
       \brief init function only called once in the Constructor
    */
    void init();
};
} // namespace Gui
} // namespace Ra

#endif // RADIUMENGINE_LightCreator_HPP
