#include <Gui/EditionWidget.hpp>

#include <string>
#include <vector>

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
        setupUi(this);
        QObject::connect(m_resetButton, SIGNAL(clicked()), this, SLOT(resetSelectedObject()));
        QObject::connect(m_applyButton, SIGNAL(clicked()), this, SLOT(applyMatrix()));

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

    bool EditionWidget::getTransform(Ra::Core::Transform* tf)
    {
        Ra::Engine::ItemEntry item = m_selectionManager->currentItem();

        if(item.isValid())
        {
            if (item.isEntityNode())
            {
                *tf = item.m_entity->getTransform();
                return true;
            }

            //no action if the item is only a component

            if (item.isRoNode() && item.m_component->canEdit(item.m_roIndex))
            {
                *tf = item.m_component->getTransform(item.m_roIndex);
                return true;
            }
        }

        return false;
    }

    void EditionWidget::resetSelectedObject()
    {
        //we don't care of failure here
        Ra::Core::Transform id = Ra::Core::Transform::Identity();
        setTransform(id);
    }

    void EditionWidget::applyMatrix()
    {
        int index = tabWidget->currentIndex();

        switch(index)
        {
        case 0 :
            //wolfram
            applyWolfram();
            break;
        case 1 :
            //direct
            applyDirect();
            break;
        default :
            //TODO ?
            break;
        }
    }

    bool EditionWidget::applyWolfram()
    {
        std::cout << "Wolfram !" << std::endl;

        Core::Matrix4 m;
        m << 1, 0, 0, 0,
             0, 1, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 1;
        std::string input = m_wolframEdit->toPlainText().toStdString();

        if( input.find("{") != 0 )
        {
            //bad input
            return false;
        }

        //remove all spaces
        for(size_t pos = input.find(" "); pos != std::string::npos; pos = input.find(" ")){
            input.erase(pos, pos+1);
        }

        int l = 0;
        size_t spos = 0;
        size_t epos = input.find("}");
        while ( (spos != std::string::npos) &&
                (epos != std::string::npos) &&
                (l < 4) )
        {
            std::string line = input.substr(spos+1, epos-1);
            input.erase(spos, epos+1);
            int r = 0;
            size_t colon = line.find(",");
            while( (colon != std::string::npos) &&
                   (r < 4) )
            {
                colon = line.find(",");
                std::string num = line.substr(0,colon);
                std::cout << num << std::endl;
                m(l,r) = std::stoi(num);
                line.erase(0,colon+1);
                ++r;
            }
            spos = input.find("{");
            input.erase(0,spos);
            spos = input.find("{");
            epos = input.find("}");
            ++l;
        }

        for(int i = 0; i < 4; ++i){
            std::cout << m(i,0) << " " << m(i,1) << " " << m(i,2) << " " << m(i,3) << std::endl;
        }
        return true;
    }

    bool EditionWidget::applyDirect()
    {
        std::cout << "Direct !" << std::endl;
        return true;
    }

}
}
