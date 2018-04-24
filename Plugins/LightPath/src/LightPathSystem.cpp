#include <LightPathSystem.hpp>

#include <Engine/RadiumEngine.hpp>

namespace LightPathPlugin {
  LightPathSystem::LightPathSystem() : Ra::Engine::System() {
    // LOG( logINFO ) << "Light Path Plugin System created.";
  }
  
  LightPathSystem::~LightPathSystem() {
    // LOG( logINFO ) << "Light Path Plugin System destroyed.";
  }

  void LightPathSystem::handleAssetLoading( Ra::Engine::Entity* entity,
                                            const Ra::Asset::FileData* fileData ) {
    // TODO
    
  }
  
  void LightPathSystem::generateTasks( Ra::Core::TaskQueue* taskQueue,
                                       const Ra::Engine::FrameInfo& frameInfo ) {
    // TODO, but not sure since this plugin only show light path
  }
  
} // namespace LightPathPLugin


