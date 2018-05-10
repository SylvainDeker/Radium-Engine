#include <Gui/EditionWidget.hpp>

#include <string>
#include <vector>
#include <cstdio>
#include <locale>
#include <iostream>
#include <sstream>
#include <cmath>
#include <limits>

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
                m_TabButtonDirect[i*4+j] = new QDoubleSpinBox(direct);
                m_TabButtonDirect[i*4+j]->setDecimals(10);
                m_TabButtonDirect[i*4+j]->setMaximum(std::numeric_limits<float>::max());
                m_TabButtonDirect[i*4+j]->setMinimum(-std::numeric_limits<float>::max());
                m_directLayout->addWidget(m_TabButtonDirect[i*4+j],i+1,j,1,1);
            }
        }
        //I hate qt designer
        m_rotation_x->setMaximum(std::numeric_limits<float>::max());
        m_rotation_x->setMinimum(-std::numeric_limits<float>::max());
        m_rotation_y->setMaximum(std::numeric_limits<float>::max());
        m_rotation_y->setMinimum(-std::numeric_limits<float>::max());
        m_rotation_z->setMaximum(std::numeric_limits<float>::max());
        m_rotation_z->setMinimum(-std::numeric_limits<float>::max());
        m_translation_x->setMaximum(std::numeric_limits<float>::max());
        m_translation_x->setMinimum(-std::numeric_limits<float>::max());
        m_translation_y->setMaximum(std::numeric_limits<float>::max());
        m_translation_y->setMinimum(-std::numeric_limits<float>::max());
        m_translation_z->setMaximum(std::numeric_limits<float>::max());
        m_translation_z->setMinimum(-std::numeric_limits<float>::max());
        m_scale_x->setMaximum(std::numeric_limits<float>::max());
        m_scale_x->setMinimum(-std::numeric_limits<float>::max());
        m_scale_y->setMaximum(std::numeric_limits<float>::max());
        m_scale_y->setMinimum(-std::numeric_limits<float>::max());
        m_scale_z->setMaximum(std::numeric_limits<float>::max());
        m_scale_z->setMinimum(-std::numeric_limits<float>::max());

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

    void EditionWidget::updateInfos()
    {
        Ra::Core::Transform tf;
        if(getTransform(&tf))
        {
            std::cout << "update infos" << std::endl;
            Ra::Core::Matrix4 m = tf.matrix();
            Ra::Core::Matrix3 r = tf.rotation();

            m_translation_x->setValue(m(0,3));
            m_translation_y->setValue(m(1,3));
            m_translation_z->setValue(m(2,3));
            //TODO maybe broken
            m_scale_x->setValue(m(0,0)/r(0,0));
            m_scale_y->setValue(m(1,1)/r(1,1));
            m_scale_z->setValue(m(2,2)/r(2,2));
            //see decomposition of r matrix
            m_rotation_x->setValue(std::atan2(r(2,1), r(2,2))/M_DEGREE_TO_RADIAN);
            m_rotation_y->setValue(std::atan2(-r(2,0), std::sqrt(r(2,1)*r(2,1)+r(2,2)*r(2,2)))/M_DEGREE_TO_RADIAN);
            m_rotation_z->setValue(std::atan2(r(1,0), r(0,0))/M_DEGREE_TO_RADIAN);

            std::ostringstream matrixText;
            matrixText << "{\n{" << m(0,0) << "," << m(0,1) << "," << m(0,2) << "," << m(0,3) << "},\n{"
                       << m(1,0) << "," << m(1,1) << "," << m(1,2) << "," << m(1,3) << "},\n{"
                       << m(2,0) << "," << m(2,1) << "," << m(2,2) << "," << m(2,3) << "},\n{"
                       << m(3,0) << "," << m(3,1) << "," << m(3,2) << "," << m(3,3) << "}\n}";
            m_wolframEdit->setText(QString::fromStdString(matrixText.str()));

            for(int i = 0; i < 16; ++i)
            {
                m_TabButtonDirect[i]->setValue(m(i/4,i%4));
            }

        } else {
            std::cout << "set blank" << std::endl;
        }
    }

    void EditionWidget::onCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
    {
        updateInfos();
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
                updateInfos();
                return true;
            }

            //no action if the item is only a component

            if (item.isRoNode() && item.m_component->canEdit(item.m_roIndex))
            {
                item.m_component->setTransform(item.m_roIndex, tf);
                updateInfos();
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
        Core::Transform tf = Core::Transform::Identity();
        //scale, then rotation, and finally translation (inverted because matrix multiplication)
        tf.translate(Core::Vector3(m_translation_x->value(), m_translation_y->value(), m_translation_z->value()));
        tf.rotate(Eigen::AngleAxisf(m_rotation_x->value()*M_DEGREE_TO_RADIAN, Eigen::Vector3f::UnitX()));
        tf.rotate(Eigen::AngleAxisf(m_rotation_y->value()*M_DEGREE_TO_RADIAN, Eigen::Vector3f::UnitY()));
        tf.rotate(Eigen::AngleAxisf(m_rotation_z->value()*M_DEGREE_TO_RADIAN, Eigen::Vector3f::UnitZ()));
        tf.scale(Core::Vector3(m_scale_x->value(), m_scale_y->value(), m_scale_z->value()));
        return setTransform(tf);
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
                m(i,j) = m_TabButtonDirect[i*4+j]->value();
            }
        }
        return setMatrix(m);
    }

}
}
