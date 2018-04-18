#ifndef LIGHTPATHPLUGIN_HPP_
#define LIGHTPATHPLUGIN_HPP_

#include <QAction>
#include <QObject>
#include <QtPlugin>

#include <PluginBase/RadiumPluginInterface.hpp>

#include <LightPathPluginMacros.hpp>

namespace Ra {
namespace Engine {
class RadiumEngine;
}
} // namespace Ra

namespace LightPathPlugin {
class LightPathPluginC : public QObject, Ra::Plugins::RadiumPluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "RadiumEngine.PluginInterface" )
    Q_INTERFACES( Ra::Plugins::RadiumPluginInterface )

  public:
    virtual ~LightPathPluginC();

    void registerPlugin( const Ra::PluginContext& context ) override;

    bool doAddWidget( QString& name ) override;
    QWidget* getWidget() override;

    bool doAddMenu() override;
    QMenu* getMenu() override;

    bool doAddAction( int& nb ) override;
    QAction* getAction( int id ) override;
};

} // namespace LightPathPlugin

#endif // LIGHTPATHPLUGIN_HPP_
