
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_GETTER_CHECK_ASSERT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_GETTER_CHECK_ASSERT_HPP

#include <cstddef>
#include <memory>
#include <cassert>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {
namespace point {
namespace shared {
namespace getter {

// check shared_ptr and
// get coordinate value if it is not nullptr,
// otherwise assert.
struct check_assert
{
    template< typename Point, std::size_t Dimension >
    static typename boost::geometry::coordinate_type< Point >::type
    impl( std::shared_ptr< Point > const& r );
};

template< typename Point, std::size_t Dimension >
inline typename boost::geometry::coordinate_type< Point >::type
check_assert::impl( std::shared_ptr< Point > const& r )
{
    auto const check_assert_impl_argument_r_must_not_be_nullptr = static_cast< bool >( r );
    assert( check_zero_impl_argument_r_must_not_be_nullptr );
    return boost::geometry::get< Dimension >( *r );
}

} // getter
} // shared
} // point
} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_GETTER_NOCHECK_HPP
