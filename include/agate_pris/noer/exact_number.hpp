﻿
#ifndef AGATE_PRIS_NOER_EXACT_NUMBER_HPP
#define AGATE_PRIS_NOER_EXACT_NUMBER_HPP

#include <type_traits>
#include <limits>
#include <boost/type_traits/has_operator.hpp>
#include <boost/mpl/bool.hpp>
#include <agate_pris/noer/config/deprecated.hpp>

namespace agate_pris {
namespace noer {

// forward declation for free function
template< typename Repr > class exact_number;

// hide a function from ADL
namespace exact_number_hide {

template< typename Repr >
struct get_impl
{
    static inline auto const& get( exact_number< Repr > const& n );
    static inline auto&       get( exact_number< Repr >&       n );
};

/// @brief \~japanese `exact_number` の内部表現にアクセス
///        \~english  access to the internal representation of `exact_number`

/// @attention \~japanese この関数はADLによって発見されない。
///            \~english  This function cannnod be found by ADL.

/// @details \~japanese 以下のように呼び出す。
///          \~english  call as below.
/// \~
/// ~~~{.cpp}
/// auto i = agate_pris::noer::get( num );
/// ~~~

/// @relates agate_pris::noer::exact_number

/// @{
template< typename Repr >
inline auto const& get( exact_number< Repr > const& n )
{
    return get_impl< Repr >::get( n );
}
template< typename Repr >
inline auto& get( exact_number< Repr >& n )
{
    return get_impl< Repr >::get( n );
}
/// @}

/// @brief \~japanese 任意の型への変換
///        \~english  conversion to any type

/// @attention \~japanese
/// この関数は変換先の型が厳密な数値型であるか否かを問わない。
/// 厳密な数値演算が必要な時、型合わせのためだけに本関数を使用してはならない。
/// この関数はADLによって発見されない。
/// \~english
/// This funtion does not matter weather destination type of conversion is exact or not.
/// It should never be used only for type matching when exact arithmetic operation is necessary.
/// This function cannnod be found by ADL.

/// @details \~japanese 以下の式によって型変換を行う。
///          \~english  convet by following expression.
/// \~
/// ~~~{.cpp}
/// return static_cast< Target >( m_repr );
/// ~~~
/// \~japanese 以下のように呼び出す。
/// \~english  call as below.
/// \~
/// ~~~{.cpp}
/// auto x = agate_pris::noer::convert_to< int >( num );
/// ~~~

/// @relates agate_pris::noer::exact_number
template< typename Target, typename Repr >
inline auto convert_to( exact_number< Repr > const& n )
{
    return static_cast< Target >( get( n ) );
}

template< typename Target, typename Source >
inline auto convert_to( Source const& s )
{
    return static_cast< Target >( s );
}

} // exact_number_hide

namespace detail {
namespace exact_number {

// check all args are exact
// ---------------------------------------------------------------------

template< typename... Args >
struct check;

template< typename Last >
struct check< Last >
: boost::mpl::bool_< std::numeric_limits< Last >::is_exact >
{};

template< typename First, typename Second, typename... Tail >
struct check< First, Second, Tail... >
: boost::mpl::bool_
<
    std::numeric_limits< First >::is_exact &&
    check< Second, Tail... >::value
>
{};

} // exact_number
} // detail

/// @class exact_number

/// @brief \~japanese 厳密な数値を取り扱うためのクラステンプレート
///        \~english  class template for traiting exact numbers

/// @attention \~japanese `numeric_limits< Repr >::is_exact` は `true` でなければならない。
///            \~english  `numeric_limits< Repr >::is_exact` must be `true` .

/// @tparam Repr \~japanese 内部で保持する値を表現する型
///              \~english  represent number as implemention

/// @details \~japanese `exact_number` は以下のように使う  
///          \~english  Use `exact_number` like this
///          \~
/// ~~~{.cpp}
/// exact_number< int > v;
/// ~~~
template< typename Repr >
class exact_number
{
    friend exact_number_hide::get_impl< Repr >;
    private:
    Repr m_repr;
    public:
    /// @brief \~japanese テンプレート引数 `Repr` の using declation
    ///        \~english  declation of template argument `Repr`
    using value_type = Repr;

