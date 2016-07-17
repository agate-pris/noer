
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_HPP

#include <agate_pris/noer/geometry/core/tag.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/intersects_box_box.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/intersects_box_point.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/intersects_box_segment.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/intersects_box_triangle.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/intersects_container.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/intersects_container_polymorphic.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/intersects_point_triangle.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/intersects_segment_segment.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/intersects_segment_triangle.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/intersects_triangle_triangle.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

template< typename CollisionDetection1, typename CollisionDetection2 >
inline bool intersects( CollisionDetection1 const& a, CollisionDetection2 const& b )
{
    return intersects( a, b, tag_t< CollisionDetection1 >{}, tag_t< CollisionDetection2 >{} );
}

} // collision_detection
} // noer
} // agate_pris

#endif
