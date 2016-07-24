
#ifndef AGATE_PRIS_NOER_GEOMETRY_INTERSECTS_BOX_SEGMENT_HPP
#define AGATE_PRIS_NOER_GEOMETRY_INTERSECTS_BOX_SEGMENT_HPP

#include <agate_pris/noer/geometry/core/tags.hpp>
#include <boost/geometry/algorithms/intersects.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

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

} // geometry
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_INTERSECTS_BOX_SEGMENT_HPP
