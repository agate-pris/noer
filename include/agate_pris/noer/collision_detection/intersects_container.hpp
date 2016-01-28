
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_CONTAINER_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_INTERSECTS_CONTAINER_HPP

#include <type_traits>
#include <agate_pris/noer/collision_detection/tags.hpp>
#include <boost/fusion/algorithm/query/any.hpp>
#include <boost/fusion/include/any.hpp>

#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>

namespace agate_pris
{
    namespace noer
    {
        namespace collision_detection
        {
            namespace traits
            {
                template< typename... Elements >
                struct tag< std::tuple< Elements... > >
                {
                    using type = container_tag;
                };
            }

            template< typename CollisionDetection1, typename CollisionDetection2 >
            inline bool intersects( CollisionDetection1 const& c1, CollisionDetection2 const& c2, container_tag, container_tag )
            {
                // a is element of c1
                auto f = [ &c2 ]( auto& a )
                {
                    // b is elemnt of c2
                    auto f = [ &a ]( auto& b )
                    {
                        return intersects( a, b );
                    };
                    boost::fusion::result_of::any( c2, f );
                };

                return boost::fusion::result_of::any( c1, f );
            }

            template< typename CollisionDetection1, typename CollisionDetection2, typename AnyTag >
            inline auto intersects( CollisionDetection1 const& container, CollisionDetection2 const& object, container_tag, AnyTag )
            -> std::enable_if_t< !std::is_same< AnyTag, polymorphic_tag >::value, bool >
            {
                // e is element of container
                auto f = [ &object ]( auto& e )
                {
                    return intersects( e, object );
                };
                
                return boost::fusion::any( container, f );
            }

            template< typename CollisionDetection1, typename CollisionDetection2, typename AnyTag >
            inline auto intersects( CollisionDetection1 const& object, CollisionDetection2 const& container, AnyTag, container_tag )
            -> std::enable_if_t< !std::is_same< AnyTag, polymorphic_tag >::value, bool >
            {
                return false;
                // e is element of container
                auto f = [ &object ]( auto& e )
                {
                    return intersects( e, object );
                };
                
                return boost::fusion::result_of::any( container, f );
            }
        }
    }
}

#endif