
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_DIMENSION_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_DIMENSION_HPP

#include <utility>
#include <agate_pris/noer/collision_detection/point_type.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>

namespace agate_pris {
namespace noer {
namespace collision_detection {

template< typename CollisionDetectionType >
struct dimension
{
    static constexpr const std::size_t value =
    boost::geometry::dimension< point_type_t< CollisionDetectionType > >::value;
};

} // collision_detection
} // noer
} // agate_pris

#endif
