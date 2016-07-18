
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
namespace geometry {
namespace model {
namespace point {
namespace shared {

template< typename Point, typename Getter, typename Setter >
class entity
{
    // type
    public:
    using coordinate_type = typename boost::geometry::coordinate_type< Point >::type;
    using element_type    = Point;
    using shared_pointer  = std::shared_ptr< element_type >;

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
    entity( entity< Point, Getter, Setter > const& r ) BOOST_NOEXCEPT_OR_NOTHROW;
    // construct shared_ptr object that takes resource from r
    entity( entity< Point, Getter, Setter >&& r ) BOOST_NOEXCEPT_OR_NOTHROW;

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

    // get coordinate value
    template< std::size_t Dimension >
    coordinate_type get() const;

    // set coordiante value
    template< std::size_t Dimension >
    void set( coordinate_type const& );
};

// construct empty shared_ptr
template< typename Point, typename Getter, typename Setter >
inline entity< Point, Getter, Setter >::entity() BOOST_NOEXCEPT_OR_NOTHROW {}

// construct empty shared_ptr
template< typename Point, typename Getter, typename Setter >
inline entity< Point, Getter, Setter >::entity( std::nullptr_t ) BOOST_NOEXCEPT_OR_NOTHROW {}

// construct shared_ptr object that owns same resource as r
template< typename Point, typename Getter, typename Setter >
inline entity< Point, Getter, Setter >::entity( entity< Point, Getter, Setter > const& r ) BOOST_NOEXCEPT_OR_NOTHROW
    : m_ptr( r.data() )
{}

// construct shared_ptr object that takes resource from r
template< typename Point, typename Getter, typename Setter >
inline entity< Point, Getter, Setter >::entity( entity< Point, Getter, Setter >&& r ) BOOST_NOEXCEPT_OR_NOTHROW
    : m_ptr( std::move( r.data() ) )
{}

// construct shared_ptr object that owns same resource as r
template< typename Point, typename Getter, typename Setter >
inline entity< Point, Getter, Setter >::entity( shared_pointer const& r ) BOOST_NOEXCEPT_OR_NOTHROW
    : m_ptr( r )
{}

// construct shared_ptr object that takes resource from r
template< typename Point, typename Getter, typename Setter >
inline entity< Point, Getter, Setter >::entity( shared_pointer&& r ) BOOST_NOEXCEPT_OR_NOTHROW
    : m_ptr( std::move( r ) )
{}

// public function
// ---------------------------------------------------------------------

// get shared_ptr const reference
template< typename Point, typename Getter, typename Setter >
inline typename entity< Point, Getter, Setter >::shared_pointer const&
entity< Point, Getter, Setter >::data() const BOOST_NOEXCEPT_OR_NOTHROW
{
    return m_ptr;
}

// get shared_ptr reference
template< typename Point, typename Getter, typename Setter >
inline typename entity< Point, Getter, Setter >::shared_pointer&
entity< Point, Getter, Setter >::data() BOOST_NOEXCEPT_OR_NOTHROW
{
    return m_ptr;
}

// check if owns managed object
template< typename Point, typename Getter, typename Setter >
inline entity< Point, Getter, Setter >::operator bool() const BOOST_NOEXCEPT_OR_NOTHROW
{
    return static_cast< bool >( m_ptr );
}

// get coordinate value
template< typename Point, typename Getter, typename Setter >
template<std::size_t Dimension>
inline typename entity< Point, Getter, Setter >::coordinate_type
entity< Point, Getter, Setter >::get() const
{
    return Getter::impl< Point, Dimension >( m_ptr );
}

// set coordiante value
template< typename Point, typename Getter, typename Setter >
template< std::size_t Dimension >
inline void entity< Point, Getter, Setter >::set( coordinate_type const& v )
{
    Setter::impl< Point, Dimension >( m_ptr, v );
}

} // shared
} // point
} // model
} // collision_detection
} // noer
} // agate_pris

namespace boost {
namespace geometry {
namespace traits {

template< typename Point, typename Getter, typename Setter >
struct tag< agate_pris::noer::geometry::model::point::shared::entity< Point, Getter, Setter > >
{
    using type = point_tag;
};

template< typename Point, typename Getter, typename Setter >
struct coordinate_type< agate_pris::noer::geometry::model::point::shared::entity< Point, Getter, Setter > >
{
    using type = typename coordinate_type< Point >::type;
};

template< typename Point, typename Getter, typename Setter >
struct coordinate_system< agate_pris::noer::geometry::model::point::shared::entity< Point, Getter, Setter > >
{
    using type = typename coordinate_system< Point >::type;
};

template< typename Point, typename Getter, typename Setter >
struct dimension< agate_pris::noer::geometry::model::point::shared::entity< Point, Getter, Setter > >
    : dimension< Point >
{};

template< typename Point, typename Getter, typename Setter, std::size_t Dimension >
struct access< agate_pris::noer::geometry::model::point::shared::entity< Point, Getter, Setter >, Dimension >
{
    static inline decltype( auto ) get( agate_pris::noer::geometry::model::point::shared::entity< Point, Getter, Setter > const& p )
    {
        return p.get< Dimension >();
    }

    static inline void set
    (
        agate_pris::noer::geometry::model::point::shared::entity< Point, Getter, Setter >& p,
        typename coordinate_type< Point >::type const& value
    )
    {
        p.set< Dimension >( value );
    }
};

} // traits
} // geometry
} // boost

#endif
