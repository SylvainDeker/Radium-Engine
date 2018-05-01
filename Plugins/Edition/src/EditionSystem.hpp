#ifndef EDITIONPLUGIN_EDITIONSYSTEM_HPP
#define EDITIONPLUGIN_EDITIONSYSTEM_HPP

#include <Engine/System/System.hpp>

namespace EditionPlugin
{
	class  EditionSystem : public Ra::Engine::System
	{
	public:
		EditionSystem();
		virtual ~EditionSystem();
		virtual void generateTasks(Ra::Core::TaskQueue* taskQueue,
			const Ra::Engine::FrameInfo& frameInfo);

	private:
	};

} // namespace EditionPlugin

#endif // EDITIONPLUGIN_EDITIONSYSTEM_HPP
