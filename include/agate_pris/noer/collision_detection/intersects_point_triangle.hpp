
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_POINT_TRIANGLE_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_POINT_TRIANGLE_HPP

#include <utility>
#include <agate_pris/noer/collision_detection/tags.hpp>
#include <agate_pris/noer/collision_detection/dimension.hpp>
#include <agate_pris/noer/collision_detection/point_type.hpp>
#include <agate_pris/noer/collision_detection/access.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <boost/geometry/strategies/cartesian/side_by_triangle.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <agate_pris/noer/collision_detection/point_order.hpp>

namespace agate_pris
{
	namespace noer
	{
		namespace collision_detection
		{
			template< typename PointType, typename TriangleType >
			bool intersects( PointType const& point, TriangleType const& triangle, point_tag, triangle_tag )
			{
				static_assert( dimension< PointType >::value == 2 && dimension< TriangleType >::value == 2, "Dimension must be 2." );

				namespace bg = boost::geometry;
				using triangle_point_type = point_type_t< TriangleType >;
				using point_coordinate_type = typename bg::coordinate_type< PointType >::type;
				using triangle_coordinate_type = typename bg::coordinate_type< triangle_point_type >::type;
				using coordinate_type = decltype( std::declval< point_coordinate_type >() + std::declval< triangle_coordinate_type >() );

				const auto bounting_box = bg::return_envelope< bg::model::box< triangle_point_type > >( triangle );

				if( !intersects( point, bounting_box ) )
					return false;

				const triangle_point_type a( get< 0, 0 >( triangle ), get< 0, 1 >( triangle ) );
				const triangle_point_type b( get< 1, 0 >( triangle ), get< 1, 1 >( triangle ) );
				const triangle_point_type c( get< 2, 0 >( triangle ), get< 2, 1 >( triangle ) );

				const auto apb = bg::strategy::side::side_by_triangle< coordinate_type >::apply( a, b, point );
				const auto bpc = bg::strategy::side::side_by_triangle< coordinate_type >::apply( b, c, point );
				const auto cpa = bg::strategy::side::side_by_triangle< coordinate_type >::apply( c, a, point );

				// clockwise
				if( point_order< TriangleType >::value == bg::clockwise )
				{
					// all is right
					return 0 <= apb && 0 <= bpc && 0 <= cpa;
				}
				// counterclockwise
				// all is left
				return 0 >= apb && 0 >= bpc && 0 >= cpa;
			}

			template< typename PointType, typename TriangleType >
			inline bool intersects( TriangleType const& triangle, PointType const& point, triangle_tag, point_tag )
			{
				return intersects( point, triangle );
			}
		}
	}
}

#endif
