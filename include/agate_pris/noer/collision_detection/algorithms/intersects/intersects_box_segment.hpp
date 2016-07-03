
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_BOX_SEGMENT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_BOX_SEGMENT_HPP

#include <agate_pris/noer/collision_detection/tags.hpp>
#include <boost/geometry/algorithms/intersects.hpp>

namespace agate_pris {
namespace noer {
namespace collision_detection {

template< typename BoxType, typename SegmentType >
inline bool intersects( BoxType const& b, SegmentType const& s, box_tag, segment_tag )
{
    return boost::geometry::intersects( b, s );
}

template< typename BoxType, typename SegmentType >
inline bool intersects( SegmentType const& s, BoxType const& b, segment_tag, box_tag )
{
    return boost::geometry::intersects( s, b );
}

} // collision_detection
} // noer
} // agate_pris

#endif
