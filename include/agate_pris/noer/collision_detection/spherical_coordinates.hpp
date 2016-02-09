
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_SPHERICAL_COORDINATES_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_SPHERICAL_COORDINATES_HPP

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
            };
        }
    }
}

#endif
