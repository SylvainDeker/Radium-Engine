#include "EditionSystem.hpp"

#include "EditionComponent.hpp"

namespace EditionPlugin
{

	EditionSystem::EditionSystem() : Ra::Engine::System()
	{
	}

	EditionSystem::~EditionSystem()
	{
	}

	void EditionSystem::generateTasks(Ra::Core::TaskQueue* taskQueue,
		const Ra::Engine::FrameInfo& frameInfo) {
	}

} // namespace EditionPlugin
