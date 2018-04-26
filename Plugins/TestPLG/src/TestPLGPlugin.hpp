#ifndef TestPLGPLUGIN_HPP_
#define TestPLGPLUGIN_HPP_

#include <Core/CoreMacros.hpp>
#include <PluginBase/RadiumPluginInterface.hpp>
#include <TestPLGPluginMacros.hpp>
#include <UI/TestPLGui.hpp>
#include <QAction>
#include <QColor>
#include <QObject>
#include <QtPlugin>
#include <QPushButton>
#include <QFrame>


#include <GuiBase/Utils/PickingManager.hpp>

namespace Ra {
namespace Engine {
class RadiumEngine;
class Entity;
} // namespace Engine
} // namespace Ra

namespace TestPLGPlugin {
class TestPLGComponent;

// Due to an ambigous name while compiling with Clang, must differentiate plugin class from plugin
// namespace
class TestPLGPluginC : public QObject, Ra::Plugins::RadiumPluginInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA( IID "RadiumEngine.PluginInterface" )
    Q_INTERFACES( Ra::Plugins::RadiumPluginInterface )

  public:
    TestPLGPluginC();
    virtual ~TestPLGPluginC();

    virtual void registerPlugin( const Ra::PluginContext& context ) override;

    virtual bool doAddWidget( QString& name ) override;
    virtual QWidget* getWidget() override;

    virtual bool doAddMenu() override;
    virtual QMenu* getMenu() override;

    virtual bool doAddAction( int& nb ) override;
    virtual QAction* getAction( int id ) override;

  public slots:
    void onCurrentChanged( const QModelIndex& current, const QModelIndex& prev );
    void activePaintColor( bool on );
    void changePaintColor( const QColor& color );

  private:
    TestPLGui * m_widget;

    Ra::GuiBase::SelectionManager* m_selectionManager;
    Ra::Gui::PickingManager* m_PickingManager;

    class TestPLGSystem* m_system;

    Ra::Core::Color m_paintColor;
    bool m_isPainting;
};

} // namespace TestPLGPlugin

#endif // TestPLGPLUGIN_HPP_
