
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_CACHED_POINT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_CACHED_POINT_HPP

#include <type_traits>

namespace agate_pris
{
    namespace noer
    {
        template< typename Cache, typename Entity >
        class cached_point
        {
            private:
            Cache m_cache;
            Entity m_entity;

            public:
            // copy and move constructor
            cached_point( cached_point const& ) = default;
            cached_point( cached_point&& ) = default;

            // constructor
            template
            <
                typename Arg,
                typename = std::enable_if_t
                <
                    !std::is_base_of
                    <
                        cached_point,
                        std::decay_t< Arg >
                    >::value
                >
            >
            cached_point( Arg&& arg )
            : m_entity( std::forward< Arg >( arg ) )
            {
            }
        };
    }
}

#endif
