#include <LightPathSystem.hpp>

#include <Core/File/FileData.hpp>
#include <Core/File/GeometryData.hpp>
#include <Core/String/StringUtils.hpp>
#include <Core/Tasks/Task.hpp>
#include <Core/Tasks/TaskQueue.hpp>

#include <Engine/Entity/Entity.hpp>
#include <Engine/FrameInfo.hpp>
#include <Engine/Managers/ComponentMessenger/ComponentMessenger.hpp>
#include <Engine/RadiumEngine.hpp>
#include <Engine/Renderer/RenderTechnique/RenderTechnique.hpp>


namespace LightPathPlugin {
    LightPathSystem::LightPathSystem() : Ra::Engine::System() {
        LOG(logINFO) << "Light Path Plugin System created.";
    }
  
    LightPathSystem::~LightPathSystem() {
        LOG(logINFO) << "Light Path Plugin System destroyed.";
    }

    void LightPathSystem::handleAssetLoading( Ra::Engine::Entity* entity,
                                          const Ra::Asset::FileData* fileData ) {
      // TODO
    }

    void LightPathSystem::generateTasks( Ra::Core::TaskQueue* taskQueue,
                                     const Ra::Engine::FrameInfo& frameInfo ) {
      // TODO, but not sure since this plugin only show light path
    }
}
