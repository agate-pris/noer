﻿
#ifndef AGATE_PRIS_NOER_GEOMETRY_INTERSECTS_HPP
#define AGATE_PRIS_NOER_GEOMETRY_INTERSECTS_HPP

#include <agate_pris/noer/geometry/core/tag.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/box_box.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/box_point.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/box_segment.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/box_triangle.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/point_triangle.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/segment_segment.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/segment_triangle.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/triangle_triangle.hpp>

#include <agate_pris/noer/geometry/algorithms/intersects/stl_container.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/boost_fusion_container.hpp>
#include <agate_pris/noer/geometry/algorithms/intersects/polymorphic.hpp>

#include <agate_pris/noer/geometry/geometries/adapted/std_list.hpp>
#include <agate_pris/noer/geometry/geometries/adapted/std_tuple.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

template< typename CollisionDetection1, typename CollisionDetection2 >
inline bool intersects( CollisionDetection1 const& a, CollisionDetection2 const& b )
{
    return intersects( a, b, tag_t< CollisionDetection1 >{}, tag_t< CollisionDetection2 >{} );
}

} // geometry
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_INTERSECTS_HPP
