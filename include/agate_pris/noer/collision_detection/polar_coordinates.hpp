
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

                // radius accessor
                inline auto const& get_radius() const;
                template< typename Arg >
                inline void set_radius( Arg&& r );

                // angle accessor
                inline auto const& get_angle() const;
                template< typename Arg >
                inline void set_angle( Arg&& a );
            };

            // constructor
            // -----------
            template< typename RadiusType, typename AngleType >
            template< typename Radius, typename Angle >
            polar_coordinates< RadiusType, AngleType >::polar_coordinates( Radius&& r, Angle&& a )
            : m_radius( std::forward< Radius >( r ) )
            , m_angle( std::forward< Angle  >( a ) )
            {}

            // radius accessor
            // ---------------
            template< typename Radius, typename Angle >
            auto const& polar_coordinates< Radius, Angle >::get_radius() const
            {
                return m_radius;
            }

            template< typename Radius, typename Angle >
            template< typename Arg >
            void polar_coordinates< Radius, Angle >::set_radius( Arg&& r )
            {
                m_radius = std::forward< Radius >( r );
            }

            // angle accessor
            // --------------
            template< typename Radius, typename Angle >
            auto const& polar_coordinates< Radius, Angle >::get_angle() const
            {
                return m_angle;
            }

            template< typename Radius, typename Angle >
            template< typename Arg >
            inline void polar_coordinates< Radius, Angle >::set_angle( Arg&& a )
            {
                m_angle = std::forward< Arg >( a );
            }
        }
    }
}

#endif
