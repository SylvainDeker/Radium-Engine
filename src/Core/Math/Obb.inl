#include "Obb.hpp"

namespace Ra {
namespace Core {
//
// Bounding boxes functions.
//

inline Math::Aabb Obb::toAabb() const {
    Math::Aabb tmp;
    for ( int i = 0; i < 8; ++i )
    {
        tmp.extend( m_transform * m_aabb.corner( static_cast<Math::Aabb::CornerType>( i ) ) );
    }
    return tmp;
}

inline Math::Vector3 Obb::corner( int i ) const {
    return m_aabb.corner( static_cast<Math::Aabb::CornerType>( i ) );
}

inline Math::Vector3 Obb::worldCorner( int i ) const {
    return m_transform * m_aabb.corner( static_cast<Math::Aabb::CornerType>( i ) );
}

inline void Obb::addPoint( const Math::Vector3& p ) {
    m_aabb.extend( p );
}
} // namespace Core
} // namespace Ra
