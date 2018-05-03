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

    //TODO remove debug output
    bool EditionWidget::selectedSetTransform(Ra::Core::Transform& tf)
    {
        Ra::Engine::ItemEntry item = m_selectionManager->currentItem();

        std::cout << "selection ROidx :" << item.m_roIndex << std::endl;

        if(item.isValid())
        {
            if (item.isEntityNode())
            {
                item.m_entity->setTransform(tf);
                item.m_entity->swapTransformBuffers();
                std::cout << "entity reset done" << std::endl;
                return true;
            } else {
                std::cout << "not an entity" << std::endl;
            }

            //no action if the item is only a component

            if (item.isRoNode() && item.m_component->canEdit(item.m_roIndex))
            {
                item.m_component->setTransform(item.m_roIndex, tf);
                std::cout << "reset done" << std::endl;
                return true;
            } else {
                std::cout << "not a editable RO" << std::endl;
            }
        }

        return false;
    }

    void EditionWidget::resetSelectedObject()
    {
        //we don't care of failure here
        Ra::Core::Transform id = Ra::Core::Transform::Identity();
        selectedSetTransform(id);
    }

    void EditionWidget::selectedSetMatrix(Core::Matrix4 &m)
    {
        Ra::Core::Transform tf = Ra::Core::Transform(m);
        if(selectedSetTransform(tf))
        {
            //TODO if failure ?
        }
    }

}
}
