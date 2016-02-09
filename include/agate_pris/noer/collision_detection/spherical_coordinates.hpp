
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_SPHERICAL_COORDINATES_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_SPHERICAL_COORDINATES_HPP

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
            };
        }
    }
}

#endif
