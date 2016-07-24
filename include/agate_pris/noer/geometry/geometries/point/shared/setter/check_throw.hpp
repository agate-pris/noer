
#ifndef AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_POINT_SHARED_SETTER_CHECK_THROW_HPP
#define AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_POINT_SHARED_SETTER_CHECK_THROW_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>
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
// otherwise throw exception std::invalid_argument.
struct check_throw
{
    template< typename Point, std::size_t Dimension >
    static void impl( std::shared_ptr< Point > const& r, typename boost::geometry::coordinate_type< Point >::type const& v );
};

template< typename Point, std::size_t Dimension >
inline void check_throw::impl
( std::shared_ptr< Point > const& r, typename boost::geometry::coordinate_type< Point >::type const& v )
{
    if( r )
        boost::geometry::set< Dimension >( *r, v );
    throw std::invalid_argument(
        "agate_pris::noer::geometry::model::point::shared::setter::check_throw::impl "
        "detect invalid argument.\n"
        "argument r must not be nullptr."
    );
}

} // setter
} // shared
} // point
} // model
} // geometry
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_POINT_SHARED_SETTER_CHECK_THROW_HPP
