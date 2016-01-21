
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_HPP

#include <agate_pris/noer/collision_detection/tag.hpp>

namespace agate_pris
{
	namespace noer
	{
		namespace collision_detection
		{
			template< typename CollisionDetection1, typename CollisionDetection2 >
			bool intersects( CollisionDetection1 const& a, CollisionDetection2 const& b )
			{
				return intersects( a, b, tag_t< CollisionDetection1 >{}, tag_t< CollisionDetection2 >{} );
			}
		}
	}
}

#endif
