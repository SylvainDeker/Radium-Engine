#include <Engine/Renderer/Light/DirLight.hpp>

#include <Engine/Renderer/RenderTechnique/RenderParameters.hpp>
#include <QMessageBox>
namespace Ra {
namespace Engine {
DirectionalLight::DirectionalLight( Entity* entity, const std::string& name ) :
    Light( entity, Light::DIRECTIONAL, name ),
    m_direction( 0, -1, 0 ) {}

DirectionalLight::~DirectionalLight() {}

void DirectionalLight::getRenderParameters( RenderParameters& params ) const {
    Light::getRenderParameters( params );

    params.addParameter( "light.directional.direction", m_direction );
}
void DirectionalLight::setTransform( Core::Container::Index roIdx, const Core::Math::Transform& transform ){
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

    if(transform(0,3)!=0 || transform(1,3)!= 0 || transform(2,3)!= 0){
      QMessageBox::warning(nullptr,"Warning",
        "Translation does not affect a Directional Light !");
    }

}

Core::Math::Transform DirectionalLight::getTransform( Core::Container::Index roIdx ) const {
    (void) roIdx;
    return Core::Math::Transform::Identity();
};

std::string DirectionalLight::getShaderInclude() const {
    return "Directional";
}

} // namespace Engine
} // namespace Ra
