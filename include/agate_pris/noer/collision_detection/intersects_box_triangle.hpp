
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_BOX_TRIANGLE_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_BOX_TRIANGLE_HPP

#include <agate_pris/noer/collision_detection/tags.hpp>
#include <agate_pris/noer/collision_detection/dimension.hpp>
#include <agate_pris/noer/collision_detection/point_type.hpp>
#include <agate_pris/noer/collision_detection/access.hpp>
#include <agate_pris/noer/collision_detection/intersects.hpp>
#include <boost/geometry/geometries/segment.hpp>

namespace agate_pris {
namespace noer {
namespace collision_detection {

template< typename BoxType, typename TriangleType >
bool intersects( BoxType const& box, TriangleType const& triangle, box_tag, triangle_tag )
{
	static_assert( dimension< BoxType >::value == 2 && dimension< TriangleType >::value == 2, "Dimension must be 2." );

	using box_point_type = point_type_t< BoxType >;
	using triangle_point_type = point_type_t< TriangleType >;

	const box_point_type a( get< 0, 0 >( box ), get< 0, 1 >( box ) );
	const box_point_type b( get< 1, 0 >( box ), get< 0, 1 >( box ) );
	const box_point_type c( get< 1, 0 >( box ), get< 1, 1 >( box ) );
	const box_point_type d( get< 0, 0 >( box ), get< 1, 1 >( box ) );
	const triangle_point_type e( get< 0, 0 >( triangle ), get< 0, 1 >( triangle ) );
	const triangle_point_type f( get< 1, 0 >( triangle ), get< 1, 1 >( triangle ) );
	const triangle_point_type g( get< 2, 0 >( triangle ), get< 2, 1 >( triangle ) );

	if( intersects( box, e ) )
		return true;
	if( intersects( box, f ) )
		return true;
	if( intersects( box, g ) )
		return true;

	if( intersects( triangle, a ) )
		return true;
	if( intersects( triangle, b ) )
		return true;
	if( intersects( triangle, c ) )
		return true;
	if( intersects( triangle, d ) )
		return true;

	using segment_type = boost::geometry::model::referring_segment< triangle_point_type const >;
	const segment_type ef( e, f );
	const segment_type fg( f, g );
	const segment_type ge( g, e );

	if( intersects( box, ef ) )
		return true;
	if( intersects( box, fg ) )
		return true;
	if( intersects( box, ge ) )
		return true;

	return false;
}

template< typename BoxType, typename TriangleType >
inline bool intersects( TriangleType const& triangle, BoxType const& box, triangle_tag, box_tag )
{
	return intersects( box, triangle );
}

} // collision_detection
} // noer
} // agate_pris

#endif
