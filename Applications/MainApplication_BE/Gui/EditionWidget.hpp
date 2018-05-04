#ifndef EDITIONPLUGIN_HPP_
#define EDITIONPLUGIN_HPP_

#include <QWidget>
#include <PluginBase/RadiumPluginInterface.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>
#include <ui_EditionWidget.h>

namespace Ra {
namespace Gui {

class EditionWidget : public QWidget{
    Q_OBJECT

public:
    EditionWidget(QWidget* parent, Ra::GuiBase::SelectionManager* selectionManager);

    ///set the transform on the selected object, return false in case of failure
    bool setTransform(Ra::Core::Transform &tf);
    Ra::Core::Transform* getTransform();

public slots:
    void resetSelectedObject();
    void applyMatrix(Ra::Core::Matrix4 &m);

private:
    Ra::Gui::PickingManager* m_pickingManager;
    Ra::GuiBase::SelectionManager* m_selectionManager;

};
}
}

#endif //EDITIONPLUGIN_HPP_
