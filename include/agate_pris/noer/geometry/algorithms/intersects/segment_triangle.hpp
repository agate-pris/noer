
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_SEGMENT_TRIANGLE_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_SEGMENT_TRIANGLE_HPP

#include <agate_pris/noer/geometry/core/coordinate_dimension.hpp>
#include <agate_pris/noer/geometry/core/point_type.hpp>
#include <agate_pris/noer/geometry/core/tags.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/geometries/segment.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

template< typename SegmentType, typename TriangleType >
bool intersects( SegmentType const& s, TriangleType const& t, segment_tag, triangle_tag )
{
    static_assert( dimension< SegmentType >::value == 2 && dimension< TriangleType >::value == 2, "Dimension must be 2." );

    namespace bg = boost::geometry;

    using segment_point_type = point_type_t< SegmentType >;
    using segment_coordinate_type = typename bg::coordinate_type< segment_point_type >::type;
    using triangle_point_type = point_type_t< TriangleType >;
    using triangle_edge_type = bg::model::segment< triangle_point_type >;

    if( intersects( triangle, segment_point_type( get< 0, 0 >( s ), get< 0, 1 >( s ) ) ) )
        return true;
    if( intersects( triangle, segment_point_type( get< 1, 0 >( s ), get< 1, 1 >( s ) ) ) )
        return true;

    const triangle_edge_type ab( get< 0, 0 >( t ), get< 0, 1 >( t ) );
    const triangle_edge_type bc( get< 1, 0 >( t ), get< 1, 1 >( t ) );
    const triangle_edge_type ca( get< 2, 0 >( t ), get< 2, 1 >( t ) );

    if( intersects( s, ab ) )
        return true;
    if( intersects( s, bc ) )
        return true;
    if( intersects( s, ca ) )
        return true;

    return false;
}

template< typename SegmentType, typename TriangleType >
inline bool intersects( TriangleType const& t, SegmentType const& s, triangle_tag, segment_tag )
{
    return intersects( s, t );
}

} // collision_detection
} // noer
} // agate_pris

#endif
