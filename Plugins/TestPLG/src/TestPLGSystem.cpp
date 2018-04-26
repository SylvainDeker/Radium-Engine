#include <TestPLGSystem.hpp>

#include <Core/Asset/FileData.hpp>
#include <Core/Asset/GeometryData.hpp>
#include <Core/String/StringUtils.hpp>
#include <Core/Tasks/Task.hpp>
#include <Core/Tasks/TaskQueue.hpp>

#include <Engine/Entity/Entity.hpp>
#include <Engine/FrameInfo.hpp>
#include <Engine/Managers/ComponentMessenger/ComponentMessenger.hpp>
#include <Engine/RadiumEngine.hpp>
#include <Engine/Renderer/RenderTechnique/RenderTechnique.hpp>

#include <TestPLGComponent.hpp>

namespace TestPLGPlugin {
TestPLGSystem::TestPLGSystem() : Ra::Engine::System() {}

TestPLGSystem::~TestPLGSystem() {}

void TestPLGSystem::handleAssetLoading( Ra::Engine::Entity* entity,
                                          const Ra::Asset::FileData* fileData ) {
                                            /*
    auto geomData = fileData->getGeometryData();

    uint id = 0;

    for ( const auto& data : geomData )
    {
        std::string componentName = "MP_" + entity->getName() + std::to_string( id++ );
        TestPLGComponent* comp = new TestPLGComponent( componentName, entity );
        // comp->setDataId( data->getName() );
        registerComponent( entity, comp );
    }
    */
}

void TestPLGSystem::generateTasks( Ra::Core::TaskQueue* taskQueue,
                                     const Ra::Engine::FrameInfo& frameInfo ) {
    // Do nothing, as this system only displays painted meshes.
}

void TestPLGSystem::startPaintMesh( bool start ) {
    // switch rendered mesh
    /*
    for ( auto& compEntry : this->m_components )
    {
        auto MPcomp = static_cast<TestPLGComponent*>( compEntry.second );
        MPcomp->startPaint( start );
    }
    */
}

void TestPLGSystem::paintMesh( const Ra::Engine::Renderer::PickingResult& picking,const Ra::Core::Color& color ) {

  /*
    for ( auto& compEntry : this->m_components )
    {
        auto MPcomp = static_cast<TestPLGComponent*>( compEntry.second );
        MPcomp->paintMesh( picking, color );
    }
    */
}

} // namespace TestPLGPlugin
