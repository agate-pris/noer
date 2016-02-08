
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POLAR_COORDINATES_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POLAR_COORDINATES_HPP

namespace agate_pris
{
    namespace noer
    {
        namespace collision_detection
        {
            template< typename RadiusType, typename AngleType >
            class polar_coordinates
            {
                private:
                RadiusType m_radius;
                AngleType  m_angle;
            };
        }
    }
}

#endif
