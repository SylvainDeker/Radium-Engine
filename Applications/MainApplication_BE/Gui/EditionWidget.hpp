#ifndef EDITIONPLUGIN_HPP_
#define EDITIONPLUGIN_HPP_

#include <QWidget>
#include <PluginBase/RadiumPluginInterface.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>
#include <ui_EditionWidget.h>

namespace Ra {
namespace Gui {
// Due to an ambigous name while compiling with Clang, must differentiate plugin class from plugin
// namespace
class EditionWidget : public QWidget , private Ui::EditionWidget{
    Q_OBJECT

public:
    EditionWidget(QWidget* parent, Ra::GuiBase::SelectionManager* selectionManager);

public slots:
    void resetSelectedEntity();

private:
    Ra::Gui::PickingManager* m_pickingManager;
    Ra::GuiBase::SelectionManager* m_selectionManager;

};
}
}

#endif //EDITIONPLUGIN_HPP_