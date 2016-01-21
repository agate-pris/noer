
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_TRIANGLE_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_TRIANGLE_HPP

#include <utility>
#include <array>

#include <boost/array.hpp>
#include <agate_pris/noer/collision_detection/tag.hpp>
#include <agate_pris/noer/collision_detection/tags.hpp>
#include <agate_pris/noer/collision_detection/access.hpp>
#include <agate_pris/noer/collision_detection/point_type.hpp>

namespace agate_pris
{
	namespace noer
	{
		namespace collision_detection
		{
			template
			<
				typename PointType, bool ClockWise = true,
				template< typename, std::size_t > typename Container = std::array
			>
			class triangle
			{
				using container_type = Container< PointType, 3 >;
				private:
				container_type m_vertices;

				public:
				triangle() = default;
				triangle( const PointType& a, const PointType& b, const PointType& c )
				: m_vertices( { a, b, c } )
				{}

				container_type& get()
				{
					return m_vertices;
				}
				container_type const& get() const
				{
					return m_vertices;
				}
			};

			namespace traits
			{
				template
				<
					typename PointType, bool ClockWise,
					template< typename, std::size_t > typename Container
				>
				struct tag< triangle< PointType, ClockWise, Container > >
				{
					using type = triangle_tag;
				};

				template
				<
					typename PointType, bool ClockWise,
					template< typename, std::size_t > typename Container,
					std::size_t Index, std::size_t Dimension
				>
				struct indexed_access< triangle< PointType, ClockWise, Container >, Index, Dimension >
				{
					using coordinate_type = typename boost::geometry::coordinate_type< PointType >::type;

					static inline coordinate_type get( triangle< PointType, ClockWise, Container > const& t )
					{
						return boost::geometry::get< Dimension >( t.get()[ Index ] );
					}

					static inline void set
					( triangle< PointType, ClockWise, Container >& t, coordinate_type const& value )
					{
						boost::geometry::set< Dimension >( t.get()[ Index ], value );
					}
				};

				template
				<
					typename PointType, bool ClockWise,
					template< typename, std::size_t > typename Container
				>
				struct point_type< triangle< PointType, ClockWise, Container > >
				{
					using type = PointType;
				};
			}
		}
	}
}

#endif
