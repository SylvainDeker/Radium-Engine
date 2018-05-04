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

    bool EditionWidget::setTransform(Ra::Core::Transform& tf)
    {
        Ra::Engine::ItemEntry item = m_selectionManager->currentItem();

        if(item.isValid())
        {
            if (item.isEntityNode())
            {
                item.m_entity->setTransform(tf);
                item.m_entity->swapTransformBuffers();
                return true;
            }

            //no action if the item is only a component

            if (item.isRoNode() && item.m_component->canEdit(item.m_roIndex))
            {
                item.m_component->setTransform(item.m_roIndex, tf);
                return true;
            }
        }

        return false;
    }

    Ra::Core::Transform* EditionWidget::getTransform()
    {
        Ra::Engine::ItemEntry item = m_selectionManager->currentItem();

        if(item.isValid())
        {
            if (item.isEntityNode())
            {
                return item.m_entity->getTransform();
            }

            //no action if the item is only a component

            if (item.isRoNode() && item.m_component->canEdit(item.m_roIndex))
            {
                return item.m_component->getTransform(item.m_roIndex);
            }
        }

        return nullptr;
    }

    void EditionWidget::resetSelectedObject()
    {
        //we don't care of failure here
        Ra::Core::Transform id = Ra::Core::Transform::Identity();
        setTransform(id);
    }

    void EditionWidget::applyMatrix(Core::Matrix4 &m)
    {
        Ra::Core::Transform tf = Ra::Core::Transform(m);
        if(setTransform(tf))
        {
            //TODO if failure ?
        }
    }

}
}