    // default constructor
    exact_number() = default;

    // copy and move constructor and operator
    exact_number( exact_number< Repr > const& ) = default;
    exact_number( exact_number< Repr >&& ) = default;
    exact_number< Repr >& operator = ( exact_number< Repr > const& ) = default;
    exact_number< Repr >& operator = ( exact_number< Repr >&& ) = default;

    // conversion from the other exact_number
    template< typename Arg >
    exact_number( exact_number< Arg > const& arg );
    template< typename Rhs >
    exact_number< Repr >& operator = ( exact_number< Rhs > const& rhs );

    // conversion from any types
    template< typename Arg, typename = std::enable_if_t< detail::exact_number::check< Arg >::value > >
    exact_number( Arg const& arg )
    : m_repr( arg )
    {}
    template< typename Arg, typename = std::enable_if_t< detail::exact_number::check< Arg >::value > >
    exact_number< Repr >& operator = ( Arg const& arg )
    {
        m_repr = arg;
        return *this;
    }

    // conversion to any exact number
    template< typename T, typename = std::enable_if_t< std::numeric_limits< T >::is_exact > >
    AGATE_PRIS_NOER_DEPRECATED operator T() const
    {
        return static_cast< T >( m_repr );
    }

    //@{
    template< typename Rhs >
    exact_number< Repr >& operator += ( Rhs const& rhs );
    template< typename Rhs >
    exact_number< Repr >& operator -= ( Rhs const& rhs );
    template< typename Rhs >
    exact_number< Repr >& operator *= ( Rhs const& rhs );
    template< typename Rhs >
    exact_number< Repr >& operator /= ( Rhs const& rhs );
    //@}

    /// @brief \~japanese `exact_number< Repr >` との算術複合代入演算子
    ///        \~english  Arithmetic assignment operators with `exact_number< Repr >`

