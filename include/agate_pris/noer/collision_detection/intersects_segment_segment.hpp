
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_SEGMENT_SEGMENT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_SEGMENT_SEGMENT_HPP

#include <agate_pris/noer/collision_detection/tags.hpp>
#include <agate_pris/noer/collision_detection/dimension.hpp>
#include <agate_pris/noer/collision_detection/point_type.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <agate_pris/noer/collision_detection/access.hpp>
#include <boost/geometry/strategies/cartesian/side_by_triangle.hpp>

namespace agate_pris {
namespace noer {
namespace collision_detection {

template< typename SegmentType >
bool intersects( SegmentType const& ab, SegmentType const& cd, segment_tag, segment_tag )
{
	static_assert( dimension< SegmentType >::value == 2, "Dimension must be 2." );

	namespace bg = boost::geometry;

	using point_type = point_type_t< SegmentType >;
	using coordinate_type = typename bg::coordinate_type< point_type >::type;

	auto box_ab = bg::return_envelope< bg::model::box< point_type > >( ab );
	auto box_cd = bg::return_envelope< bg::model::box< point_type > >( cd );

	if( !intersects( box_ab, box_cd ) )
		return false;

	const point_type a( get< 0, 0 >( ab ), get< 0, 1 >( ab ) );
	const point_type b( get< 1, 0 >( ab ), get< 1, 1 >( ab ) );
	const point_type c( get< 0, 0 >( cd ), get< 0, 1 >( cd ) );
	const point_type d( get< 1, 0 >( cd ), get< 1, 1 >( cd ) );

	auto acb = bg::strategy::side::side_by_triangle< coordinate_type >::apply( a, b, c );
	auto adb = bg::strategy::side::side_by_triangle< coordinate_type >::apply( a, b, d );
	auto cad = bg::strategy::side::side_by_triangle< coordinate_type >::apply( c, d, a );
	auto cbd = bg::strategy::side::side_by_triangle< coordinate_type >::apply( c, d, b );

	return acb * adb <= 0 && cad * cbd <= 0;
}

} // collision_detection
} // noer
} // agate_pris

#endif
