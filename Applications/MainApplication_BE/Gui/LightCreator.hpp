#ifndef RADIUMENGINE_LIGHTCREATOR_HPP
#define RADIUMENGINE_LIGHTCREATOR_HPP

#include <QWidget>

#include <memory>

#include <Core/Container/Index.hpp>
//#include <Engine/Renderer/RenderObject/RenderObject.hpp>

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


  protected:


  private:


  private:

};
} // namespace Gui
} // namespace Ra

#endif // RADIUMENGINE_LightCreator_HPP