    /// @{
    template< typename Rhs > exact_number& operator += ( exact_number< Rhs > const& r ) { m_repr += get( r ); return *this; }
    template< typename Rhs > exact_number& operator -= ( exact_number< Rhs > const& r ) { m_repr -= get( r ); return *this; }
    template< typename Rhs > exact_number& operator *= ( exact_number< Rhs > const& r ) { m_repr *= get( r ); return *this; }
    template< typename Rhs > exact_number& operator /= ( exact_number< Rhs > const& r ) { m_repr /= get( r ); return *this; }
    /// @}
};

/// @brief \~english  produces the value of its operand
///        \~japanese オペランドの値を生成
template< typename Repr >
std::enable_if_t< boost::has_unary_plus< Repr >::value, exact_number< Repr > >
operator + ( exact_number< Repr > const& arg )
{
    return exact_number< Repr >( +get( arg ) );
}

/// @brief \~english  produces the negative of its operand
///        \~japanese オペランドの負数を生成
template< typename Repr >
std::enable_if_t< boost::has_unary_minus< Repr >::value, exact_number< Repr > >
operator - ( exact_number< Repr > const& arg )
{
    return exact_number< Repr >( -get( arg ) );
}

namespace exact_number_hide {

template< typename Repr >
auto& get_impl< Repr >::get( exact_number< Repr >& num )
{
    return num.m_repr;
}
template< typename Repr >
auto const& get_impl< Repr >::get( exact_number< Repr > const& num )
{
    return num.m_repr;
}

} // exact_number_hide

using exact_number_hide::get;
using exact_number_hide::convert_to;

/// @brief \~japanese テンプレート引数 `Repr` の異なる `exact_number` 用コンストラクタ
///        \~english  constructor for `exact_number` with different template argument `Repr`

/// @details \~japanese メンバ変数 `m_repr` は以下の式によって初期化される。
///          \~english  member variable `m_repr` is initialized by the following expression.
///          \~
/// ~~~{.cpp}
/// m_repr( static_cast< Repr >( arg ) )
/// ~~~
template< typename Repr >
template< typename Arg >
exact_number< Repr >::exact_number( exact_number< Arg > const& arg )
    : m_repr( convert_to< Repr >( arg ) )
{}

/// @brief \~japanese テンプレート引数 `Repr` の異なる `exact_number` 用コピー代入演算子
///        \~english  copy assignment operator for `exact_number` with different template argument `Repr`

/// @details \~japanese 以下の式によって引数 `rhs` をメンバ変数 `m_repr` に代入する。
///          \~english  assign argument rhs for member variable `m_repr` by the following expression.
///          \~
/// ~~~{.cpp}
/// m_repr = static_cast< Repr >( arg );
/// ~~~
template< typename Repr >
template< typename Rhs >
exact_number< Repr >& exact_number< Repr >::operator = ( exact_number< Rhs > const& arg )
{
    m_repr = static_cast< Repr >( arg );
    return *this;
}

/// @brief \~english compound assignment operator except for `exact_number`
/// \~japanese `exact_number` 以外との複合代入演算子
/// @attention \~english  `numeric_limits< Rhs >::is_exact` must be `true` .
/// \~japanese `numeric_limits< Rhs >::is_exact` は `true` でなければならない。
/// @param rhs \~english  right hand side
/// \~japanese 右辺
/// @tparam Rhs \~english  type of right hand side
/// \~japanese 右辺の型
/// @{
template< typename Repr >
template< typename Rhs >
exact_number< Repr >& exact_number< Repr >::operator += ( Rhs const& rhs )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
    m_repr += rhs;
    return *this;
}
template< typename Repr >
template< typename Rhs >
exact_number< Repr >& exact_number< Repr >::operator -= ( Rhs const& rhs )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
    m_repr -= rhs;
    return *this;
}
template< typename Repr >
template< typename Rhs >
exact_number< Repr >& exact_number< Repr >::operator *= ( Rhs const& rhs )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
    m_repr *= rhs;
    return *this;
}
template< typename Repr >
template< typename Rhs >
exact_number< Repr >& exact_number< Repr >::operator /= ( Rhs const& rhs )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
    m_repr /= rhs;
    return *this;
}
/// @}

/// @relates agate_pris::noer::exact_number

/// @brief \~japanese 基本型または `exact_number` と `exact_number` の演算
///        \~english  operation for fundamental type or `exact_number` and `exact_number

/// @attention \~japanese `numeric_limits< Lhs >::is_exact` または同 `Rhs` は `true` でなければならない。
///            \~english  `numeric_limits< Lhs >::is_exact` or same of `Rhs` must be `true` .

/// @param lhs \~japanese 左辺
///            \~english  left hand side

/// @param rhs \~japanese 右辺
///            \~english  right hand side

/// @tparam Lhs \~japanese 左辺の型またはそのメンバの型
///             \~english  type of left hand side or member of it

/// @tparam Rhs \~japanese 右辺の型またはそのメンバの型
///             \~english  type of right hand side or member of it

/// @details \~japanese 戻り値の型は演算結果を保持する `exact_number` になる。
///          \~english  Return value type is `exact_number` holding result type of arithmetic operation.

