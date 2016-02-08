
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_CACHED_POINT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_CACHED_POINT_HPP

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

            // copy and move constructor
            cached_point( cached_point const& ) = default;
            cached_point( cached_point&& ) = default;
        };
    }
}

#endif
