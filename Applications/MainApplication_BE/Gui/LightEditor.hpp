#ifndef RADIUMENGINE_LightEditor_HPP
#define RADIUMENGINE_LightEditor_HPP

#include <QWidget>

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


  protected:


  private:


  private:

};
} // namespace Gui
} // namespace Ra

#endif // RADIUMENGINE_LightEditor_HPP
