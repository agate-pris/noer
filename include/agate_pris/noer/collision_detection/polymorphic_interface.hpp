
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POLYMORPHIC_INTERFACE_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POLYMORPHIC_INTERFACE_HPP

#include <agate_pris/noer/collision_detection/polymorphic_implement_fwd.hpp>
#include <agate_pris/noer/collision_detection/tag.hpp>
#include <agate_pris/noer/collision_detection/tags.hpp>
#include <type_traits>

namespace agate_pris {
namespace noer {
namespace collision_detection {

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

// overload intersects
template< typename... Objects >
inline bool intersects( polymorphic_interface< Objects... > const& a, polymorphic_interface< Objects... > const& b )
{
	return a.intersects( b );
}

template< typename AnyObject, typename AnyTag, typename... Objects >
inline auto intersects( polymorphic_interface< Objects... > const& a, AnyObject const& b, polymorphic_tag, AnyTag )
-> std::enable_if_t< !std::is_same< AnyTag, container_tag >::value, bool >
{
	return a.intersects( b );
}

template< typename AnyObject, typename AnyTag, typename... Objects >
inline auto intersects( AnyObject const& b, polymorphic_interface< Objects... > const& a, AnyTag, polymorphic_tag )
-> std::enable_if_t< !std::is_same< AnyTag, container_tag >::value, bool >
{
	return a.intersects( b );
}

} // collision_detection
} // noer
} // agate_pris

#endif