/// @{
template< typename Lhs, typename Rhs >
auto operator + ( Lhs const& lhs, exact_number< Rhs > const& rhs ) -> exact_number< decltype( std::declval< Lhs >() + std::declval< Rhs >() ) >
{
    static_assert( std::numeric_limits< Lhs >::is_exact, "Lhs must be exact!" );
    return exact_number< decltype( std::declval< Lhs >() + std::declval< Rhs >() ) >( lhs + get( rhs ) );
}
template< typename Lhs, typename Rhs >
auto operator - ( Lhs const& lhs, exact_number< Rhs > const& rhs ) -> exact_number< decltype( std::declval< Lhs >() - std::declval< Rhs >() ) >
{
    static_assert( std::numeric_limits< Lhs >::is_exact, "Lhs must be exact!" );
    return exact_number< decltype( std::declval< Lhs >() - std::declval< Rhs >() ) >( lhs - get( rhs ) );
}
template< typename Lhs, typename Rhs >
auto operator * ( Lhs const& lhs, exact_number< Rhs > const& rhs ) -> exact_number< decltype( std::declval< Lhs >() * std::declval< Rhs >() ) >
{
    static_assert( std::numeric_limits< Lhs >::is_exact, "Lhs must be exact!" );
    return exact_number< decltype( std::declval< Lhs >() * std::declval< Rhs >() ) >( lhs * get( rhs ) );
}
template< typename Lhs, typename Rhs >
auto operator / ( Lhs const& lhs, exact_number< Rhs > const& rhs ) -> exact_number< decltype( std::declval< Lhs >() / std::declval< Rhs >() ) >
{
    static_assert( std::numeric_limits< Lhs >::is_exact, "Lhs must be exact!" );
    return exact_number< decltype( std::declval< Lhs >() / std::declval< Rhs >() ) >( lhs / get( rhs ) );
}

template< typename Lhs, typename Rhs >
auto operator + ( exact_number< Lhs > const& lhs, Rhs const& rhs ) -> exact_number< decltype( std::declval< Lhs >() + std::declval< Rhs >() ) >
{
    static_assert( std::numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
    return exact_number< decltype( std::declval< Lhs >() + std::declval< Rhs >() ) >( get( lhs ) + rhs );
}
template< typename Lhs, typename Rhs >
auto operator - ( exact_number< Lhs > const& lhs, Rhs const& rhs ) -> exact_number< decltype( std::declval< Lhs >() - std::declval< Rhs >() ) >
{
    static_assert( std::numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
    return exact_number< decltype( std::declval< Lhs >() - std::declval< Rhs >() ) >( get( lhs ) - rhs );
}
template< typename Lhs, typename Rhs >
auto operator * ( exact_number< Lhs > const& lhs, Rhs const& rhs ) -> exact_number< decltype( std::declval< Lhs >() * std::declval< Rhs >() ) >
{
    static_assert( std::numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
    return exact_number< decltype( std::declval< Lhs >() * std::declval< Rhs >() ) >( get( lhs ) * rhs );
}
template< typename Lhs, typename Rhs >
auto operator / ( exact_number< Lhs > const& lhs, Rhs const& rhs ) -> exact_number< decltype( std::declval< Lhs >() / std::declval< Rhs >() ) >
{
    static_assert( std::numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
    return exact_number< decltype( std::declval< Lhs >() / std::declval< Rhs >() ) >( get( lhs ) / rhs );
}

template< typename Lhs, typename Rhs >
auto operator + ( exact_number< Lhs > const& lhs, exact_number< Rhs > const& rhs ) -> exact_number< decltype( std::declval< Lhs >() + std::declval< Rhs >() ) >
{
    return exact_number< decltype( std::declval< Lhs >() + std::declval< Rhs >() ) >( get( lhs ) + get( rhs ) );
}
template< typename Lhs, typename Rhs >
auto operator - ( exact_number< Lhs > const& lhs, exact_number< Rhs > const& rhs ) -> exact_number< decltype( std::declval< Lhs >() - std::declval< Rhs >() ) >
{
    return exact_number< decltype( std::declval< Lhs >() - std::declval< Rhs >() ) >( get( lhs ) - get( rhs ) );
}
template< typename Lhs, typename Rhs >
auto operator * ( exact_number< Lhs > const& lhs, exact_number< Rhs > const& rhs ) -> exact_number< decltype( std::declval< Lhs >() * std::declval< Rhs >() ) >
{
    return exact_number< decltype( std::declval< Lhs >() * std::declval< Rhs >() ) >( get( lhs ) * get( rhs ) );
}
template< typename Lhs, typename Rhs >
auto operator / ( exact_number< Lhs > const& lhs, exact_number< Rhs > const& rhs ) -> exact_number< decltype( std::declval< Lhs >() / std::declval< Rhs >() ) >
{
    return exact_number< decltype( std::declval< Lhs >() / std::declval< Rhs >() ) >( get( lhs ) / get( rhs ) );
}
/// @}

// 比較演算子
// Comparison operators
// =====================================================================

// operator <
// ---------------------------------------------------------------------
template< typename Lhs, typename Rhs >
bool operator < ( exact_number< Lhs > const& l, exact_number< Rhs > const& r )
{
    return get( l ) < get( r );
}
template< typename Lhs, typename Rhs >
bool operator < ( exact_number< Lhs > const& l, Rhs const& r )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact." );
    return get( l ) < r;
}
template< typename Lhs, typename Rhs >
bool operator < ( Lhs const& l, exact_number< Rhs > const& r )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Lhs >::is_exact, "Lhs must be exact." );
    return l < get( r );
}

// operator >
// ---------------------------------------------------------------------
template< typename Lhs, typename Rhs >
bool operator > ( exact_number< Lhs > const& l, exact_number< Rhs > const& r )
{
    return r < l;
}
template< typename Lhs, typename Rhs >
bool operator > ( exact_number< Lhs > const& l, Rhs const& r )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact." );
    return r < l;
}
template< typename Lhs, typename Rhs >
bool operator > ( Lhs const& l, exact_number< Rhs > const& r )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Lhs >::is_exact, "Lhs must be exact." );
    return r < l;
}

