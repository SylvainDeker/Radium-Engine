#include <DummyComponent.hpp>

namespace DummyPlugin
{
	DummyComponent::DummyComponent(const std::string& name, Ra::Engine::Entity* entity)
		: Ra::Engine::Component(name, entity)
	{
	}

	DummyComponent::~DummyComponent()
	{
	}

	void DummyComponent::initialize()
	{
	}

} // namespace FancyMeshPlugin
