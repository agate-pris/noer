
#ifndef AGATE_PRIS_NOER_GEOMETRY_POINT_TYPE_HPP
#define AGATE_PRIS_NOER_GEOMETRY_POINT_TYPE_HPP

#include <boost/geometry/core/point_type.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

namespace traits {

template< typename CollisionDetection >
struct point_type
{
    using type = typename boost::geometry::point_type< CollisionDetection >::type;
};

} // traits

template< typename CollisionDetectionType >
struct point_type
{
    using type = typename traits::point_type< CollisionDetectionType >::type;
};

template< typename CollisionDetectionType >
using point_type_t = typename point_type< CollisionDetectionType >::type;

} // geometry
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_POINT_TYPE_HPP
