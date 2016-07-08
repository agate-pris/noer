
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_HPP

#include <boost/numeric/ublas/vector.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/cs.hpp>

namespace agate_pris {
namespace noer {
namespace collision_detection {

namespace detail {

template< std::size_t DimensionCount, std::size_t Index >
struct array_assign
{
    template< typename CoordinateType, typename ArrayType >
    static inline void apply( boost::numeric::ublas::vector< CoordinateType, ArrayType >& values, CoordinateType const& value )
    {
        values( Index ) = value;
    }
};

template<> struct array_assign< 2, 2 >
{
    template< typename CoordinateType, typename ArrayType >
    static inline void apply( boost::numeric::ublas::vector< CoordinateType, ArrayType >&, CoordinateType const& ) {}
};

template<> struct array_assign< 1, 1 >
{
    template< typename CoordinateType, typename ArrayType >
    static inline void apply( boost::numeric::ublas::vector< CoordinateType, ArrayType >&, CoordinateType const& ) {}
};

template<> struct array_assign< 1, 2 >
{
    template< typename CoordinateType, typename ArrayType >
    static inline void apply( boost::numeric::ublas::vector< CoordinateType, ArrayType >&, CoordinateType const& ) {}
};

} // detail

namespace point_hide {

template
<
    typename CoordinateType,
    std::size_t DimensionCount,
    typename ArrayType = boost::numeric::ublas::bounded_array
    < CoordinateType, DimensionCount >
>
class point : public boost::numeric::ublas::vector< CoordinateType, ArrayType >
{
    public:
    point()
        : boost::numeric::ublas::vector< CoordinateType, ArrayType >( DimensionCount )
    {}

    /// @brief Constructor to set one value
    explicit inline point( CoordinateType const& v0 )
        : boost::numeric::ublas::vector< CoordinateType, ArrayType >( DimensionCount )
    {
        detail::array_assign< DimensionCount, 0 >::apply( *this, v0 );
        detail::array_assign< DimensionCount, 1 >::apply( *this, CoordinateType() );
        detail::array_assign< DimensionCount, 2 >::apply( *this, CoordinateType() );
    }

    /// @brief Constructor to set two values
    inline point( CoordinateType const& v0, CoordinateType const& v1 )
        : boost::numeric::ublas::vector< CoordinateType, ArrayType >( DimensionCount )
    {
        detail::array_assign< DimensionCount, 0 >::apply( *this, v0 );
        detail::array_assign< DimensionCount, 1 >::apply( *this, v1 );
        detail::array_assign< DimensionCount, 2 >::apply( *this, CoordinateType() );
    }

    /// @brief Constructor to set three values
    inline point( CoordinateType const& v0, CoordinateType const& v1, CoordinateType const& v2 )
        : boost::numeric::ublas::vector< CoordinateType, ArrayType >( DimensionCount )
    {
        detail::array_assign< DimensionCount, 0 >::apply( *this, v0 );
        detail::array_assign< DimensionCount, 1 >::apply( *this, v1 );
        detail::array_assign< DimensionCount, 2 >::apply( *this, v2 );
    }

    /// @brief Copy constructor
    inline point( const point& p )
        // cause error C4996 in Microsoft Visual C++
        // : m_values( p.m_values )
    {
        // this is fine
        *this = p;
    }

    /// @brieft \~english  Get a coordinate
    ///         \~japanese 座標を取得する
    /// @tparam Index \~english  coordinate to get
    ///               \~japanese 取得する座標
    /// @return \~english  the coordinate
    ///         \~japanese 座標
    template< unsigned int Index >
    inline CoordinateType const& get() const
    {
        static_assert( Index < DimensionCount, "Index < DimensionCount must be true." );
        return operator()( Index );
    }

    /// @brief  \~english  Get vector implemented by Boost.uBLAS.
    ///         \~japanese Boost.uBLASによって実装されたベクターを取得する
    /// @return \~english  the vector of coordinates
    ///         \~japanese 座標ベクトル
    /// @{
    inline boost::numeric::ublas::vector< CoordinateType, ArrayType > const& get() const
    {
        return m_values;
    }
    inline boost::numeric::ublas::vector< CoordinateType, ArrayType >&       get()
    {
        return m_values;
    }
    /// @}

    /// @brief        \~english  Set a coordinate
    ///               \~japanese 座標を設定
    /// @tparam Index \~english  coordinate to set
    ///               \~japanese 設定する座標
    /// @param value  \~english  value to set
    ///               \~japanese セットする値
    template< std::size_t Index >
    void set( CoordinateType const& value )
    {
        static_assert( Index < DimensionCount, "Index < DimensionCount must be true." );
        operator()( Index ) = value;
    }

    /// @brief        \~english  Set coordinates vector
    ///               \~japanese 座標ベクトルを設定
    /// @param values \~english  coordinates vector to set
    ///               \~japanese 設定する座標ベクトル
    void set( CoordinateType const& values )
    {
        m_values = values;
    }
};

} // point_hide

using point_hide::point;

} // collision_detection
} // noer
} // agate_pris

// Adapt to Boost.Geometry
namespace boost {
namespace geometry {
namespace traits {

template< typename CoordinateType, std::size_t DimensionCount, typename ArrayType >
struct tag< agate_pris::noer::collision_detection::point< CoordinateType, DimensionCount, ArrayType > >
{
    using type = boost::geometry::point_tag;
};

template< typename CoordinateType, std::size_t DimensionCount, typename ArrayType >
struct coordinate_type< agate_pris::noer::collision_detection::point< CoordinateType, DimensionCount, ArrayType > >
{
    using type = CoordinateType;
};

template< typename CoordinateType, std::size_t DimensionCount, typename ArrayType >
struct coordinate_system< agate_pris::noer::collision_detection::point< CoordinateType, DimensionCount, ArrayType > >
{
    using type = boost::geometry::cs::cartesian;
};

template< typename CoordinateType, std::size_t DimensionCount, typename ArrayType >
struct dimension
<
    agate_pris::noer::collision_detection::point
    <
        CoordinateType,
        DimensionCount,
        ArrayType
    >
>
    : boost::mpl::int_< DimensionCount >
{};

template< typename CoordinateType, std::size_t DimensionCount, typename ArrayType, std::size_t Dimension >
struct access
<
    agate_pris::noer::collision_detection::point< CoordinateType, DimensionCount, ArrayType >,
    Dimension
>
{
    static inline CoordinateType get( agate_pris::noer::collision_detection::point< CoordinateType, DimensionCount, ArrayType > const& p )
    {
        return p.template get< Dimension >();
    }
    static inline void set( agate_pris::noer::collision_detection::point< CoordinateType, DimensionCount, ArrayType >& p, const CoordinateType& value )
    {
        p.template set< Dimension >( value );
    }
};

} // traits
} // geometry
} // boost

#endif
