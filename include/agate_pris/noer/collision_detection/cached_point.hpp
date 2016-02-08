
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_CACHED_POINT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_CACHED_POINT_HPP

#include <type_traits>
#include <boost/geometry/algorithms/transform.hpp>

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
            template< typename std::size_t Index >
            auto get() const
            {
                return boost::geometry::get< Index >( m_cache );
            }
            bool update_cache()
            {
                return boost::geometry::transform( m_entity, m_cache );
            }

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
            template< typename First, typename Second, typename... Tail >
            cached_point( First&& f, Second&& s, Tail&&... t )
            : m_entity( std::forward< First >( f ), std::forward< Second >( s ), std::forward< Tail >( t )... )
            {
            }
        };
    }
}

namespace boost
{
    namespace geometry
    {
        namespace traits
        {
            template< typename Cache, typename Entity >
            struct tag< cached_point< Cache, Entity > >
            : public tag< Cache >
            {};

            template< typename Cache, typename Entity >
            struct coordinate_type< cached_point< Cache, Entity > >
            : coordinate_type< Cache >
            {};

            template< typename Cache, typename Entity >
            struct coordinate_system< cached_point< Cache, Entity > >
            : coordinate_system< Cache >
            {};

            template< typename Cache, typename Entity >
            struct dimension< cached_point< Cache, Entity > >
            : dimension< Cache >
            {};

            template< typename Cache, typename Entity, long unsigned int Dimension >
            struct access< cached_point< Cache, Entity >, Dimension >
            {
                static inline auto get( cached_point< Cache, Entity > const& p )
                {
                    return p.template get< Dimension >();
                }
            };
        }
    }
}

#endif
