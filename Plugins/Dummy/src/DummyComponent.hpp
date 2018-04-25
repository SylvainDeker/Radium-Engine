#ifndef DUMMYPLUGIN_DUMMYCOMPONENT_HPP
#define DUMMYPLUGIN_DUMMYCOMPONENT_HPP

#include <Engine/Component/Component.hpp>

namespace DummyPlugin
{
	class DummyComponent : public Ra::Engine::Component
	{
	public:
		DummyComponent(const std::string& name, Ra::Engine::Entity* entity);

		virtual ~DummyComponent();

		virtual void initialize() override;

	private:
	};

} // namespace DummyPlugin

#endif // DUMMYPLUGIN_DUMMYCOMPONENT_HPP
