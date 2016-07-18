
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_SETTER_CHECK_ASSERT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_SETTER_CHECK_ASSERT_HPP

#include <cstddef>
#include <memory>
#include <cassert>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {
namespace model {
namespace point {
namespace shared {
namespace setter {

// check shared_ptr and
// set coordinate value if it is not nullptr,
// otherwise assert.
struct check_assert
{
    template< typename Point, std::size_t Dimension >
    static void impl( std::shared_ptr< Point > const& r, typename boost::geometry::coordinate_type< Point >::type const& v );
};

template< typename Point, std::size_t Dimension >
inline void check_assert::impl
( std::shared_ptr< Point > const& r, typename boost::geometry::coordinate_type< Point >::type const& v )
{
    auto const check_assert_impl_argument_r_must_not_be_nullptr = static_cast< bool >( r );
    assert( check_assert_impl_argument_r_must_not_be_nullptr );
    boost::geometry::set< Dimension >( *r, v );
}

} // setter
} // shared
} // point
} // model
} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_SETTER_CHECK_THROW_HPP
