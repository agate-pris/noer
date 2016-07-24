
#ifndef AGATE_PRIS_NOER_GEOMETRY_ALGORITHMS_INTERSECTS_STL_CONTAINER_HPP
#define AGATE_PRIS_NOER_GEOMETRY_ALGORITHMS_INTERSECTS_STL_CONTAINER_HPP

#include <type_traits>
#include <agate_pris/noer/geometry/core/tags.hpp>
#include <agate_pris/noer/geometry/core/overload_priolity.hpp>
#include <boost/mpl/greater.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

template< typename Lhs, typename Rhs >
inline bool intersects( Lhs const& lhs, Rhs const& rhs, stl_container_tag, stl_container_tag )
{
    for( auto const& e : lhs )
    {
        if( intersects( e, rhs ) )
            return true;
    }

    return false;
}

template< typename Container, typename Object, typename AnyTag >
inline auto intersects( Container const& container, Object const& object, stl_container_tag, AnyTag )
-> std::enable_if_t< boost::mpl::greater
<
    overload_priolity< stl_container_tag >,
    overload_priolity< AnyTag            >
>::value, bool >
{
    for( auto const& e : container )
    {
        if( intersects( e, object ) )
            return true;
    }

    return false;
}

template< typename Object, typename Container, typename AnyTag >
inline auto intersects( Object const& object, Container const& container, AnyTag, stl_container_tag )
-> std::enable_if_t< boost::mpl::greater
    <
    overload_priolity< stl_container_tag >,
    overload_priolity< AnyTag            >
>::value, bool >
{
    return intersects( container, object );
}

} // geometry
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_ALGORITHMS_INTERSECTS_STL_CONTAINER_HPP
