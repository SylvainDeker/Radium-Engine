#include <LightPathPlugin.hpp>
#include <Engine/RadiumEngine.hpp>
#include <LightPathSystem.hpp>
#include <LightPathUI.hpp>

namespace LightPathPlugin {

  LightPathPluginC::LightPathPluginC(): l_system (nullptr),
                                        l_widget (nullptr) {}
  
  LightPathPluginC::~LightPathPluginC() {}

  void LightPathPluginC::registerPlugin( const Ra::PluginContext& context ) {
    delete (l_system);
    l_system = new LightPathSystem;
    context.m_engine->registerSystem( "LightPathSystem", l_system );
  }

  bool LightPathPluginC::doAddWidget( QString& name ) {
    delete (l_widget);
    l_widget = new LightPathUI();
    name = "Light Path";
    return true;
  }

  QWidget* LightPathPluginC::getWidget() {
    return l_widget;
  }

  bool LightPathPluginC::doAddMenu() {
    return false;
  }

  QMenu* LightPathPluginC::getMenu() {
    return nullptr;
  }

  bool LightPathPluginC::doAddAction( int& nb ) {
    nb = 0;
    return false;
  }

  QAction* LightPathPluginC::getAction( int id ) {
    return nullptr;
  }

} // namespace LightPathPlugin
