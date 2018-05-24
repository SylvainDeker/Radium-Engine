#include <Engine/Renderer/Light/PointLight.hpp>

#include <Engine/Renderer/RenderTechnique/RenderParameters.hpp>

namespace Ra {
namespace Engine {

PointLight::PointLight( Entity* entity, const std::string& name ) :
    Light( entity, Light::POINT, name ),
    m_position( 0, 0, 0 ),
    m_attenuation() {}

PointLight::~PointLight() {}

void PointLight::getRenderParameters( RenderParameters& params ) const {
    Light::getRenderParameters( params );

    params.addParameter( "light.point.position", m_position );
    params.addParameter( "light.point.attenuation.constant", m_attenuation.constant );
    params.addParameter( "light.point.attenuation.linear", m_attenuation.linear );
    params.addParameter( "light.point.attenuation.quadratic", m_attenuation.quadratic );
}

std::string PointLight::getShaderInclude() const {
    return "Point";
}

void PointLight::setTransform( Core::Container::Index roIdx, const Core::Math::Transform& transform ){
    (void) roIdx;
    m_position += 0.5 * Core::Math::Vector3(transform(0,3),transform(1,3),transform(2,3));
}

Core::Math::Transform PointLight::getTransform( Core::Container::Index roIdx ) {
    (void) roIdx;
    return Core::Math::Transform::Identity();
};

} // namespace Engine
} // namespace Ra
