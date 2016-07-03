
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_CONTAINER_POLYMORPHIC_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_CONTAINER_POLYMORPHIC_HPP

#include <agate_pris/noer/collision_detection/core/tags.hpp>
#include <boost/fusion/algorithm/query/any.hpp>
#include <boost/fusion/include/any.hpp>

#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>

namespace agate_pris {
namespace noer {
namespace collision_detection {

template< typename CollisionDetection1, typename CollisionDetection2 >
inline bool intersects( CollisionDetection1 const& p, CollisionDetection2 const& c, polymorphic_tag, container_tag )
{
    // e is element of c
    auto f = [ &p ]( auto& e )
    {
        return intersects( p, e );
    };

    return boost::fusion::any( c, f );
}

template< typename CollisionDetection1, typename CollisionDetection2 >
inline bool intersects( CollisionDetection1 const& c, CollisionDetection2 const& p, container_tag, polymorphic_tag )
{
    // e is element of c
    auto f = [ &p ]( auto& e )
    {
        return intersects( p, e );
    };

    return boost::fusion::any( c, f );
}

} // collision_detection
} // noer
} // agate_pris

#endif
