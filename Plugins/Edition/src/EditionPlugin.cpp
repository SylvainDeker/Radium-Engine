#include <EditionPlugin.hpp>

#include <Engine/RadiumEngine.hpp>

#include <EditionSystem.hpp>

namespace EditionPlugin {

	EditionPluginC::~EditionPluginC() {};

	void EditionPluginC::registerPlugin(const Ra::PluginContext& context)
	{
		//Register a system here 
		EditionSystem* system = new EditionSystem;
		context.m_engine->registerSystem("EditionSystem", system);
	}

	bool EditionPluginC::doAddWidget(QString & name)
	{
		//initialize name and return true if you wish to add a widget in the toolbox
		return false;
	}

	QWidget * EditionPluginC::getWidget()
	{
		//create your widget here and return the pointer
		return nullptr;
	}

	bool EditionPluginC::doAddMenu()
	{
		//return true if you wish to add a menu
		return false;
	}

	QMenu * EditionPluginC::getMenu()
	{
		//create your menu here and return the pointer
		return nullptr;
	}

	bool EditionPluginC::doAddAction(int & nb)
	{
		nb = 0;
		return false;
	}

	QAction * EditionPluginC::getAction(int id)
	{
		return nullptr;
	}

}
