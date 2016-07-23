
#ifndef AGATE_PRIS_NOER_GEOMETRY_TAG_HPP
#define AGATE_PRIS_NOER_GEOMETRY_TAG_HPP

#include <boost/geometry/core/tag.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

namespace traits {

template< typename CollisionDetection >
struct tag
{
    using type = typename boost::geometry::tag< CollisionDetection >::type;
};

} // traits

template< typename CollisionDetection >
struct tag
{
    using type = typename traits::tag< CollisionDetection >::type;
};

template< typename CollisionDetection >
using tag_t = typename tag< CollisionDetection >::type;

} // agate_pris
} // noer
} // geometry

#endif // AGATE_PRIS_NOER_GEOMETRY_TAG_HPP
