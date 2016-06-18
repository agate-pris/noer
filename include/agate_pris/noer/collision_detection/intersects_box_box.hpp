
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_BOX_BOX_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_BOX_BOX_HPP

#include <agate_pris/noer/collision_detection/tags.hpp>
#include <boost/geometry/algorithms/intersects.hpp>

namespace agate_pris {
namespace noer {
namespace collision_detection {

template< typename BoxType >
inline bool intersects( BoxType const& a, BoxType const& b, box_tag, box_tag )
{
	return boost::geometry::intersects( a, b );
}

} // collision_detection
} // noer
} // agate_pris

#endif
