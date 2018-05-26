#include <Engine/Renderer/Light/SpotLight.hpp>

#include <Engine/Renderer/RenderTechnique/RenderParameters.hpp>

namespace Ra {
namespace Engine {
SpotLight::SpotLight( Entity* entity, const std::string& name ) :
    Light( entity, Light::SPOT, name ),
    m_position( 0, 0, 0 ),
    m_direction( 0, -1, 0 ),
    m_attenuation() {}

SpotLight::~SpotLight() {}

void SpotLight::getRenderParameters( RenderParameters& params ) const {
    Light::getRenderParameters( params );

    params.addParameter( "light.spot.position", m_position );
    params.addParameter( "light.spot.direction", m_direction );
    params.addParameter( "light.spot.innerAngle", m_innerAngle );
    params.addParameter( "light.spot.outerAngle", m_outerAngle );
    params.addParameter( "light.spot.attenuation.constant", m_attenuation.constant );
    params.addParameter( "light.spot.attenuation.linear", m_attenuation.linear );
    params.addParameter( "light.spot.attenuation.quadratic", m_attenuation.quadratic );
}

std::string SpotLight::getShaderInclude() const {
    return "Spot";
}
void SpotLight::setTransform( Core::Container::Index roIdx, const Core::Math::Transform& transform ){
    (void) roIdx;

    if(transform(0,0)==1 && transform(0,1)==0 && transform(0,2)==0 ){ // X
      m_direction = Core::Math::Vector3(
        m_direction.x()  ,
        (m_direction.y() * transform(1,1) + m_direction.z() * transform(1,2)) ,
        (m_direction.y() * transform(2,1) + m_direction.z() * transform(2,2))
      );
    }
    else  if (transform(1,0)==0 && transform(1,1)==1 && transform(1,2)==0){ // Y
      m_direction = Core::Math::Vector3(
          ( m_direction.x() * transform(0,0) + m_direction.z() * transform(0,2) ),
          (m_direction.y())  ,
           (m_direction.x() * transform(2,0) + m_direction.z() * transform(2,2))

      );
    }
    else  if (transform(2,0)==0 && transform(2,1)==0 && transform(2,2)==1){ //Z
      m_direction = Core::Math::Vector3(
        ( m_direction.x() * transform(0,0) + m_direction.y() * transform(0,1)) ,
        (m_direction.x() * transform(1,0) + m_direction.y() * transform(1,1))  ,
        m_direction.z()

      );
    }

    m_position = 0.5 * Core::Math::Vector3(m_position.x()+transform(0,3)
                                          ,m_position.y()+transform(1,3)
                                          ,m_position.z()+transform(2,3)
                                          );
}

Core::Math::Transform SpotLight::getTransform( Core::Container::Index roIdx ) const {
    (void) roIdx;
    Core::Math::Transform m =Core::Math::Transform::Identity();
     m = m.translate(m_position);
    return m;
};

} // namespace Engine
} // namespace Ra
