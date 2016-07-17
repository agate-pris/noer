
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_BOX_POINT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_BOX_POINT_HPP

#include <agate_pris/noer/collision_detection/core/tags.hpp>
#include <boost/geometry/algorithms/intersects.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

template< typename BoxType, typename PointType >
inline bool intersects( BoxType const& b, PointType const& p, box_tag, point_tag )
{
    return boost::geometry::intersects( b, p );
}

template< typename BoxType, typename PointType >
inline bool intersects( PointType const& p, BoxType const& b, point_tag, box_tag )
{
    return boost::geometry::intersects( p, b );
}

} // collision_detection
} // noer
} // agate_pris

#endif
