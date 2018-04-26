#ifndef TestPLGPLUGIN_TestPLGCOMPONENT_HPP
#define TestPLGPLUGIN_TestPLGCOMPONENT_HPP

#include <TestPLGPluginMacros.hpp>

#include <Core/Mesh/TriangleMesh.hpp>

#include <Engine/Component/Component.hpp>
#include <Engine/Managers/ComponentMessenger/ComponentMessenger.hpp>
#include <Engine/Renderer/RenderObject/RenderObject.hpp>
#include <Engine/Renderer/Renderer.hpp>

namespace Ra {
namespace Core {
class TaskQueue;
struct TaskParams;
} // namespace Core
namespace Engine {
struct FrameInfo;
}
} // namespace Ra

namespace TestPLGPlugin {

class MESH_PAINT_PLUGIN_API TestPLGComponent : public Ra::Engine::Component {
  public:
    TestPLGComponent( const std::string& name, Ra::Engine::Entity* entity );
    virtual ~TestPLGComponent();

    virtual void initialize() override;

  protected:

};

} // namespace TestPLGPlugin

#endif
