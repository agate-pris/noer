
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

template< eval Eval, std::size_t Begin, std::size_t End, bool IsLast = ( Begin + 1 ) == End, bool IsEnd = Begin == End >
struct eval_point;

template< eval Eval, std::size_t Begin, std::size_t End >
struct eval_point< Eval, Begin, End, false, true >
{
    template< typename Lhs, typename Rhs >
    static void impl( Lhs&, Rhs const& ) {}
};

template< eval Eval, std::size_t Begin, std::size_t End >
struct eval_point< Eval, Begin, End, true, false >
{
    template< typename Lhs, typename Rhs >
    static void impl( Lhs& lhs, Rhs const& rhs )
    {
        eval_value< Eval, Begin, Lhs, typename param< Rhs >::type >::impl
        ( lhs, boost::geometry::get< Begin >( rhs ) );
    }
};

template< eval Eval, std::size_t Begin, std::size_t End >
struct eval_point< Eval, Begin, End, false, false >
{
    template< typename Lhs, typename Rhs >
    static void impl( Lhs& lhs, Rhs const& rhs )
    {
        constexpr std::size_t border = ( Begin + End ) / 2;
        eval_point< Eval, Begin,  border >::impl( lhs, rhs );
        eval_point< Eval, border, End    >::impl( lhs, rhs );
    }
};

} // detail

template< eval Eval, typename Lhs, typename Rhs >
inline void eval_point( Lhs& lhs, Rhs const& rhs )
{
    namespace bg = ::boost::geometry;
    static_assert( bg::dimension< Lhs >::value == bg::dimension< Rhs >::value, "dimension must be same value." );
    constexpr std::size_t dimension = bg::dimension< Lhs >::value;
    detail::eval_point< Eval, 0, dimension >::impl( lhs, rhs );
}

template< typename Lhs, typename Rhs >
inline void add_point( Lhs& lhs, Rhs const& rhs )
{
    eval_point< eval::add >( lhs, rhs );
}

template< typename Lhs, typename Rhs >
inline void subtract_point( Lhs& lhs, Rhs const& rhs )
{
    eval_point< eval::sub >( lhs, rhs );
}

} // geometry
} // noer
} // geometry

#endif
