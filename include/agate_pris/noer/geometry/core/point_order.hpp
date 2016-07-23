
#ifndef AGATE_PRIS_NOER_GEOMETRY_POINT_ORDER_HPP
#define AGATE_PRIS_NOER_GEOMETRY_POINT_ORDER_HPP

#include <boost/geometry/core/point_order.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

namespace traits {

template< typename CollisionDetectionType >
struct point_order
{
    static const boost::geometry::order_selector value = boost::geometry::point_order< CollisionDetectionType >::value;
};

} // traits

template< typename CollisionDetectionType >
struct point_order
{
    static const boost::geometry::order_selector value = traits::point_order< CollisionDetectionType >::value;
};

} // geometry
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_POINT_ORDER_HPP
