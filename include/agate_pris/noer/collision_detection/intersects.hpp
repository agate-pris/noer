
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_HPP

#include <agate_pris/noer/collision_detection/tag.hpp>
#include <agate_pris/noer/collision_detection/intersects_box_box.hpp>
#include <agate_pris/noer/collision_detection/intersects_box_point.hpp>
#include <agate_pris/noer/collision_detection/intersects_box_segment.hpp>
#include <agate_pris/noer/collision_detection/intersects_point_triangle.hpp>

namespace agate_pris
{
	namespace noer
	{
		namespace collision_detection
		{
			template< typename CollisionDetection1, typename CollisionDetection2 >
			inline bool intersects( CollisionDetection1 const& a, CollisionDetection2 const& b )
			{
				return intersects( a, b, tag_t< CollisionDetection1 >{}, tag_t< CollisionDetection2 >{} );
			}
		}
	}
}

#endif
