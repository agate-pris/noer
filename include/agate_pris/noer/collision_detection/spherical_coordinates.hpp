
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_SPHERICAL_COORDINATES_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_SPHERICAL_COORDINATES_HPP

#include <utility>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/access.hpp>

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

                // radius accessor
                inline auto const& get_radius() const;
                template< typename Arg > inline void set_radius( Arg&& r );

                // angle accessor
                template< std::size_t Index > inline auto get_angle() const;
                template< std::size_t Index, typename Arg > inline void set_angle( Arg&& a );
            };

            // constructor
            // -----------
            template< typename RadiusType, typename AnglesType >
            template< typename Radius, typename Angles >
            spherical_coordinates< RadiusType, AnglesType >::spherical_coordinates( Radius&& r, Angles&& a )
            : m_radius( std::forward< Radius >( r ) )
            , m_angles( std::forward< Angles >( a ) )
            {}

            // radius accessor
            // ---------------
            template< typename Radius, typename Angles >
            auto const& spherical_coordinates< Radius, Angles >::get_radius() const
            {
                return m_radius;
            }

            template< typename Radius, typename Angles >
            template< typename Arg >
            void spherical_coordinates< Radius, Angles >::set_radius( Arg&& r )
            {
                m_radius = std::forward< Arg >( r );
            }

            // angle accessor
            // --------------
            template< typename Radius, typename Angles >
            template< std::size_t Index >
            auto spherical_coordinates< Radius, Angles >::get_angle() const
            {
                return boost::geometry::get< Index >( m_angles );
            }

            template< typename Radius, typename Angles >
            template< std::size_t Index, typename Arg >
            inline void spherical_coordinates< Radius, Angles >::set_angle( Arg&& a )
            {
                boost::geometry::set< Index >( m_angles, std::forward< Arg >( a ) );
            }
        }
    }
}

#endif
