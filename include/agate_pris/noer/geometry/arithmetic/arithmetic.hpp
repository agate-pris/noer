
#ifndef AGATE_PRIS_NOER_GEOMETRY_ARITHMETIC_ARITHMETIC_HPP
#define AGATE_PRIS_NOER_GEOMETRY_ARITHMETIC_ARITHMETIC_HPP

#include <cstddef>
#include <type_traits>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/call_traits.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>

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

enum class eval
{
    add,
    sub,
};

namespace detail {

template< eval Eval, std::size_t Dimension, typename Point, typename Value >
struct eval_value;

template< std::size_t Dimension, typename Point, typename Value >
struct eval_value< eval::add, Dimension, Point, Value >
{
    static void impl( Point&, Value const& );
};

template< std::size_t Dimension, typename Point, typename Value >
struct eval_value< eval::sub, Dimension, Point, Value >
{
    static void impl( Point&, Value const& );
};

template<std::size_t Dimension, typename Point, typename Value>
inline void eval_value< eval::add, Dimension, Point, Value >::impl
( Point& p, Value const& v )
{
    namespace bg = ::boost::geometry;
    auto c = bg::get< Dimension >( p );
    c += v;
    bg::set< Dimension >( p, c );
}

template<std::size_t Dimension, typename Point, typename Value>
inline void eval_value< eval::sub, Dimension, Point, Value >::impl
( Point& p, Value const& v )
{
    namespace bg = ::boost::geometry;
    auto c = bg::get< Dimension >( p );
    c -= v;
    bg::set< Dimension >( p, c );
}

} // detail

template< std::size_t Dimension, typename Point, typename Value >
inline void add_value( Point& p, Value const& v )
{
    detail::eval_value< eval::add, Dimension, Point, Value >::impl
    ( p, v );
}

template< std::size_t Dimension, typename Point, typename Value >
inline void subtract_value( Point& p, Value const& v )
{
    detail::eval_value< eval::sub, Dimension, Point, Value >::impl
    ( p, v );
}

namespace detail {

template< std::size_t Begin, std::size_t End, bool IsLast = ( Begin + 1 ) == End, bool IsEnd = Begin == End >
struct add_point;

template< std::size_t Begin, std::size_t End >
struct add_point< Begin, End, false, true >
{
    template< typename Lhs, typename Rhs >
    static void impl( Lhs&, Rhs const& ) {}
};

template< std::size_t Begin, std::size_t End >
struct add_point< Begin, End, true, false >
{
    template< typename Lhs, typename Rhs >
    static void impl( Lhs& lhs, Rhs const& rhs )
    {
        namespace bg = ::boost::geometry;
        auto c = bg::get< Begin >( lhs );
        c += bg::get< Begin >( rhs );
        bg::set< Begin >( lhs, c );
    }
};

template< std::size_t Begin, std::size_t End >
struct add_point< Begin, End, false, false >
{
    template< typename Lhs, typename Rhs >
    static void impl( Lhs& lhs, Rhs const& rhs )
    {
        constexpr std::size_t border = ( Begin + End ) / 2;
        add_point< Begin,  border >::impl( lhs, rhs );
        add_point< border, End    >::impl( lhs, rhs );
    }
};

} // detail

template< typename Lhs, typename Rhs >
inline void add_point( Lhs& lhs, Rhs const& rhs )
{
    namespace bg = ::boost::geometry;
    static_assert( bg::dimension< Lhs >::value == bg::dimension< Rhs >::value, "dimension must be same value." );
    constexpr std::size_t dimension = bg::dimension< Lhs >::value;
    detail::add_point< 0, dimension >::impl( lhs, rhs );
}

} // geometry
} // noer
} // geometry

#endif
