
#ifndef AGATE_PRIS_NOER_GEOMETRY_POLYMORPHIC_INTERFACE_HPP
#define AGATE_PRIS_NOER_GEOMETRY_POLYMORPHIC_INTERFACE_HPP

#include <agate_pris/noer/geometry/polymorphic_implement_fwd.hpp>
#include <agate_pris/noer/geometry/core/tag.hpp>
#include <agate_pris/noer/geometry/core/tags.hpp>
#include <type_traits>

namespace agate_pris {
namespace noer {
namespace geometry {

namespace detail {

template< typename... Objects >
struct polymorphic_interface {};

template< typename Last >
struct polymorphic_interface< Last >
{
    virtual bool intersects( Last const& object ) const = 0;
};

template< typename Head, typename... Tail >
struct polymorphic_interface< Head, Tail... >
    : polymorphic_interface< Tail... >
{
    using polymorphic_interface< Tail... >::intersects;
    virtual bool intersects( Head const& object ) const = 0;
};

} // detail

template< typename... Objects >
struct polymorphic_interface
    : detail::polymorphic_interface< Objects... >
{
    template< typename Subject >
    using implement_type = polymorphic_implement< Subject, Objects... >;
    using interface_type = polymorphic_interface< Objects... >;
    using detail::polymorphic_interface< Objects... >::intersects;
    virtual bool intersects( interface_type const& ) const = 0;
};

template<>
struct polymorphic_interface<>
{
    template< typename Subject >
    using implement_type = polymorphic_implement< Subject >;
    using interface_type = polymorphic_interface<>;
    virtual bool intersects( interface_type const& ) const = 0;
};

namespace traits {
template
<
    typename... Objects
>
struct tag< polymorphic_interface< Objects... > >
{
    using type = polymorphic_tag;
};
}

} // geometry
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_POLYMORPHIC_INTERFACE_HPP
