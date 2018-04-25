#include "DummySystem.hpp"

#include "DummyComponent.hpp"

namespace DummyPlugin
{

	DummySystem::DummySystem(DummyPluginC* plugin) : 
		Ra::Engine::System(),
		m_plugin(plugin)
	{
	}

	DummySystem::~DummySystem()
	{
	}

	void DummySystem::generateTasks(Ra::Core::TaskQueue* taskQueue,
		const Ra::Engine::FrameInfo& frameInfo) {
		m_plugin->incrementFrameCounter();
	}

} // namespace DummyPlugin
