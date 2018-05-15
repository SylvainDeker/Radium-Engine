#include <Core/Animation/PoseOperation.hpp>
#include <Eigen/Geometry>

namespace Ra {
namespace Core {
namespace Animation {

bool compatible( const Pose& p0, const Pose& p1 ) {
    return ( p0.size() == p1.size() );
}

Pose relativePose( const Pose& modelPose, const RestPose& restPose ) {
    CORE_ASSERT( compatible( modelPose, restPose ), " Poses with different size " );
    Pose T( restPose.size() );
#pragma omp parallel for
    for ( int i = 0; i < int( T.size() ); ++i )
    {
        T[i] = modelPose[i] * restPose[i].inverse( Eigen::Affine );
    }
    return T;
}

Pose applyTransformation( const Pose& pose, const Container::AlignedStdVector<Math::Transform>& transform ) {
    Pose T( std::min( pose.size(), transform.size() ) );
#pragma omp parallel for
    for ( int i = 0; i < int( T.size() ); ++i )
    {
        T[i] = transform[i] * pose[i];
    }
    return T;
}

Pose applyTransformation( const Pose& pose, const Math::Transform& transform ) {
    Pose T( pose.size() );
#pragma omp parallel for
    for ( int i = 0; i < int( T.size() ); ++i )
    {
        T[i] = transform * pose[i];
    }
    return T;
}

bool areEqual( const Pose& p0, const Pose& p1 ) {
    CORE_ASSERT( compatible( p0, p1 ), " Poses with different size " );
    const uint n = p0.size();
    for ( uint i = 0; i < n; ++i )
    {
        if ( !p0[i].isApprox( p1[i] ) )
        {
            return false;
        }
    }
    return true;
}

Pose interpolatePoses( const Pose& a, const Pose& b, const Scalar t ) {
    CORE_ASSERT( ( a.size() == b.size() ), "Poses are wrong" );
    CORE_ASSERT( ( ( t >= 0.0 ) && ( t <= 1.0 ) ), "T is wrong" );

    const uint size = a.size();
    Pose interpolatedPose( size );

#pragma omp parallel for
    for ( int i = 0; i < int( size ); ++i )
    {
        // interpolate between the transforms
        Ra::Core::Math::Transform aTransform = a[i];
        Ra::Core::Math::Transform bTransform = b[i];

        Ra::Core::Math::Quaternion aRot = Ra::Core::Math::Quaternion( aTransform.rotation() );
        Ra::Core::Math::Quaternion bRot = Ra::Core::Math::Quaternion( bTransform.rotation() );
        Ra::Core::Math::Quaternion interpRot = aRot.slerp( t, bRot );

        Ra::Core::Math::Vector3 interpTranslation =
            ( 1.0 - t ) * aTransform.translation() + t * bTransform.translation();

        Ra::Core::Math::Transform interpolatedTransform;
        interpolatedTransform.linear() = interpRot.toRotationMatrix();
        interpolatedTransform.translation() = interpTranslation;

        interpolatedPose[i] = interpolatedTransform;
    }

    return interpolatedPose;
}

void interpolateTransforms( const Ra::Core::Math::Transform& a, const Ra::Core::Math::Transform& b,
                            const Scalar t, Ra::Core::Math::Transform& interpolated ) {
    Ra::Core::Math::Quaternion aRot = Ra::Core::Math::Quaternion( a.rotation() );
    Ra::Core::Math::Quaternion bRot = Ra::Core::Math::Quaternion( b.rotation() );
    Ra::Core::Math::Quaternion interpRot = aRot.slerp( t, bRot );

    Ra::Core::Math::Vector3 interpTranslation = ( 1.0 - t ) * a.translation() + t * b.translation();

    interpolated.linear() = interpRot.toRotationMatrix();
    interpolated.translation() = interpTranslation;
}

} // namespace Animation
} // namespace Core
} // namespace Ra
