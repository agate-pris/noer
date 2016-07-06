
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_SHARED_POINT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_SHARED_POINT_HPP

#include <utility>
#include <memory>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace agate_pris {
namespace noer {
namespace collision_detection {

/// @brief \~english class for share point using  `std::shared_ptr`
/// \~japanese `std::shared_ptr` によって座標を共有するクラス
template< typename PointType >
struct point_shared
{
    std::shared_ptr< PointType > ptr;

    /// @brief \~english default constructor
    /// \~japanese デフォルトコンストラクタ
    constexpr explicit point_shared() noexcept {};

    /// @brief \~english constructor for initialize `shared_ptr`
    /// \~japanese shared_ptr を初期化するコンストラクタ
    /// @{
    template
    <
        typename Arg,
        typename = std::enable_if_t
        <
            !std::is_base_of
            <
                point_shared< PointType >,
                std::decay_t< Arg >
            >::value
        >
    >
    point_shared( Arg&& arg )
    : ptr( std::forward< Arg >( arg ) )
    {}

    template< typename First, typename Second, typename... Tail >
    inline point_shared( First&& first, Second&& second, Tail&&... tail )
    : ptr
    (
        std::forward< First >( first ),
        std::forward< Second >( second ),
        std::forward< Tail >( tail )...
    )
    {}
    /// @}
};

} // collision_detection
} // noer
} // agate_pris

namespace boost {
namespace geometry {
namespace traits {

template< typename PointType >
struct tag< agate_pris::noer::collision_detection::point_shared< PointType > >
{
    using type = point_tag;
};

template< typename PointType >
struct coordinate_type< agate_pris::noer::collision_detection::point_shared< PointType > >
{
    using type = typename coordinate_type< PointType >::type;
};

template< typename PointType >
struct coordinate_system< agate_pris::noer::collision_detection::point_shared< PointType > >
{
    using type = typename coordinate_system< PointType >::type;
};

template< typename PointType >
struct dimension< agate_pris::noer::collision_detection::point_shared< PointType > >
{
    static constexpr const std::size_t value = dimension< PointType >::value;
};

template< typename PointType, std::size_t Dimension >
struct access< agate_pris::noer::collision_detection::point_shared< PointType >, Dimension >
{
    static inline decltype( auto ) get( agate_pris::noer::collision_detection::point_shared< PointType > const& p )
    {
        if( !p.ptr ) throw;
        return geometry::get< Dimension >( *( p.ptr ) );
    }

    static inline void set
    (
        agate_pris::noer::collision_detection::point_shared< PointType >& p,
        typename coordinate_type< PointType >::type const& value
    )
    {
        if( !p.ptr ) throw;
        geometry::set< Dimension >( *( p.ptr ), value );
    }
};

} // traits
} // geometry
} // boost

#endif
