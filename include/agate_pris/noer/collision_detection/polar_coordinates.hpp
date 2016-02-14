
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POLAR_COORDINATES_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POLAR_COORDINATES_HPP

#include <utility>
#include <cmath>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/access.hpp>

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
                inline polar_coordinates( Radius&& r, Angle&& a );
                inline polar_coordinates( polar_coordinates const& ) = default;
                inline polar_coordinates( polar_coordinates&& ) = default;

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

namespace boost
{
    namespace geometry
    {
        // transform to cartesian coordinate overload
        template
        <
            typename Radius, typename Angle, typename Target,
            typename = std::enable_if_t< std::is_same
            <
                boost::geometry::point_tag,
                typename boost::geometry::tag< Target >::type
            >::value >,
            typename = std::enable_if_t< std::is_same
            <
                boost::geometry::cs::cartesian,
                typename boost::geometry::coordinate_system< Target >::type
            >::value >,
            typename = std::enable_if_t< boost::geometry::dimension< Target >::value == 2 >
        >
        bool transform( agate_pris::noer::collision_detection::polar_coordinates< Radius, Angle > const& source, Target& target )
        {
            namespace bg = boost::geometry;
            using coordinate_type = typename bg::coordinate_type< Target >::type;

            auto const& r = static_cast< coordinate_type >( source.get_radius() );
            auto const& t = source.get_angle();
            bg::set< 0 >( target, r * std::cos( t ) );
            bg::set< 1 >( target, r * std::sin( t ) );

            return true;
        };
    }
}

#endif
