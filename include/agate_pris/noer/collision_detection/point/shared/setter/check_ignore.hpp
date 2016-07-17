
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_SETTER_CHECK_IGNORE_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_SETTER_CHECK_IGNORE_HPP

#include <cstddef>
#include <memory>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {
namespace point {
namespace shared {
namespace setter {

// check shared_ptr and
// set coordinate value if it is not nullptr,
// otherwise ignore.
struct check_ignore
{
    template< typename Point, std::size_t Dimension >
    static void impl( std::shared_ptr< Point > const& r, typename boost::geometry::coordinate_type< Point >::type const& v );
};

template< typename Point, std::size_t Dimension >
inline void check_ignore::impl
( std::shared_ptr< Point > const& r, typename boost::geometry::coordinate_type< Point >::type const& v )
{
    if( r )
        boost::geometry::set< Dimension >( *r, v );
}

} // setter
} // shared
} // point
} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_SETTER_CHECK_THROW_HPP
