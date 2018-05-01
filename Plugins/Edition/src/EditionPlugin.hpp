#ifndef EDITIONPLUGIN_HPP_
#define EDITIONPLUGIN_HPP_

#include <PluginBase/RadiumPluginInterface.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>

namespace EditionPlugin {
// Due to an ambigous name while compiling with Clang, must differentiate plugin class from plugin
// namespace
class EditionPluginC : public QObject, Ra::Plugins::RadiumPluginInterface {
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "RadiumEngine.PluginInterface")
	Q_INTERFACES(Ra::Plugins::RadiumPluginInterface)

public:
	virtual ~EditionPluginC();

	void registerPlugin(const Ra::PluginContext& context) override;

	virtual bool doAddWidget(QString& name) override;
	virtual QWidget* getWidget() override;

	virtual bool doAddMenu() override;
	virtual QMenu* getMenu() override;

	virtual bool doAddAction(int& nb) override;
	virtual QAction* getAction(int id) override;

public slots:
    void resetSelectedRO();

private:
    Ra::Gui::PickingManager* m_pickingManager;
    Ra::GuiBase::SelectionManager* m_selectionManager;

};
}

#endif //EDITIONPLUGIN_HPP_