// operator >=
// ---------------------------------------------------------------------
template< typename Lhs, typename Rhs >
bool operator >= ( exact_number< Lhs > const& l, exact_number< Rhs > const& r )
{
    return !( l < r );
}
template< typename Lhs, typename Rhs >
bool operator >= ( exact_number< Lhs > const& l, Rhs const& r )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact." );
    return !( l < r );
}
template< typename Lhs, typename Rhs >
bool operator >= ( Lhs const& l, exact_number< Rhs > const& r )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Lhs >::is_exact, "Lhs must be exact." );
    return !( l < r );
}

// operator <=
// ---------------------------------------------------------------------
template< typename Lhs, typename Rhs >
bool operator <= ( exact_number< Lhs > const& l, exact_number< Rhs > const& r )
{
    return !( l > r );
}
template< typename Lhs, typename Rhs >
bool operator <= ( exact_number< Lhs > const& l, Rhs const& r )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact." );
    return !( l > r );
}
template< typename Lhs, typename Rhs >
bool operator <= ( Lhs const& l, exact_number< Rhs > const& r )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Lhs >::is_exact, "Lhs must be exact." );
    return !( l > r );
}

// operator ==
// ---------------------------------------------------------------------
template< typename Lhs, typename Rhs >
bool operator == ( exact_number< Lhs > const& l, exact_number< Rhs > const& r )
{
    return get( l ) == get( r );
}
template< typename Lhs, typename Rhs >
bool operator == ( exact_number< Lhs > const& l, Rhs const& r )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact." );
    return get( l ) == r;
}
template< typename Lhs, typename Rhs >
bool operator == ( Lhs const& l, exact_number< Rhs > const& r )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Lhs >::is_exact, "Lhs must be exact." );
    return l == get( r );
}

// operator !=
// ---------------------------------------------------------------------
template< typename Lhs, typename Rhs >
bool operator != ( exact_number< Lhs > const& l, exact_number< Rhs > const& r )
{
    return !( l == r );
}
template< typename Lhs, typename Rhs >
bool operator != ( exact_number< Lhs > const& l, Rhs const& r )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact." );
    return !( l == r );
}
template< typename Lhs, typename Rhs >
bool operator != ( Lhs const& l, exact_number< Rhs > const& r )
{
    using std::numeric_limits;
    static_assert( numeric_limits< Lhs >::is_exact, "Lhs must be exact." );
    return !( l == r );
}

} // noer
} // agate_pris

#endif
