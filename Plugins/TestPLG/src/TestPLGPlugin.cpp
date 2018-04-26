#include <TestPLGPlugin.hpp>

#include <QAction>
#include <QIcon>
#include <QToolBar>

#include <Engine/Entity/Entity.hpp>
#include <Engine/Managers/EntityManager/EntityManager.hpp>
#include <Engine/Managers/SignalManager/SignalManager.hpp>
#include <Engine/Managers/SystemDisplay/SystemDisplay.hpp>
#include <Engine/RadiumEngine.hpp>
#include <Engine/Renderer/RenderObject/RenderObject.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>

#include <GuiBase/SelectionManager/SelectionManager.hpp>
#include <GuiBase/Utils/PickingManager.hpp>

#include "UI/TestPLGui.hpp"
#include <TestPLGSystem.hpp>

namespace TestPLGPlugin {

TestPLGPluginC::TestPLGPluginC() :
    m_selectionManager( nullptr ),
    m_PickingManager( nullptr ),
    m_system( nullptr ),
    // m_paintColor( Ra::Core::Color( 1.0, 0.0, 0.0, 1.0 ) ),
    m_isPainting( false ) {
    m_widget = new TestPLGui();
}

TestPLGPluginC::~TestPLGPluginC() {}

void TestPLGPluginC::registerPlugin( const Ra::PluginContext& context ) {
    // register selection context
    m_selectionManager = context.m_selectionManager;
    m_PickingManager = context.m_pickingManager;
    m_system = new TestPLGSystem;
    context.m_engine->registerSystem( "TestPLGSystem", m_system );
    connect( m_selectionManager, &Ra::GuiBase::SelectionManager::currentChanged, this,
             &TestPLGPluginC::onCurrentChanged );
}

bool TestPLGPluginC::doAddWidget( QString& name ) {
    name = "TestPLG";
    return true;
}

QWidget* TestPLGPluginC::getWidget() {
    return m_widget;
}

bool TestPLGPluginC::doAddMenu() {
    return false;
}

QMenu* TestPLGPluginC::getMenu() {
    return nullptr;
}

bool TestPLGPluginC::doAddAction( int& nb ) {
    nb = 0;
    return false;
}

QAction* TestPLGPluginC::getAction( int id ) {
    return nullptr;
}

void TestPLGPluginC::activePaintColor( bool on ) {
    m_isPainting = on;
    m_system->startPaintMesh( on );
}

void TestPLGPluginC::changePaintColor( const QColor& color ) {
    m_paintColor = Ra::Core::Color( Scalar( color.red() ) / 255, Scalar( color.green() ) / 255,
                                    Scalar( color.blue() ) / 255, 1.0 );
}

void TestPLGPluginC::onCurrentChanged( const QModelIndex& current, const QModelIndex& prev ) {
    if ( m_isPainting && Ra::Core::Index::Invalid() != m_selectionManager->currentItem().m_roIndex )
    {
        m_system->paintMesh( m_PickingManager->getCurrent(), m_paintColor );
    }
}

} // namespace TestPLGPlugin
