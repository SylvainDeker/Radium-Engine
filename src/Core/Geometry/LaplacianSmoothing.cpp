#include <Core/Geometry/LaplacianSmoothing.hpp>

#include <utility>

namespace Ra {
namespace Core {
namespace Algorithm {

Geometry::ScalarValue smartClamp( const Geometry::BitSet& bit, const Geometry::ScalarValue& value, const bool flag ) {
    Geometry::ScalarValue s( value );
    Scalar zero = 0.0;
    s.prune( zero );
    for ( Geometry::ScalarValue::InnerIterator it( s, 0 ); it; ++it )
    {
        uint i = it.row();
        if ( !( bit[i] || flag ) )
        {
            s.coeffRef( i, 0 ) = 0.0;
        }
    }
    return s;
}

void smartClamp( const Geometry::BitSet& bit, const Geometry::ScalarValue& value, Geometry::ScalarValue& clamped,
                 const bool flag ) {
    Geometry::ScalarValue s( value );
    Scalar zero = 0.0;
    s.prune( zero );
    for ( Geometry::ScalarValue::InnerIterator it( s, 0 ); it; ++it )
    {
        uint i = it.row();
        if ( !( bit[i] || flag ) )
        {
            s.coeffRef( i, 0 ) = 0.0;
        }
    }
    s.swap( clamped );
}

Container::VectorArray<Vector3> laplacianSmoothing( const Container::VectorArray<Vector3>& v,
                                         const Ra::Core::Geometry::LaplacianMatrix& L,
                                         const Geometry::ScalarValue& weight, const uint iteration ) {
    Container::VectorArray<Vector3> p( v );
    auto pM = p.getMap();
    Container::VectorArray<Vector3> tmp( v );
    auto tmpM = tmp.getMap();
    for ( uint i = 0; i < iteration; ++i )
    {
        tmpM = pM * L;
        for ( uint c = 0; c < v.size(); ++c )
        {
            tmpM.col( c ) = ( tmpM.col( c ) * weight.coeff( c, 0 ) ) +
                            ( pM.col( c ) * ( 1.0 - weight.coeff( c, 0 ) ) );
        }
        pM.swap( tmpM );
    }
    return tmp;
}

void laplacianSmoothing( const Container::VectorArray<Vector3>& v,
                         const Ra::Core::Geometry::LaplacianMatrix& L, const Geometry::ScalarValue& weight,
                         const uint iteration, Container::VectorArray<Vector3>& p ) {
    p = v;
    auto pM = p.getMap();
    Container::VectorArray<Vector3> tmp( v );
    auto tmpM = tmp.getMap();
    for ( uint i = 0; i < iteration; ++i )
    {
        tmpM = pM * L;
        for ( uint c = 0; c < v.size(); ++c )
        {
            tmpM.col( c ) = ( tmpM.col( c ) * weight.coeff( c, 0 ) ) +
                            ( pM.col( c ) * ( 1.0 - weight.coeff( c, 0 ) ) );
        }
        pM.swap( tmpM );
    }
    std::swap( p, tmp );
}

} // namespace Algorithm
} // namespace Core
} // namespace Ra
