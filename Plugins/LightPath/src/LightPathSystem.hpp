#ifndef LIGHTPATHPLUGIN_LIGHTPATHSYSTEM_HPP
#define LIGHTPATHPLUGIN_LIGHTPATHSYSTEM_HPP

#include <LightPathPluginMacros.hpp>

#include <Engine/System/System.hpp>

namespace Ra {
namespace Core {
struct TriangleMesh;
}
} // namespace Ra

namespace Ra {
namespace Engine {
class Entity;
struct RenderTechnique;
class Component;
} // namespace Engine
} // namespace Ra

namespace LightPathPlugin {
    class LP_PLUGIN_API LightPathSystem : public Ra::Engine::System {
    public:
        LightPathSystem();
        virtual ~LightPathSystem();

        void handleAssetLoading( Ra::Engine::Entity* entity,
                                 const Ra::Asset::FileData* fileData ) override;
    
        void generateTasks( Ra::Core::TaskQueue* taskQueue,
                            const Ra::Engine::FrameInfo& frameInfo ) override;
    
    };
} // namespace LightPathPlugin

#endif // LIGHTPATHPLUGIN_LIGHTPATHSYSTEM_HPP
