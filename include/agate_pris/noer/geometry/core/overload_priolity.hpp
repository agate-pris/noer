
#ifndef AGATE_PRIS_NOER_GEOMETRY_CORE_OVERLOAD_PRIOLITY_HPP
#define AGATE_PRIS_NOER_GEOMETRY_CORE_OVERLOAD_PRIOLITY_HPP

#include <boost/mpl/long.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

namespace traits {

template< typename T >
struct overload_priolity
    : boost::mpl::long_< 0 >
{};

} // traits

template< typename T >
struct overload_priolity
    : traits::overload_priolity< T >
{};

} // geometry
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_CORE_OVERLOAD_PRIOLITY_HPP
