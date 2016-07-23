
#ifndef AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_ADAPTED_STD_LIST_HPP
#define AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_ADAPTED_STD_LIST_HPP

#include <list>
#include <agate_pris/noer/geometry/core/tag.hpp>
#include <agate_pris/noer/geometry/core/tags.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

namespace traits {

template< typename T >
struct tag< std::list< T > >
{
    using type = stl_container_tag;
};

} // traits

} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_GEOMETRIES_ADAPTED_STD_LIST_HPP
