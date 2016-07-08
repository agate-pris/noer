
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_SHARED_POINT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_SHARED_POINT_HPP

#include <utility>
#include <memory>
#include <cstddef>
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
    // construct empty shared_ptr
    BOOST_CONSTEXPR point_shared( std::nullptr_t ) BOOST_NOEXCEPT_OR_NOTHROW;

    // construct shared_ptr object that owns same resource as r
    point_shared( point_shared< Point > const& r ) BOOST_NOEXCEPT_OR_NOTHROW;

    // public function
    public:
    shared_pointer const& data() const BOOST_NOEXCEPT_OR_NOTHROW;
    shared_pointer&       data() BOOST_NOEXCEPT_OR_NOTHROW;
};

// construct empty shared_ptr
template< typename Point >
inline point_shared< Point >::point_shared() {}

// construct empty shared_ptr
template< typename Point >
inline point_shared< Point >::point_shared( std::nullptr_t ) {}

// construct shared_ptr object that owns same resource as r
template< typename Point >
inline point_shared< Point >::point_shared( point_shared< Point > const& r )
    : m_ptr( r.data() )
{}

// public function
// ---------------------------------------------------------------------

// get shared_ptr const reference
template< typename Point >
inline point_shared< Point >::shared_pointer const& point_shared< Point >::data() const
{
    return m_ptr;
}

// get shared_ptr reference
template< typename Point >
inline point_shared< Point >::shared_pointer& point_shared< Point >::data()
{
    return m_ptr;
}

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
