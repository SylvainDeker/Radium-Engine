#ifndef DUMMYPLUGIN_DUMMYSYSTEM_HPP
#define DUMMYPLUGIN_DUMMYSYSTEM_HPP

#include <Engine/System/System.hpp>

#include <DummyPlugin.hpp>

namespace DummyPlugin
{
	class  DummySystem : public Ra::Engine::System
	{
	public:
		DummySystem(DummyPluginC* plugin);
		virtual ~DummySystem();
		virtual void generateTasks(Ra::Core::TaskQueue* taskQueue,
			const Ra::Engine::FrameInfo& frameInfo);

	private:
		DummyPluginC* m_plugin;
	};

} // namespace DummyPlugin

#endif // DUMMYPLUGIN_DUMMYSYSTEM_HPP
