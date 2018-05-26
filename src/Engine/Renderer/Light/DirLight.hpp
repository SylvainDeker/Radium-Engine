#ifndef RADIUMENGINE_DIRLIGHT_HPP
#define RADIUMENGINE_DIRLIGHT_HPP

#include <Engine/RaEngine.hpp>
#include <Engine/Renderer/Light/Light.hpp>

namespace Ra {
namespace Engine {

class RA_ENGINE_API DirectionalLight final : public Light {
  public:
    RA_CORE_ALIGNED_NEW

    DirectionalLight( Entity* entity, const std::string& name = "dirlight" );
    ~DirectionalLight();

    void getRenderParameters( RenderParameters& params ) const override;

    void setDirection( const Core::Math::Vector3& pos ) override;
    inline const Core::Math::Vector3& getDirection() const;

    std::string getShaderInclude() const;

    /*!
       \brief Redefinition from Component to manipulate lights with Gizmos
       \param Core::Container::Index roIdx Useless here
       \param const Core::Math::Transform& transform the transformation
       \return void
    */

    void setTransform( Core::Container::Index roIdx, const Core::Math::Transform& transform ) override;

    /*!
       \brief Redefinition from Component to update Gizmos position when you use them on light
       \return void
    */
    Ra::Core::Math::Transform getTransform( Core::Container::Index roIdx ) const override;

  private:
    Core::Math::Vector3 m_direction;
};

} // namespace Engine
} // namespace Ra

#include <Engine/Renderer/Light/DirLight.inl>

#endif // RADIUMENGINE_POINTLIGHT_HPP
