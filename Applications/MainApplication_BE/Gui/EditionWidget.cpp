#include <Gui/EditionWidget.hpp>

#include <string>
#include <vector>
#include <cstdio>
#include <locale>

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

    bool EditionWidget::setMatrix(Core::Matrix4 &m)
    {
        Ra::Core::Transform tf(m);
        return setTransform(tf);
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
            if(!applyWolfram()){
                std::cout << "error wolfram" << std::endl;
            }
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

    ///parse the text into a Matrix4 (support 3x3 and 4x4) and apply it to the selected object
    bool EditionWidget::applyWolfram()
    {
        struct lconv *locale = localeconv();
        Core::Matrix4 m = Core::Transform::Identity().matrix();
        std::string input = m_wolframEdit->toPlainText().toStdString();

        //remove all spaces
        for(size_t pos = input.find(" "); pos != std::string::npos; pos = input.find(" ")){
            input.erase(pos, 1);
        }
        //remove all returns
        for(size_t pos = input.find("\n"); pos != std::string::npos; pos = input.find("\n")){
            input.erase(pos, 1);
        }

        std::vector<std::string> toks = Ra::Core::StringUtils::splitString(input, ',');
        //deal with locale
        for(size_t i = 0; i < toks.size(); ++i){
            size_t point = toks[i].find(".");
            if( point != std::string::npos ){
                toks[i].replace(point, 1, locale->decimal_point);
            }
        }

        if( toks.size() == 9 )
        {
            std::string format = "";
            for(int i = 0; i < 9; ++i)
            {
                switch (i) {
                case 0:
                    format = "{{%f";
                    break;
                case 8:
                    format = "%f}}";
                    break;
                case 2:
                case 5:
                    format = "%f}";
                    break;
                case 3:
                case 6:
                    format = "{%f";
                    break;
                default:
                    format = "%f";
                    break;
                }
                if( std::sscanf(toks[i].c_str(), format.c_str(), &m(i/3,i%3)) != 1 )
                {
                    //failure
                    return false;
                }
            }
        } else if( toks.size() == 16 )
        {
            std::string format = "";
            for(int i = 0; i < 16; ++i)
            {
                switch (i) {
                case 0:
                    format = "{{%f";
                    break;
                case 15:
                    format = "%f}}";
                    break;
                case 3:
                case 7:
                case 11:
                    format = "%f}";
                    break;
                case 4:
                case 8:
                case 12:
                    format = "{%f";
                    break;
                default:
                    format = "%f";
                    break;
                }
                if( std::sscanf(toks[i].c_str(), format.c_str(), &m(i/4,i%4)) != 1 )
                {
                    //failure
                    return false;
                }
            }
        } else
        {
            return false;
        }

        return setMatrix(m);;
    }

    bool EditionWidget::applyDirect()
    {
        std::cout << "Direct !" << std::endl;
        return true;
    }

}
}
