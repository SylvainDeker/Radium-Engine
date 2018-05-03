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
        QObject::connect(resetButton, SIGNAL(clicked()), this, SLOT(resetSelectedObject()));

        QVBoxLayout* layout = new QVBoxLayout(this);

        layout->addWidget(resetButton);
    }

    void EditionWidget::resetSelectedObject()
    {
        Ra::Engine::ItemEntry item = m_selectionManager->currentItem();

        std::cout << "selection ROidx :" << item.m_roIndex << std::endl;

        if(item.isValid())
        {
            Ra::Core::Transform transform = Ra::Core::Transform::Identity();
            if (item.isEntityNode())
            {
                item.m_entity->setTransform(transform);
                item.m_entity->swapTransformBuffers();
                std::cout << "entity reset done" << std::endl;
            } else {
                std::cout << "not an entity" << std::endl;
            }

            //no action if the item is only a component

            if (item.isRoNode() && item.m_component->canEdit(item.m_roIndex))
            {
                item.m_component->setTransform(item.m_roIndex, transform);
                std::cout << "reset done" << std::endl;
            } else {
                std::cout << "not a editable RO" << std::endl;
            }
        }
    }

}
}
