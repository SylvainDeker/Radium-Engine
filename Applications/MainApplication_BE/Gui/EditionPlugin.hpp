#ifndef EDITIONPLUGIN_HPP_
#define EDITIONPLUGIN_HPP_

#include <PluginBase/RadiumPluginInterface.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>

namespace EditionPlugin {
// Due to an ambigous name while compiling with Clang, must differentiate plugin class from plugin
// namespace
class EditionPluginC : public Qwidget{
    Q_OBJECT

public:
    EditionPluginC(QWidget* parent = nullptr);
     ~EditionPluginC();

public slots:
    void resetSelectedEntity();

private:
    Ra::Gui::PickingManager* m_pickingManager;
    Ra::GuiBase::SelectionManager* m_selectionManager;

};
}

#endif //EDITIONPLUGIN_HPP_

