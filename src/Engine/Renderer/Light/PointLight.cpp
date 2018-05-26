#include <Engine/Renderer/Light/PointLight.hpp>

#include <Engine/Renderer/RenderTechnique/RenderParameters.hpp>
#include <QMessageBox>
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
    if(transform(0,0)!=1 || transform(0,1)!=0 || transform(0,2)!=0 ||
        transform(1,0)!=0 || transform(1,1)!=1 || transform(1,2)!=0 ||
        transform(2,0)!=0 || transform(2,1)!=0 || transform(2,2)!=1)
    {
      QMessageBox::warning(nullptr,"Warning",
        "Rotation does not affect a Point Light !");
    }

    m_position = 0.5 * Core::Math::Vector3(m_position.x()+transform(0,3)
                                          ,m_position.y()+transform(1,3)
                                          ,m_position.z()+transform(2,3)
                                          );
}

Core::Math::Transform PointLight::getTransform( Core::Container::Index roIdx ) const {
    (void) roIdx;
    auto m =Core::Math::Transform::Identity();
    return m.translate(m_position);
};

} // namespace Engine
} // namespace Ra
