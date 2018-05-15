#ifndef RADIUM_DISTANCETESTS_HPP_
#define RADIUM_DISTANCETESTS_HPP_

#include <Core/Geometry/DistanceQueries.hpp>

using Ra::Core::Math::Vector3;
namespace RaTests {
class DistanceTests : public Test {
    void run() override {
        Math::Vector3 a( -2.f, 0.f, 0.f );
        Math::Vector3 b( 2.f, 0.f, 0.f );
        Math::Vector3 c( 0.f, 3.f, 0.f );
        Math::Vector3 d( 0.f, -3.f, 0.f );
        Math::Vector3 e( -4.f, -3.f, 0.f );
        Math::Vector3 f( 4.f, 3.f, 0.f );

        // Test point to triangle query
        Scalar distPointToTri =
            std::sqrt( Ra::Core::Geometry::pointToTriSq( c, a, b, d ).distanceSquared );
        RA_UNIT_TEST( distPointToTri == ( c - ( 0.5 * ( a + b ) ) ).norm(),
                      "Distance point to triangle not ok." );

        // Test line to segment distance query
        const Math::Vector3& lineOrigin = a;
        Math::Vector3 lineDirection = d - a;
        const Math::Vector3& segCenter = (Scalar)0.5 * ( c + b );
        Math::Vector3 segDirection = b - c;
        Scalar segExtent = (Scalar)0.5 * std::sqrt( ( b - c ).dot( b - c ) );
        Scalar distLineToSeg = Ra::Core::Geometry::lineToSegSq(
                                   lineOrigin, lineDirection, segCenter, segDirection, segExtent )
                                   .sqrDistance;
        RA_UNIT_TEST( distLineToSeg == Ra::Core::Geometry::pointToSegmentSq( a, c, b - c ),
                      "Distance line to segment not ok." );

        // Test line to triangle distance query
        Math::Vector3 v[3] = {a, d, e};
        Scalar distLineToTri =
            Ra::Core::Geometry::lineToTriSq( segCenter, segDirection, v ).sqrDistance;
        RA_UNIT_TEST( distLineToTri == Ra::Core::Geometry::pointToSegmentSq( a, c, b - c ),
                      "Distance line to triangle not ok." );

        // Test segment to triangle distance query
        Scalar distSegToTri =
            Ra::Core::Geometry::segmentToTriSq( segCenter, segDirection, segExtent, v )
                .sqrDistance;
        RA_UNIT_TEST( distSegToTri == Ra::Core::Geometry::pointToSegmentSq( a, c, b - c ),
                      "Distance segment to triangle not ok." );

        // Test triangle to triangle distance query
        Math::Vector3 v2[3] = {c, f, b};
        Scalar distTriToTri = Ra::Core::Geometry::triangleToTriSq( v, v2 ).sqrDistance;
        RA_UNIT_TEST( distTriToTri == Ra::Core::Geometry::pointToSegmentSq( a, c, b - c ),
                      "Distance triangle to triangle not ok." );
    }
};

RA_TEST_CLASS( DistanceTests );
} // namespace RaTests

#endif // RADIUM_DISTANCETESTS_HPP_
