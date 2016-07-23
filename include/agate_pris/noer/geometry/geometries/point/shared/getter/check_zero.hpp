
#ifndef AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_POINT_SHARED_GETTER_CHECK_ZERO_HPP
#define AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_POINT_SHARED_GETTER_CHECK_ZERO_HPP

#include <cstddef>
#include <memory>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {
namespace model {
namespace point {
namespace shared {
namespace getter {

// check shared_ptr and
// get coordinate value if it is not nullptr,
// otherwise return 0.
struct check_zero
{
    template< typename Point, std::size_t Dimension >
    static typename boost::geometry::coordinate_type< Point >::type
    impl( std::shared_ptr< Point > const& r );
};

template< typename Point, std::size_t Dimension >
inline typename boost::geometry::coordinate_type< Point >::type
check_zero::impl( std::shared_ptr< Point > const& r )
{
    if( r )
        return boost::geometry::get< Dimension >( *r );
    return static_cast< typename boost::geometry::coordinate_type< Point >::type >( 0 );
}

} // getter
} // shared
} // point
} // model
} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_POINT_SHARED_GETTER_NOCHECK_HPP
