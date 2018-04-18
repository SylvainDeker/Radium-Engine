#include <LightPathPlugin.hpp>

#include <Engine/RadiumEngine.hpp>

#include <LightPathSystem.hpp>

namespace LightPathPlugin {

LightPathPluginC::~LightPathPluginC() {}

void LightPathPluginC::registerPlugin( const Ra::PluginContext& context ) {
    LightPathSystem* system = new LightPathSystem;
    context.m_engine->registerSystem( "LightPathSystem", system );
}

bool LightPathPluginC::doAddWidget( QString& name ) {
    return false;
}

QWidget* LightPathPluginC::getWidget() {
    return nullptr;
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
