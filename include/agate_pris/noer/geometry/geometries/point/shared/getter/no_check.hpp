
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_GETTER_NO_CHECK_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_GETTER_NO_CHECK_HPP

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

// do not check if shared_ptr is nullptr
// and get coordinate value
struct no_check
{
    template< typename Point, std::size_t Dimension >
    static typename boost::geometry::coordinate_type< Point >::type
    impl( std::shared_ptr< Point > const& r );
};

template< typename Point, std::size_t Dimension >
inline typename boost::geometry::coordinate_type< Point >::type
no_check::impl( std::shared_ptr< Point > const& r )
{
    return boost::geometry::get< Dimension >( *r );
}

} // getter
} // shared
} // point
} // model
} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_GETTER_NOCHECK_HPP
