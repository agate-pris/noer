
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_TRIANGLE_TRIANGLE_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_TRIANGLE_TRIANGLE_HPP

#include <agate_pris/noer/collision_detection/access.hpp>
#include <agate_pris/noer/collision_detection/dimension.hpp>
#include <agate_pris/noer/collision_detection/intersects.hpp>
#include <agate_pris/noer/collision_detection/point_type.hpp>
#include <agate_pris/noer/collision_detection/tags.hpp>
#include <boost/geometry/geometries/segment.hpp>

namespace agate_pris {
namespace noer {
namespace collision_detection {

template< typename TriangleType >
bool intersects( TriangleType const& abc, TriangleType const& def, triangle_tag, triangle_tag )
{
    static_assert( dimension< TriangleType >::value == 2, "Dimension must be 2." );

    using point_type = point_type_t< TriangleType >;
    using segment_type = boost::geometry::model::referring_segment< point_type const >;

    const point_type a( get< 0, 0 >( abc ), get< 0, 1 >( abc ) );
    const point_type b( get< 1, 0 >( abc ), get< 1, 1 >( abc ) );
    const point_type c( get< 2, 0 >( abc ), get< 2, 1 >( abc ) );
    const point_type d( get< 0, 0 >( def ), get< 0, 1 >( def ) );
    const point_type e( get< 1, 0 >( def ), get< 1, 1 >( def ) );
    const point_type f( get< 2, 0 >( def ), get< 2, 1 >( def ) );

    if( intersects( a, def ) )
        return true;
    if( intersects( b, def ) )
        return true;
    if( intersects( c, def ) )
        return true;

    if( intersects( d, abc ) )
        return true;
    if( intersects( e, abc ) )
        return true;
    if( intersects( f, abc ) )
        return true;

    const auto ab = segment_type( a, b );
    const auto bc = segment_type( b, c );
    const auto ca = segment_type( c, a );
    const auto de = segment_type( d, e );
    const auto ef = segment_type( e, f );
    const auto fd = segment_type( f, d );

    if( intersects( ab, de ) )
        return true;
    if( intersects( ab, ef ) )
        return true;
    if( intersects( ab, fd ) )
        return true;

    if( intersects( bc, de ) )
        return true;
    if( intersects( bc, ef ) )
        return true;
    if( intersects( bc, fd ) )
        return true;

    if( intersects( ca, de ) )
        return true;
    if( intersects( ca, ef ) )
        return true;
    if( intersects( ca, fd ) )
        return true;

    return false;
}

} // collision_detection
} // noer
} // agate_pris

#endif
