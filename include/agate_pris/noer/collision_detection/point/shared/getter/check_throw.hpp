
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_GETTER_CHECK_THROW_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_GETTER_CHECK_THROW_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>
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
// otherwise throw exception std::invalid_argument.
struct check_throw
{
    template< typename Point, std::size_t Dimension >
    static typename boost::geometry::coordinate_type< Point >::type
    impl( std::shared_ptr< Point > const& r );
};

template< typename Point, std::size_t Dimension >
inline typename boost::geometry::coordinate_type< Point >::type
check_throw::impl( std::shared_ptr< Point > const& r )
{
    if( r )
        return boost::geometry::get< Dimension >( *r );
    throw std::invalid_argument(
        "agate_pris::noer::geometry::point::shared::getter::check_throw::impl "
        "detect invalid argument.\n"
        "argument r must not be nullptr."
    );
}

} // getter
} // shared
} // point
} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_GETTER_NOCHECK_HPP
