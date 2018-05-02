#include <Gui/LightCreator.hpp>

#include <Engine/RadiumEngine.hpp>
#include <Engine/Renderer/Material/BlinnPhongMaterial.hpp>
#include <Engine/Renderer/RenderObject/RenderObject.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>
#include <Engine/Renderer/RenderTechnique/RenderTechnique.hpp>

#include <QCloseEvent>
#include <QMessageBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>

namespace Ra {
namespace Gui {
LightCreator::LightCreator( QWidget* parent ) : QWidget(parent){
  setFixedSize(300,300);
  setWindowTitle("Light Creator");
  move(50,50);
  m_form = new QFormLayout();
  this->setLayout(m_form);
  m_namelab = new QLabel("Name: ");
  m_nameedit = new QLineEdit();
  m_form->addWidget(m_namelab);
  m_form->addWidget(m_nameedit);
}


} // namespace Gui
} // namespace Ra
