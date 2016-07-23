
#ifndef AGATE_PRIS_NOER_GEOMETRY_POLYMORPHIC_IMPLEMENT_HPP
#define AGATE_PRIS_NOER_GEOMETRY_POLYMORPHIC_IMPLEMENT_HPP

#include <agate_pris/noer/geometry/algorithms/intersects.hpp>
#include <agate_pris/noer/geometry/polymorphic_implement_fwd.hpp>
#include <agate_pris/noer/geometry/polymorphic_interface.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

namespace detail {

// subject's holder
template< typename Subject >
class holder
{
    private:
    Subject m_subject;

    public:
    Subject const& get() const { return m_subject; }
    Subject&       get() { return m_subject; }
};

// polymorphic_implement
// -------------------------------------------------------------
// declaration
template< typename Subject, typename Interface, typename... Objects >
struct polymorphic_implement;

// definition for empty Objects definition
// ---------------------------------------
template< typename Subject, typename Interface >
struct polymorphic_implement< Subject, Interface >
    : holder< Subject >
    , Interface
{
};

// definition for last
// -------------------
template< typename Subject, typename Interface, typename Last >
struct polymorphic_implement< Subject, Interface, Last >
    : holder< Subject >
    , Interface
{
    virtual bool intersects( Last const& object ) const override;
};

// definition for intersects
template< typename Subject, typename Interface, typename Last >
bool polymorphic_implement< Subject, Interface, Last >::intersects( Last const& object ) const
{
    return geometry::intersects( holder::get(), object );
}

// definition for the others
// -------------------------
template< typename Subject, typename Interface, typename Head, typename... Tail >
struct polymorphic_implement< Subject, Interface, Head, Tail... >
    : polymorphic_implement< Subject, Interface, Tail... >
{
    using polymorphic_implement< Subject, Interface, Tail... >::intersects;
    virtual bool intersects( Head const& object ) const override;
};

template< typename Subject, typename Interface, typename Head, typename... Tail >
bool polymorphic_implement< Subject, Interface, Head, Tail... >::intersects( Head const& object ) const
{
    return geometry::intersects( get(), object );
}

} // detail

template< typename Subject, typename... Objects >
struct polymorphic_implement
    : detail::polymorphic_implement< Subject, polymorphic_interface< Objects... >, Objects... >
{
    using detail::polymorphic_implement< Subject, polymorphic_interface< Objects... >, Objects... >::intersects;
    using polymorphic_interface< Objects... >::intersects;
    virtual bool intersects( typename polymorphic_interface< Objects... >::interface_type const& object ) const override;
};

template< typename Subject >
struct polymorphic_implement< Subject >
    : detail::polymorphic_implement< Subject, polymorphic_interface<> >
{
    virtual bool intersects( typename polymorphic_interface<>::interface_type const& object ) const override;
};

template< typename Subject, typename... Objects >
bool polymorphic_implement< Subject, Objects... >::intersects( typename polymorphic_interface< Objects... >::interface_type const& object ) const
{
    return geometry::intersects( object, holder::get() );
}

template< typename Subject >
bool polymorphic_implement< Subject >::intersects( typename polymorphic_interface<>::interface_type const& object ) const
{
    return geometry::intersects( object, holder::get() );
}

} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_POLYMORPHIC_IMPLEMENT_HPP
