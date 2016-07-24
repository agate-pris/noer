
#ifndef AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_POINT_SHARED_SETTER_NO_CHECK_HPP
#define AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_POINT_SHARED_SETTER_NO_CHECK_HPP

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
namespace setter {

// do not check if shared_ptr is nullptr
// set coordinate value
struct no_check
{
    template< typename Point, std::size_t Dimension >
    static void impl( std::shared_ptr< Point > const& r, typename boost::geometry::coordinate_type< Point >::type const& v );
};

template< typename Point, std::size_t Dimension >
inline void no_check::impl
( std::shared_ptr< Point > const& r, typename boost::geometry::coordinate_type< Point >::type const& v )
{
    boost::geometry::set< Dimension >( *r, v );
}

} // setter
} // shared
} // point
} // model
} // geometry
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_POINT_SHARED_SETTER_CHECK_THROW_HPP
