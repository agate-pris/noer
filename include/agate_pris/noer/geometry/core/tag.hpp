
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_TAG_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_TAG_HPP

#include <boost/geometry/core/tag.hpp>

namespace agate_pris
{
	namespace noer
	{
		namespace geometry
		{
			namespace traits
			{
				template< typename CollisionDetection >
				struct tag
				{
					using type = typename boost::geometry::tag< CollisionDetection >::type;
				};
			}

			template< typename CollisionDetection >
			struct tag
			{
				using type = typename traits::tag< CollisionDetection >::type;
			};

			template< typename CollisionDetection >
			using tag_t = typename tag< CollisionDetection >::type;
		}
	}
}

#endif
