#include <Gui/EditionWidget.hpp>

#include <string>
#include <vector>
#include <cstdio>
#include <locale>
#include <iostream>
#include <sstream>

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
        for( int i =0 ; i <4 ;i++){
            for ( int j = 0 ; j<4; j++){
                m_TabButtonDirect[i*4+j] = new QSpinBox(direct);
                m_directLayout->addWidget(m_TabButtonDirect[i*4+j],i+1,j,1,1);
            }
        }
        m_matrice3 = new QCheckBox(direct);
        m_matrice3->setObjectName(QStringLiteral("m_matrice3"));
        m_matrice3->setText(QApplication::translate("EditionWidget", "use matrice 3 * 3", nullptr));
        m_directLayout->addWidget(m_matrice3,0,0,1,4);
        QObject::connect(m_matrice3,SIGNAL(clicked(bool)),this,SLOT(matriceSize3()));
        QObject::connect(m_resetButton, SIGNAL(clicked()), this, SLOT(resetSelectedObject()));
        QObject::connect(m_applyButton, SIGNAL(clicked()), this, SLOT(applyMatrix()));
        QObject::connect(m_use_tranform_matrix,SIGNAL(clicked(bool)),this,SLOT(useTransformMatrix()));
        useTransformMatrix();
        QObject::connect(selectionManager, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(onCurrentChanged(QModelIndex,QModelIndex)));

    }

    void EditionWidget::onCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
    {
        Ra::Core::Transform tf;
        if(getTransform(&tf))
        {
            std::cout << "update info" << std::endl;
            Ra::Core::Matrix4 m = tf.matrix();

            std::ostringstream matrixText;
            matrixText << "{{" << m(0,0) << "," << m(0,1) << "," << m(0,2) << "," << m(0,3) << "},{"
                       << m(1,0) << "," << m(1,1) << "," << m(1,2) << "," << m(1,3) << "},{"
                       << m(2,0) << "," << m(2,1) << "," << m(2,2) << "," << m(2,3) << "},{"
                       << m(3,0) << "," << m(3,1) << "," << m(3,2) << "," << m(3,3) << "}}";
            std::cout << matrixText.str() << std::endl;
            //std::string str(matrixText.str());
            //QString qstr(str);
            m_wolframEdit->setText(QString::fromStdString(matrixText.str()));

        } else {
            std::cout << "set blank" << std::endl;
        }
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
       if (m_use_tranform_matrix->isChecked()){
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
       }else{
           transformation();

       }
    }
    void EditionWidget::matriceSize3()
    {
        const bool m_visible = !m_matrice3->isChecked();
        for( int i =0 ; i<4 ; i++)
            m_TabButtonDirect[i*4+3]->setVisible(m_visible);

        for( int i =0 ; i<4 ; i++)
            m_TabButtonDirect[12+i]->setVisible(m_visible);

    }
    void EditionWidget::useTransformMatrix(){
        const bool m_visible = !m_use_tranform_matrix->isChecked();
        m_translation_x->setEnabled(m_visible);
        m_translation_y->setEnabled(m_visible);
        m_translation_z->setEnabled(m_visible);
        m_rotation_x->setEnabled(m_visible);
        m_rotation_y->setEnabled(m_visible);
        m_rotation_z->setEnabled(m_visible);
        m_scale_x->setEnabled(m_visible);
        m_scale_y->setEnabled(m_visible);
        m_scale_z->setEnabled(m_visible);
        tabWidget->setEnabled(!m_visible);
    }

    bool EditionWidget::transformation(){
        Core::Matrix4 m = Core::Transform::Identity().matrix();
        m(0,3)=m_translation_x->value();
        m(1,3)=m_translation_y->value();
        m(2,3)=m_translation_z->value();
        m(0,0)=m_scale_x->value();
        m(1,1)=m_scale_y->value();
        m(2,2)=m_scale_z->value();
        return setMatrix(m);
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

        return setMatrix(m);
    }

    bool EditionWidget::applyDirect()
    {
        Core::Matrix4 m = Core::Transform::Identity().matrix();
        for (int i=0 ; i<4 ;i++){
            for (int j=0; j<4 ; j++){
                if (!((i==3 || j==3)&& m_matrice3->isChecked())){
                    m(i,j) = m_TabButtonDirect[i*4+j]->value();
                }
            }
        }
        return setMatrix(m);
    }

}
}
