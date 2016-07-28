
#ifndef AGATE_PRIS_NOER_GEOMETRY_ARITHMETIC_ARITHMETIC_HPP
#define AGATE_PRIS_NOER_GEOMETRY_ARITHMETIC_ARITHMETIC_HPP

#include <cstddef>
#include <type_traits>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/call_traits.hpp>
#include <boost/geometry/core/access.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

namespace detail {

template< typename Point >
struct param
{
    using type = typename boost::call_traits
    <
        typename boost::geometry::coordinate_type< Point >::type
    >::param_type;
};

} // detail

template< std::size_t Dimension, typename Point, typename Value >
inline void add_value( Point& p, Value const& value )
{
    namespace bg = ::boost::geometry;
    auto c = bg::get< Dimension >( p );
    c += value;
    bg::set< Dimension >( p, c );
}

template< std::size_t Dimension, typename Point, typename Value >
inline void subtract_value( Point& p, Value const& value )
{
    namespace bg = ::boost::geometry;
    auto c = bg::get< Dimension >( p );
    c -= value;
    bg::set< Dimension >( p, c );
}

} // geometry
} // noer
} // geometry

#endif
