
#ifndef AGATE_PRIS_NOER_GEOMETRY_ALGORITHMS_INTERSECTS_ANY_POLYMORPHIC_HPP
#define AGATE_PRIS_NOER_GEOMETRY_ALGORITHMS_INTERSECTS_ANY_POLYMORPHIC_HPP

#include <type_traits>

#include <agate_pris/noer/geometry/core/tags.hpp>
#include <agate_pris/noer/geometry/core/overload_priolity.hpp>
#include <boost/mpl/greater.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

template< typename Lhs, typename Rhs, typename AnyTag >
inline auto intersects( Lhs const& lhs, Rhs const& rhs, polymorphic_tag, AnyTag )
->std::enable_if_t
< boost::mpl::greater< overload_priolity< polymorphic_tag >, overload_priolity< AnyTag > >::value, bool >
{
    return lhs.intersects( rhs );
}

template< typename Lhs, typename Rhs, typename AnyTag >
inline auto intersects( Lhs const& lhs, Rhs const& rhs, AnyTag, polymorphic_tag )
->std::enable_if_t
< boost::mpl::greater< overload_priolity< polymorphic_tag >, overload_priolity< AnyTag > >::value, bool >
{
    return rhs.intersects( lhs );
}

} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_ALGORITHMS_INTERSECTS_ANY_POLYMORPHIC_HPP
