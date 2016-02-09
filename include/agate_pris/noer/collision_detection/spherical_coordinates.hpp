
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_SPHERICAL_COORDINATES_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_SPHERICAL_COORDINATES_HPP

#include <utility>
#include <boost/geometry/core/coordinate_type.hpp>

namespace agate_pris
{
    namespace noer
    {
        namespace collision_detection
        {
            // 1st angle behave as polar angle from x-axis
            // 2nd angle behave as azimuthal angle of orthogonal projection on yz-plane from y-axis
            template< typename RadiusType, typename AnglesType >
            class spherical_coordinates
            {
                private:
                RadiusType m_radius;
                AnglesType m_angles;

                public:
                using radius_type = RadiusType;
                using angle_type  = typename boost::geometry::coordinate_type< AnglesType >::type;

                // constructor
                template< typename Radius, typename Angles >
                spherical_coordinates( Radius&& r, Angles&& a );
                spherical_coordinates( spherical_coordinates const& ) = default;
                spherical_coordinates( spherical_coordinates&& ) = default;
            };

            // constructor
            // -----------
            template< typename RadiusType, typename AnglesType >
            template< typename Radius, typename Angles >
            spherical_coordinates< RadiusType, AnglesType >::spherical_coordinates( Radius&& r, Angles&& a )
            : m_radius( std::forward< Radius >( r ) )
            , m_angles( std::forward< Angles >( a ) )
            {}
        }
    }
}

#endif
