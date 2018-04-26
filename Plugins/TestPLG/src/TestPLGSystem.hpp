#ifndef TestPLGPLUGIN_TestPLGSYSTEM_HPP
#define TestPLGPLUGIN_TestPLGSYSTEM_HPP

#include <TestPLGPluginMacros.hpp>

#include <Engine/Renderer/Renderer.hpp>
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

namespace TestPLGPlugin {
class TestPLGComponent;
}

namespace TestPLGPlugin {
class MESH_PAINT_PLUGIN_API TestPLGSystem : public Ra::Engine::System {
  public:
    TestPLGSystem();
    virtual ~TestPLGSystem();

    virtual void handleAssetLoading( Ra::Engine::Entity* entity,
                                     const Ra::Asset::FileData* fileData ) override;

    virtual void generateTasks( Ra::Core::TaskQueue* taskQueue,
                                const Ra::Engine::FrameInfo& frameInfo ) override;

    void startPaintMesh( bool start );

    void paintMesh( const Ra::Engine::Renderer::PickingResult& picking,
                    const Ra::Core::Color& color );
};

} // namespace TestPLGPlugin

#endif // TestPLGPLUGIN_TestPLGSYSTEM_HPP
