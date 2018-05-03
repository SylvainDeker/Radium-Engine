#ifndef EDITIONWIDEGET_HPP_
#define EDITIONWIDEGET_HPP_

#include <QWidget>

#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>
#include <GuiBase/RaGuiBase.hpp>
#include <GuiBase/SelectionManager/SelectionManager.hpp>
#include <ui_EditionWidget.h>

namespace Ra {
namespace Gui {

class EditionWidget : public QWidget, private Ui::EditionWidget{
    Q_OBJECT

public:
    EditionWidget(QWidget* parent, Ra::GuiBase::SelectionManager* selectionManager);

    /**
     * @brief setTransform : set the transform on the selected object
     * @param tf
     * @param doUpdateInfos : if set to true (default) will update the displayed infos
     * @return false in case of failure : the object selected cannot be edited or is no supported
     */
    bool setTransform(const Core::Math::Transform &tf, bool doUpdateInfos);

    ///wrapper for setTransform
    bool setMatrix(Ra::Core::Math::Matrix4 &m);

    ///get the transform of the selected object, return false in case of failure (the object selected cannot be edited or is no supported)
    bool getTransform(Ra::Core::Math::Transform *tf);

public slots:
    ///reset the selected object by setting his transform to Identity
    void resetSelectedObject();

    ///try to apply the matrix entered in the user interface
    void applyMatrix();

    void matriceSize3();
    void onCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void useTransformMatrix();
    void updateInfos(bool doProperties);
    void onValueChanged(double);

private:
    bool applyMatrixText();
    bool applyMatrixBox();
    bool transformation();

    Ra::Gui::PickingManager* m_pickingManager;
    Ra::GuiBase::SelectionManager* m_selectionManager;
    QDoubleSpinBox* m_TabButtonDirect[16];
    QCheckBox* m_matrice3;

};
}
}

#endif //EDITIONWIDEGET_HPP_
