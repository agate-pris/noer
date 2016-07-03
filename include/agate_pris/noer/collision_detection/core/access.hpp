
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_GET_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_GET_HPP

#include <utility>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/access.hpp>

namespace agate_pris {
namespace noer {
namespace collision_detection {

namespace traits {

template< typename CollisionDetection, std::size_t Index, std::size_t Dimension >
struct indexed_access
{
    using coordinate_type = typename boost::geometry::coordinate_type< CollisionDetection >::type;

    static inline coordinate_type get( CollisionDetection const& cd )
    {
        return boost::geometry::get< Index, Dimension >( cd );
    }

    static inline void set( CollisionDetection& cd, coordinate_type const& value )
    {
        boost::geometry::set< Index, Dimension >( cd, value );
    }
};

} // traits

template< std::size_t Index, std::size_t Dimension, typename CollisionDetectionType >
auto get( const CollisionDetectionType& cd )
{
    return traits::indexed_access< CollisionDetectionType, Index, Dimension >::get( cd );
}

template< std::size_t Index, std::size_t Dimension, typename CollisionDetectionType, typename CoordinateType >
void set( CollisionDetectionType& cd, const CoordinateType& value )
{
    traits::indexed_access< CollisionDetectionType, Index, Dimension >::set( cd, value );
}

} // collision_detection
} // noer
} // agate_pris

#endif
