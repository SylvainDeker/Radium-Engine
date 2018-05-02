#ifndef RADIUMENGINE_LIGHTCREATOR_HPP
#define RADIUMENGINE_LIGHTCREATOR_HPP

#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <memory>
#include <QLineEdit>

#include <Core/Container/Index.hpp>
//#include <Engine/Renderer/RenderObject/RenderObject.hpp>

#include <Gui/LightCreator.hpp>

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
class LightCreator : public QWidget {
    Q_OBJECT

  public:
    LightCreator( QWidget* parent = nullptr );



  public slots:


  protected:


  private:

  private:
    QFormLayout * m_form;
    QLabel * m_namelab;
    QLineEdit * m_nameedit;

};
} // namespace Gui
} // namespace Ra

#endif // RADIUMENGINE_LightCreator_HPP
