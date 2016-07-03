
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_CACHED_POINT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_CACHED_POINT_HPP

#include <type_traits>
#include <utility>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/algorithms/transform.hpp>

namespace agate_pris {
namespace noer {
namespace collision_detection {

template< typename Cache, typename Entity >
class cached_point
{
    private:
    Cache  m_cache;
    Entity m_entity;

    public:
    template< typename std::size_t Index >
    inline auto get() const
    {
        return boost::geometry::get< Index >( m_cache );
    }
    inline bool update_cache()
    {
        return boost::geometry::transform( m_entity, m_cache );
    }

    inline auto const& get_entity() const;
    inline auto&       get_entity();

    // copy and move constructor
    cached_point( cached_point const& ) = default;
    cached_point( cached_point&&      ) = default;

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
    inline cached_point( Arg&& arg )
        : m_entity( std::forward< Arg >( arg ) )
    {}
    template< typename First, typename Second, typename... Tail >
    inline cached_point( First&& f, Second&& s, Tail&&... t )
        : m_entity( std::forward< First >( f ), std::forward< Second >( s ), std::forward< Tail >( t )... )
    {}
};

template< typename Cache, typename Entity >
inline auto const& cached_point< Cache, Entity >::get_entity() const
{
    return m_entity;
}

template< typename Cache, typename Entity >
inline auto& cached_point< Cache, Entity >::get_entity()
{
    return m_entity;
}

} // collision_detection
} // noer
} // agate_pris

namespace boost {
namespace geometry {
namespace traits {

template< typename Cache, typename Entity >
struct tag< agate_pris::noer::collision_detection::cached_point< Cache, Entity > >
    : public tag< Cache >
{};

template< typename Cache, typename Entity >
struct coordinate_type< agate_pris::noer::collision_detection::cached_point< Cache, Entity > >
    : coordinate_type< Cache >
{};

template< typename Cache, typename Entity >
struct coordinate_system< agate_pris::noer::collision_detection::cached_point< Cache, Entity > >
    : coordinate_system< Cache >
{};

template< typename Cache, typename Entity >
struct dimension< agate_pris::noer::collision_detection::cached_point< Cache, Entity > >
    : dimension< Cache >
{};

template< typename Cache, typename Entity, long unsigned int Dimension >
struct access< agate_pris::noer::collision_detection::cached_point< Cache, Entity >, Dimension >
{
    static inline auto get( agate_pris::noer::collision_detection::cached_point< Cache, Entity > const& p )
    {
        return p.template get< Dimension >();
    }
};

} // traits
} // geometry
} // boost

#endif
