#ifndef EDITIONPLUGIN_EDITIONCOMPONENT_HPP
#define EDITIONPLUGIN_EDITIONCOMPONENT_HPP

#include <EditionPluginMacros.hpp>

#include <Engine/Component/Component.hpp>

namespace EditionPlugin
{
    class EDITION_PLUGIN_API EditionComponent : public Ra::Engine::Component
	{
	public:
		EditionComponent(const std::string& name, Ra::Engine::Entity* entity);

		virtual ~EditionComponent();

		virtual void initialize() override;

	private:
	};

} // namespace EditionPlugin

#endif // EDITIONPLUGIN_EDITIONCOMPONENT_HPP
