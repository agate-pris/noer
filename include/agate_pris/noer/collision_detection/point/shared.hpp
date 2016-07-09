
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_HPP

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
namespace point {
namespace shared {

template< typename Point >
class entity
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
    BOOST_CONSTEXPR entity() BOOST_NOEXCEPT_OR_NOTHROW;
    // construct empty shared_ptr
    BOOST_CONSTEXPR entity( std::nullptr_t ) BOOST_NOEXCEPT_OR_NOTHROW;

    // construct shared_ptr object that owns same resource as r
    entity( entity< Point > const& r ) BOOST_NOEXCEPT_OR_NOTHROW;
    // construct shared_ptr object that takes resource from r
    entity( entity< Point >&& r ) BOOST_NOEXCEPT_OR_NOTHROW;

    // construct shared_ptr object that owns same resource as r
    entity( shared_pointer const& r ) BOOST_NOEXCEPT_OR_NOTHROW;
    // construct shared_ptr object that takes resource from r
    entity( shared_pointer&& r ) BOOST_NOEXCEPT_OR_NOTHROW;

    // public function
    public:
    shared_pointer const& data() const BOOST_NOEXCEPT_OR_NOTHROW;
    shared_pointer&       data() BOOST_NOEXCEPT_OR_NOTHROW;

    // check if owns managed object
    explicit operator bool() const BOOST_NOEXCEPT_OR_NOTHROW;
};

// construct empty shared_ptr
template< typename Point >
inline entity< Point >::entity() BOOST_NOEXCEPT_OR_NOTHROW {}

// construct empty shared_ptr
template< typename Point >
inline entity< Point >::entity( std::nullptr_t ) BOOST_NOEXCEPT_OR_NOTHROW {}

// construct shared_ptr object that owns same resource as r
template< typename Point >
inline entity< Point >::entity( entity< Point > const& r ) BOOST_NOEXCEPT_OR_NOTHROW
    : m_ptr( r.data() )
{}

// construct shared_ptr object that takes resource from r
template< typename Point >
inline entity< Point >::entity( entity< Point >&& r ) BOOST_NOEXCEPT_OR_NOTHROW
    : m_ptr( std::move( r.data() ) )
{}

// construct shared_ptr object that owns same resource as r
template< typename Point >
inline entity< Point >::entity( shared_pointer const& r ) BOOST_NOEXCEPT_OR_NOTHROW
    : m_ptr( r )
{}

// construct shared_ptr object that takes resource from r
template< typename Point >
inline entity< Point >::entity( shared_pointer&& r ) BOOST_NOEXCEPT_OR_NOTHROW
    : m_ptr( std::move( r ) )
{}

// public function
// ---------------------------------------------------------------------

// get shared_ptr const reference
template< typename Point >
inline typename entity< Point >::shared_pointer const& entity< Point >::data() const BOOST_NOEXCEPT_OR_NOTHROW
{
    return m_ptr;
}

// get shared_ptr reference
template< typename Point >
inline typename entity< Point >::shared_pointer& entity< Point >::data() BOOST_NOEXCEPT_OR_NOTHROW
{
    return m_ptr;
}

// check if owns managed object
template< typename Point >
inline entity< Point >::operator bool() const BOOST_NOEXCEPT_OR_NOTHROW
{
    return static_cast< bool >( m_ptr );
}

} // shared
} // point
} // collision_detection
} // noer
} // agate_pris

namespace boost {
namespace geometry {
namespace traits {

template< typename Point >
struct tag< agate_pris::noer::collision_detection::point::shared::entity< Point > >
{
    using type = point_tag;
};

template< typename Point >
struct coordinate_type< agate_pris::noer::collision_detection::point::shared::entity< Point > >
{
    using type = typename coordinate_type< Point >::type;
};

template< typename Point >
struct coordinate_system< agate_pris::noer::collision_detection::point::shared::entity< Point > >
{
    using type = typename coordinate_system< Point >::type;
};

template< typename Point >
struct dimension< agate_pris::noer::collision_detection::point::shared::entity< Point > >
{
    static constexpr const std::size_t value = dimension< Point >::value;
};

template< typename Point, std::size_t Dimension >
struct access< agate_pris::noer::collision_detection::point::shared::entity< Point >, Dimension >
{
    static inline decltype( auto ) get( agate_pris::noer::collision_detection::point::shared::entity< Point > const& p )
    {
        if( !p.m_ptr ) throw;
        return geometry::get< Dimension >( *( p.m_ptr ) );
    }

    static inline void set
    (
        agate_pris::noer::collision_detection::point::shared::entity< Point >& p,
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
