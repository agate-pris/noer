
#ifndef AGATE_PRIS_NOER_GEOMETRY_ALGORITHMS_INTERSECTS_BOOST_FUSION_CONTAINER_HPP
#define AGATE_PRIS_NOER_GEOMETRY_ALGORITHMS_INTERSECTS_BOOST_FUSION_CONTAINER_HPP

#include <type_traits>

#include <agate_pris/noer/geometry/core/tags.hpp>
#include <agate_pris/noer/geometry/core/overload_priolity.hpp>
#include <boost/mpl/greater.hpp>

#include <boost/fusion/algorithm/query/any.hpp>
#include <boost/fusion/include/any.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

namespace detail {

template< typename Container, typename Object >
inline bool intersects_boost_fusion_container( Container const& container, Object const& object )
{
    // e is element of container
    auto f = [ &object ]( auto& e ) -> bool
    {
        return intersects( object, e );
    };

    return boost::fusion::any( container, f );
}

} // detail

template< typename Lhs, typename Rhs >
inline bool intersects
(
    Lhs const& lhs,             Rhs const& rhs,
    boost_fusion_container_tag, boost_fusion_container_tag
)
{
    return detail::intersects_boost_fusion_container( lhs, rhs );
}

template< typename Container, typename Object, typename AnyTag >
inline auto intersects
(
    Container const& container, Object const& object,
    boost_fusion_container_tag, AnyTag
)
-> std::enable_if_t< boost::mpl::greater
<
    overload_priolity< boost_fusion_container_tag >,
    overload_priolity< AnyTag                     >
>::value, bool >
{
    return detail::intersects_boost_fusion_container( container, object );
}

template< typename Object, typename Container, typename AnyTag >
inline auto intersects
(
    Object const& object, Container const& container,
    AnyTag,               boost_fusion_container_tag
)
-> std::enable_if_t< boost::mpl::greater
<
    overload_priolity< boost_fusion_container_tag >,
    overload_priolity< AnyTag                     >
>::value, bool >
{
    return detail::intersects_boost_fusion_container( container, object );
}

} // geometry
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_ALGORITHMS_INTERSECTS_BOOST_FUSION_CONTAINER_HPP
