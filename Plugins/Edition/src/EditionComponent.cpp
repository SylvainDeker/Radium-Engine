#include <EditionComponent.hpp>

namespace EditionPlugin
{
	EditionComponent::EditionComponent(const std::string& name, Ra::Engine::Entity* entity)
		: Ra::Engine::Component(name, entity)
	{
	}

	EditionComponent::~EditionComponent()
	{
	}

	void EditionComponent::initialize()
	{
	}

} // namespace FancyMeshPlugin
