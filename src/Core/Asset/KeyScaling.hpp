#ifndef RADIUMENGINE_KEY_SCALING_HPP
#define RADIUMENGINE_KEY_SCALING_HPP

#include <Core/Asset/Interpolation.hpp>
#include <Core/Asset/KeyFrame.hpp>

namespace Ra {
namespace Core {
namespace Asset {

class KeyScaling : public KeyFrame<Core::Vector3> {
  public:
    /// CONSTRUCTOR
    KeyScaling( const AnimationTime& time = AnimationTime() ) : KeyFrame<Core::Vector3>( time ) {}
    KeyScaling( const KeyScaling& keyframe ) = default;

    /// DESTRUCTOR
    ~KeyScaling() {}

  protected:
    /// TRANSFORMATION
    inline Core::Vector3 defaultFrame() const override { return Core::Vector3( 1.0, 1.0, 1.0 ); }

    inline Core::Vector3 interpolate( const Core::Vector3& F0, const Core::Vector3& F1,
                                      const Scalar t ) const override {
        Core::Vector3 result;
        Core::Asset::interpolate( F0, F1, t, result );
        return result;
    }
};

} // namespace Asset
} // namespace Core
} // namespace Ra

#endif // RADIUMENGINE_KEY_SCALING_HPP
