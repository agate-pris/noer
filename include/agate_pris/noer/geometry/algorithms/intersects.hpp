
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_HPP

#include <agate_pris/noer/geometry/core/tag.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/box_box.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/box_point.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/box_segment.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/box_triangle.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/boost_fusion_container.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/container_polymorphic.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/point_triangle.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/segment_segment.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/segment_triangle.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/triangle_triangle.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/polymorphic_polymorphic.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/any_polymorphic.hpp>

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
