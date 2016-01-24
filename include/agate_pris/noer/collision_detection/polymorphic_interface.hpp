
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POLYMORPHIC_INTERFACE_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POLYMORPHIC_INTERFACE_HPP

#include <agate_pris/noer/collision_detection/polymorphic_implement_fwd.hpp>
#include <agate_pris/noer/collision_detection/tag.hpp>
#include <agate_pris/noer/collision_detection/tags.hpp>

namespace agate_pris
{
    namespace noer
    {
        namespace collision_detection
        {
            namespace detail
            {
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
            }

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

            namespace traits
            {
                template
                <
                    typename... Objects
                >
                struct tag< polymorphic_interface< Objects... > >
                {
                    using type = polymorphic_tag;
                };
            }
        }
    }
}

#endif
