
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_SHARED_POINT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_SHARED_POINT_HPP

#include <utility>
#include <memory>
#include <boost/config.hpp>
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
template< typename Point >
class point_shared
{
    // type
    using element_type   = Point;
    using shared_pointer = std::shared_ptr< element_type >;

    // variable
    private:
    shared_pointer m_ptr;

    // constructor
    public:
    // construct empty shared_ptr
    BOOST_CONSTEXPR point_shared() BOOST_NOEXCEPT_OR_NOTHROW;

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
                point_shared< Point >,
                std::decay_t< Arg >
            >::value
        >
    >
    point_shared( Arg&& arg )
    : m_ptr( std::forward< Arg >( arg ) )
    {}

    template< typename First, typename Second, typename... Tail >
    inline point_shared( First&& first, Second&& second, Tail&&... tail )
    : m_ptr
    (
        std::forward< First >( first ),
        std::forward< Second >( second ),
        std::forward< Tail >( tail )...
    )
    {}
    /// @}
};

// construct empty shared_ptr
template< typename Point >
inline point_shared< Point >::point_shared() {}

} // collision_detection
} // noer
} // agate_pris

namespace boost {
namespace geometry {
namespace traits {

template< typename Point >
struct tag< agate_pris::noer::collision_detection::point_shared< Point > >
{
    using type = point_tag;
};

template< typename Point >
struct coordinate_type< agate_pris::noer::collision_detection::point_shared< Point > >
{
    using type = typename coordinate_type< Point >::type;
};

template< typename Point >
struct coordinate_system< agate_pris::noer::collision_detection::point_shared< Point > >
{
    using type = typename coordinate_system< Point >::type;
};

template< typename Point >
struct dimension< agate_pris::noer::collision_detection::point_shared< Point > >
{
    static constexpr const std::size_t value = dimension< Point >::value;
};

template< typename Point, std::size_t Dimension >
struct access< agate_pris::noer::collision_detection::point_shared< Point >, Dimension >
{
    static inline decltype( auto ) get( agate_pris::noer::collision_detection::point_shared< Point > const& p )
    {
        if( !p.m_ptr ) throw;
        return geometry::get< Dimension >( *( p.m_ptr ) );
    }

    static inline void set
    (
        agate_pris::noer::collision_detection::point_shared< Point >& p,
        typename coordinate_type< Point >::type const& value
    )
    {
        if( !p.m_ptr ) throw;
        geometry::set< Dimension >( *( p.m_ptr ), value );
    }
};

} // traits
} // geometry
} // boost

#endif
