
#ifndef AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_ADAPTED_STD_TUPLE_HPP
#define AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_ADAPTED_STD_TUPLE_HPP

#include <tuple>
#include <agate_pris/noer/geometry/core/tag.hpp>
#include <agate_pris/noer/geometry/core/tags.hpp>
#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

namespace traits {

template< typename... Elements >
struct tag< std::tuple< Elements... > >
{
    using type = boost_fusion_container_tag;
};

} // traits

} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_ADAPTED_STD_TUPLE_HPP
