
#ifndef AGATE_PRIS_NOER_GEOMETRY_INTERSECTS_BOX_BOX_HPP
#define AGATE_PRIS_NOER_GEOMETRY_INTERSECTS_BOX_BOX_HPP

#include <agate_pris/noer/geometry/core/tags.hpp>
#include <boost/geometry/algorithms/intersects.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

template< typename BoxType >
inline bool intersects( BoxType const& a, BoxType const& b, box_tag, box_tag )
{
    return boost::geometry::intersects( a, b );
}

} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_INTERSECTS_BOX_BOX_HPP
