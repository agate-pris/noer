
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POLAR_COORDINATES_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POLAR_COORDINATES_HPP

#include <utility>

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

                public:
                using radius_type = RadiusType;
                using angle_type  = AngleType;

                // constructor
                template< typename Radius, typename Angle >
                polar_coordinates( Radius&& r, Angle&& a );
                polar_coordinates( polar_coordinates const& ) = default;
                polar_coordinates( polar_coordinates&& ) = default;
            };

            // constructor
            // -----------
            template< typename RadiusType, typename AngleType >
            template< typename Radius, typename Angle >
            polar_coordinates< RadiusType, AngleType >::polar_coordinates( Radius&& r, Angle&& a )
            : m_radius( std::forward< Radius >( r ) )
            , m_angle( std::forward< Angle  >( a ) )
            {}
        }
    }
}

#endif
