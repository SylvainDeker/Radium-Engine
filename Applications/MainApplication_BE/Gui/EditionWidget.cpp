#include <Gui/EditionWidget.hpp>

#include <string>
#include <vector>
#include <cstdio>
#include <locale>
#include <iostream>
#include <sstream>
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

#define SET_VALUE_NO_SIGNALS(obj,value) (obj)->blockSignals(true);\
                                        (obj)->setValue(value);\
                                        (obj)->blockSignals(false);

namespace Ra{
namespace Gui{

    EditionWidget::EditionWidget(QWidget *parent, Ra::GuiBase::SelectionManager* selectionManager) :
        QWidget(parent),
        m_selectionManager(selectionManager)
    {
        setupUi(this);
        for( int i =0 ; i <16 ;++i){
            m_TabButtonDirect[i] = new QDoubleSpinBox(matrixBox);
            m_TabButtonDirect[i]->setDecimals(5);
            m_TabButtonDirect[i]->setMaximum(std::numeric_limits<float>::max());
            m_TabButtonDirect[i]->setMinimum(-std::numeric_limits<float>::max());
            m_matrixBoxLayout->addWidget(m_TabButtonDirect[i],(i/4)+1,(i%4),1,1);
        }
        //TODO find limits of radium
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
        m_scale_x->setMinimum(std::numeric_limits<float>::min());
        m_scale_y->setMaximum(std::numeric_limits<float>::max());
        m_scale_y->setMinimum(std::numeric_limits<float>::min());
        m_scale_z->setMaximum(std::numeric_limits<float>::max());
        m_scale_z->setMinimum(std::numeric_limits<float>::min());
        QObject::connect(m_rotation_x, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
        QObject::connect(m_rotation_y, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
        QObject::connect(m_rotation_z, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
        QObject::connect(m_translation_x, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
        QObject::connect(m_translation_y, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
        QObject::connect(m_translation_z, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
        QObject::connect(m_scale_x, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
        QObject::connect(m_scale_y, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));
        QObject::connect(m_scale_z, SIGNAL(valueChanged(double)), this, SLOT(onValueChanged(double)));

        m_matrice3 = new QCheckBox(matrixBox);
        m_matrice3->setObjectName(QStringLiteral("m_matrice3"));
        m_matrice3->setText(QApplication::translate("EditionWidget", "use matrice 3 * 3", nullptr));
        m_matrixBoxLayout->addWidget(m_matrice3,0,0,1,4);
        QObject::connect(m_matrice3,SIGNAL(clicked(bool)),this,SLOT(matriceSize3()));
        QObject::connect(m_resetButton, SIGNAL(clicked()), this, SLOT(resetSelectedObject()));
        QObject::connect(m_applyButton, SIGNAL(clicked()), this, SLOT(applyMatrix()));
        QObject::connect(m_use_tranform_matrix,SIGNAL(clicked(bool)),this,SLOT(useTransformMatrix()));
        useTransformMatrix();
        QObject::connect(selectionManager, SIGNAL(currentChanged(QModelIndex,QModelIndex)), this, SLOT(onCurrentChanged(QModelIndex,QModelIndex)));

    }

    void EditionWidget::updateInfos(bool doProperties=true)
    {
        Ra::Core::Transform tf;
        if(getTransform(&tf))
        {
            setEnabled(true);
            Ra::Core::Matrix4 m = tf.matrix();
            Ra::Core::Matrix3 r = tf.rotation();
            Ra::Core::Vector3 angles = r.eulerAngles(0,1,2);

            if(doProperties)
            {
                //let's hope there's no negative scaling
                Ra::Core::Vector3 v(m(0,0), m(1,0), m(2,0));
                SET_VALUE_NO_SIGNALS(m_scale_x, v.norm());
                v = Ra::Core::Vector3(m(0,1), m(1,1), m(2,1));
                SET_VALUE_NO_SIGNALS(m_scale_y, v.norm());
                v = Ra::Core::Vector3(m(0,2), m(1,2), m(2,2));
                SET_VALUE_NO_SIGNALS(m_scale_z, v.norm());
                SET_VALUE_NO_SIGNALS(m_translation_x, m(0,3));
                SET_VALUE_NO_SIGNALS(m_translation_y, m(1,3));
                SET_VALUE_NO_SIGNALS(m_translation_z, m(2,3));
                SET_VALUE_NO_SIGNALS(m_rotation_x, Ra::Core::Math::toDegrees(angles(0)));
                SET_VALUE_NO_SIGNALS(m_rotation_y, Ra::Core::Math::toDegrees(angles(1)));
                SET_VALUE_NO_SIGNALS(m_rotation_z, Ra::Core::Math::toDegrees(angles(2)));
            }

            std::ostringstream matrixText;
            matrixText << "{\n{" << m(0,0) << "," << m(0,1) << "," << m(0,2) << "," << m(0,3) << "},\n{"
                       << m(1,0) << "," << m(1,1) << "," << m(1,2) << "," << m(1,3) << "},\n{"
                       << m(2,0) << "," << m(2,1) << "," << m(2,2) << "," << m(2,3) << "},\n{"
                       << m(3,0) << "," << m(3,1) << "," << m(3,2) << "," << m(3,3) << "}\n}";
            m_matrixTextEdit->setText(QString::fromStdString(matrixText.str()));

            for(int i = 0; i < 16; ++i)
            {
                m_TabButtonDirect[i]->setValue(m(i/4,i%4));
            }

        } else {
            //nothing to display
            SET_VALUE_NO_SIGNALS(m_translation_x, 0);
            SET_VALUE_NO_SIGNALS(m_translation_y, 0);
            SET_VALUE_NO_SIGNALS(m_translation_z, 0);
            SET_VALUE_NO_SIGNALS(m_scale_x, 0);
            SET_VALUE_NO_SIGNALS(m_scale_y, 0);
            SET_VALUE_NO_SIGNALS(m_scale_z, 0);
            SET_VALUE_NO_SIGNALS(m_rotation_x, 0);
            SET_VALUE_NO_SIGNALS(m_rotation_y, 0);
            SET_VALUE_NO_SIGNALS(m_rotation_z, 0);
            m_matrixTextEdit->setText("");
            for(int i = 0; i < 16; ++i)
            {
                m_TabButtonDirect[i]->setValue(0);
            }
            setEnabled(false);
        }
    }

    void EditionWidget::onCurrentChanged(const QModelIndex &current, const QModelIndex &previous)
    {
        updateInfos();
    }

    bool EditionWidget::setTransform(const Ra::Core::Transform& tf, bool doUpdateInfos=true)
    {
        Ra::Engine::ItemEntry item = m_selectionManager->currentItem();

        if(item.isValid())
        {
            //Entity
            if (item.isEntityNode())
            {
                item.m_entity->setTransform(tf);
                item.m_entity->swapTransformBuffers();
                if(doUpdateInfos){
                    updateInfos();
                }
                return true;
            }

            //no action if the item is only a component

            //Render Object
            /* desactivated as it may cause problem if a non inversible matrix is passed
            if (item.isRoNode() && item.m_component->canEdit(item.m_roIndex))
            {
                item.m_component->setTransform(item.m_roIndex, tf);
                if(doUpdateInfos){
                    updateInfos();
                }
                return true;
            }
            */
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

            /* desactivated, see setTransform
            if (item.isRoNode() && item.m_component->canEdit(item.m_roIndex))
            {
                *tf = item.m_component->getTransform(item.m_roIndex);
                return true;
            }
            */
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
                if(!applyMatrixText()){
                    //TODO more visible error
                    LOG(logINFO) << "Cannot apply matrix : bad format or non-editable object.";
                }
                break;
            case 1 :
                if(!applyMatrixBox()){
                    //TODO more visible error
                    LOG(logINFO) << "Cannot apply matrix : bad format or non-editable object.";
                }
                break;
            default :
                break;
            }
       } else {
           transformation();
       }
    }
    void EditionWidget::matriceSize3()
    {
        const bool m_visible = !m_matrice3->isChecked();
        for( int i =0 ; i<4 ; i++)
        {
            m_TabButtonDirect[i*4+3]->setVisible(m_visible);
            m_TabButtonDirect[12+i]->setVisible(m_visible);
        }

    }
    void EditionWidget::useTransformMatrix(){
        const bool visible = !m_use_tranform_matrix->isChecked();
        m_translation_x->setEnabled(visible);
        m_translation_y->setEnabled(visible);
        m_translation_z->setEnabled(visible);
        m_rotation_x->setEnabled(visible);
        m_rotation_y->setEnabled(visible);
        m_rotation_z->setEnabled(visible);
        m_scale_x->setEnabled(visible);
        m_scale_y->setEnabled(visible);
        m_scale_z->setEnabled(visible);
        tabWidget->setEnabled(!visible);
        //m_applyButton->setEnabled(!visible);
        //m_undoButton->setEnabled(!visible);
    }

    bool EditionWidget::transformation(){
        Core::Transform tf = Core::Transform::Identity();
        //scale, then rotation, and finally translation (inverted because matrix multiplication)
        tf.translate(Core::Vector3(m_translation_x->value(), m_translation_y->value(), m_translation_z->value()));
        tf.rotate(Eigen::AngleAxisf(Ra::Core::Math::toRadians(m_rotation_x->value()), Eigen::Vector3f::UnitX()));
        tf.rotate(Eigen::AngleAxisf(Ra::Core::Math::toRadians(m_rotation_y->value()), Eigen::Vector3f::UnitY()));
        tf.rotate(Eigen::AngleAxisf(Ra::Core::Math::toRadians(m_rotation_z->value()), Eigen::Vector3f::UnitZ()));
        tf.scale(Core::Vector3(m_scale_x->value(), m_scale_y->value(), m_scale_z->value()));
        bool ret = setTransform(tf, false);
        updateInfos(false);
        return ret;
    }

    ///parse the text into a Matrix4 (support 3x3 and 4x4) and apply it to the selected object
    bool EditionWidget::applyMatrixText()
    {
        struct lconv *locale = localeconv();
        Core::Matrix4 m = Core::Transform::Identity().matrix();
        std::string input = m_matrixTextEdit->toPlainText().toStdString();

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

    bool EditionWidget::applyMatrixBox()
    {
        Core::Matrix4 m = Core::Transform::Identity().matrix();
        for (int i=0 ; i<4 ;i++){
            for (int j=0; j<4 ; j++){
                m(i,j) = m_TabButtonDirect[i*4+j]->value();
            }
        }
        return setMatrix(m);
    }

    void EditionWidget::onValueChanged(double)
    {
        transformation();
    }

}
}
