
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_RELATIVE_POINT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_RELATIVE_POINT_HPP

#include <utility>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>

namespace agate_pris
{
    namespace noer
    {
        namespace collision_detection
        {
            template< typename CoordinateType, typename Parent, typename Child >
            struct relative_point
            {
                Parent parent;
                Child  child;
            };
        }
    }
}

namespace boost
{
    namespace geometry
    {
        namespace traits
        {
            template< typename CoordinateType, typename Parent, typename Child >
            struct tag< agate_pris::noer::collision_detection::relative_point< CoordinateType, Parent, Child > >
            {
                using type = point_tag;
            };

            template< typename CoordinateType, typename Parent, typename Child >
            struct coordinate_type< agate_pris::noer::collision_detection::relative_point< CoordinateType, Parent, Child > >
            {
                using type = CoordinateType;
            };

            template< typename CoordinateType, typename Parent, typename Child >
            struct coordinate_system< agate_pris::noer::collision_detection::relative_point< CoordinateType, Parent, Child > >
            {
                using type =
                std::enable_if_t
                <
                    std::is_same
                    <
                        typename coordinate_system< Parent >::type,
                        typename coordinate_system< Child  >::type
                    >::value,
                    typename coordinate_system< Child >::type
                >;
            };

            template< typename CoordinateType, typename Parent, typename Child >
            struct dimension< agate_pris::noer::collision_detection::relative_point< CoordinateType, Parent, Child > >
            {
                std::size_t value =
                std::enable_if_t
                <
                    dimension< Parent >::value == dimension< Child >::value,
                    std::integral_constant< std::size_t, dimension< Child >::value >
                >::value;
            };

            template< typename CoordinateType, typename Parent, typename Child, std::size_t Dimension >
            struct access< agate_pris::noer::collision_detection::relative_point< CoordinateType, Parent, Child >, Dimension >
            {
                static inline auto get( agate_pris::noer::collision_detection::relative_point< CoordinateType, Parent, Child > const& p )
                {
                    return
                    geometry::get< Dimension >( p.parent ) +
                    geometry::get< Dimension >( p.child );
                }

                static inline void set
                (
                    agate_pris::noer::collision_detection::relative_point< CoordinateType, Parent, Child >& p,
                    typename coordinate_type< Child >::type const& value
                )
                {
                    geometry::set< Dimension >( p.child, value );
                }
            };
        }
    }
}

#endif
