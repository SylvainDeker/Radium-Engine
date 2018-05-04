#ifndef EDITIONWIDEGET_HPP_
#define EDITIONWIDEGET_HPP_

#include <QWidget>
#include <PluginBase/RadiumPluginInterface.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>
#include <ui_EditionWidget.h>

namespace Ra {
namespace Gui {

class EditionWidget : public QWidget, private Ui::EditionWidget{
    Q_OBJECT

public:
    EditionWidget(QWidget* parent, Ra::GuiBase::SelectionManager* selectionManager);

    ///set the transform on the selected object, return false in case of failure
    bool setTransform(Ra::Core::Transform &tf);

    ///get the transform of the selected object, return false in case of failure
    bool getTransform(Ra::Core::Transform *tf);

public slots:
    void resetSelectedObject();
    void applyMatrix();

private:
    bool applyWolfram();
    bool applyDirect();

    Ra::Gui::PickingManager* m_pickingManager;
    Ra::GuiBase::SelectionManager* m_selectionManager;

};
}
}

#endif //EDITIONWIDEGET_HPP_
