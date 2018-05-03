#ifndef RADIUMENGINE_KEY_TRANSFORM_HPP
#define RADIUMENGINE_KEY_TRANSFORM_HPP

#include <Core/Asset/Interpolation.hpp>
#include <Core/Asset/KeyFrame.hpp>

namespace Ra {
namespace Core {
namespace Asset {

class KeyTransform : public KeyFrame<Core::Transform> {
  public:
    /// CONSTRUCTOR
    KeyTransform( const AnimationTime& time = AnimationTime() ) :
        KeyFrame<Core::Transform>( time ) {}
    KeyTransform( const KeyTransform& keyframe ) = default;

    /// DESTRUCTOR
    ~KeyTransform() {}

  protected:
    /// TRANSFORMATION
    inline Core::Transform defaultFrame() const override { return Core::Transform::Identity(); }

    inline Core::Transform interpolate( const Core::Transform& F0, const Core::Transform& F1,
                                        const Scalar t ) const override {
        Core::Transform result;
        Core::Asset::interpolate( F0, F1, t, result );
        return result;
    }
};

} // namespace Asset
} // namespace Core
} // namespace Ra

#endif // RADIUMENGINE_KEY_TRANSFORM_HPP
