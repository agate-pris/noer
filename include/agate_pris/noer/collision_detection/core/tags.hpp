
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_TAGS_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_TAGS_HPP

#include <boost/geometry/core/tags.hpp>

namespace agate_pris
{
	namespace noer
	{
		namespace collision_detection
		{
			using point_tag   = boost::geometry::point_tag;
			using box_tag     = boost::geometry::box_tag;
			using segment_tag = boost::geometry::segment_tag;
			struct triangle_tag {};
            struct polymorphic_tag {};
            struct container_tag {};
		}
	}
}

#endif
