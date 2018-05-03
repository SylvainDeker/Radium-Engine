#include <Gui/EditionWidget.hpp>

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include <Engine/RadiumEngine.hpp>
#include <Engine/Renderer/Renderer.hpp>
#include <Engine/Component/Component.hpp>
#include <Engine/Renderer/RenderObject/RenderObject.hpp>

#include <Core/Math/LinearAlgebra.hpp>

#include <GuiBase/SelectionManager/SelectionManager.hpp>
#include <GuiBase/Utils/PickingManager.hpp>

#include <Gui/MainWindow.hpp>

namespace Ra{
namespace Gui{

    EditionWidget::EditionWidget(QWidget *parent, Ra::GuiBase::SelectionManager* selectionManager) :
        QWidget(parent),
        m_selectionManager(selectionManager)
    {
        QPushButton* resetButton = new QPushButton("Reset", this);
        QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(resetSelectedEntity()));

        QVBoxLayout* layout = new QVBoxLayout(this);

        layout->addWidget(resetButton);
    }

    void EditionWidget::resetSelectedEntity()
    {
        Ra::Engine::ItemEntry item = m_selectionManager->currentItem();

        std::cout << "selected selection :" << item.m_roIndex << std::endl;

        /*if ( data.m_mode == Ra::Engine::Renderer::PickingMode::RO && Ra::Engine::RadiumEngine::getInstance()->getRenderObjectManager()->exists( data.m_roIdx ) )
        {
             std::shared_ptr<Ra::Engine::RenderObject> ro = Ra::Engine::RadiumEngine::getInstance()->getRenderObjectManager()->getRenderObject(data.m_roIdx);

             Ra::Core::Matrix4 transform;
             transform << 1, 0, 0, 0,
                          0, 1, 0, 0,
                          0, 0, 1, 0,
                          0, 0, 0, 1;
             ro->setLocalTransform(transform);

             std::cout << "reset done" << std::endl;
        } else {
            std::cout << "cannot reset that" << std::endl;
        }*/
        if(item.isValid())
        {
            Ra::Core::Transform transform = Ra::Core::Transform::Identity();

            if (item.isEntityNode())
            {
                item.m_entity->setTransform(transform);
                std::cout << "reset done" << std::endl;
            } else {
                std::cout << "not an entity" << std::endl;
            }

            if (item.isComponentNode())
            {
                item.m_component->setTransform(item.m_roIndex, transform);
                std::cout << "reset done" << std::endl;
            } else {
                std::cout << "not a component" << std::endl;
            }

            if ( Ra::Engine::RadiumEngine::getInstance()->getRenderObjectManager()->exists( item.m_roIndex ) )
            {
                std::shared_ptr<Ra::Engine::RenderObject> ro = Ra::Engine::RadiumEngine::getInstance()->getRenderObjectManager()->getRenderObject(item.m_roIndex);
                ro->setLocalTransform(transform);
                std::cout << "reset done" << std::endl;
            } else {
                std::cout << "not a RO" << std::endl;
            }
        }
    }

}
}
