#include <TestPLGComponent.hpp>

#include <iostream>

#include <Core/Math/ColorPresets.hpp>
#include <Core/Mesh/MeshUtils.hpp>
#include <Core/Mesh/TriangleMesh.hpp>
#include <Core/Tasks/TaskQueue.hpp>

#include <Engine/Entity/Entity.hpp>
#include <Engine/Renderer/Material/Material.hpp>
#include <Engine/Renderer/Mesh/Mesh.hpp>
#include <Engine/Renderer/RenderObject/RenderObject.hpp>
#include <Engine/Renderer/RenderObject/RenderObjectManager.hpp>
#include <Engine/Renderer/RenderTechnique/RenderTechnique.hpp>
#include <Engine/Renderer/RenderTechnique/ShaderConfigFactory.hpp>

namespace TestPLGPlugin {

TestPLGComponent::TestPLGComponent( const std::string& name, Ra::Engine::Entity* entity ) :
    Ra::Engine::Component( name, entity ) {}

TestPLGComponent::~TestPLGComponent() {}

void TestPLGComponent::initialize() {}


} // namespace TestPLGPlugin
