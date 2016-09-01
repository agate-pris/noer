
#ifndef AGATE_PRIS_NOER_GEOMETRY_TRIANGLE_HPP
#define AGATE_PRIS_NOER_GEOMETRY_TRIANGLE_HPP

#include <utility>
#include <array>

#include <boost/array.hpp>
#include <agate_pris/noer/geometry/core/tag.hpp>
#include <agate_pris/noer/geometry/core/tags.hpp>
#include <agate_pris/noer/geometry/core/access.hpp>
#include <agate_pris/noer/geometry/core/point_type.hpp>
#include <agate_pris/noer/geometry/core/point_order.hpp>
#include <boost/geometry/core/point_order.hpp>
#include <boost/geometry/algorithms/envelope.hpp>
#include <algorithm>

namespace agate_pris
{
	namespace noer
	{
		namespace geometry
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

				template< typename PointType,  template< typename, std::size_t > typename Container >
				struct point_order< triangle< PointType, true, Container > >
				{
					static const boost::geometry::order_selector value = boost::geometry::clockwise;
				};

				template< typename PointType, template< typename, std::size_t > typename Container >
				struct point_order< triangle< PointType, false, Container > >
				{
					static const boost::geometry::order_selector value = boost::geometry::counterclockwise;
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

namespace boost
{
	namespace geometry
	{
		template
		<
			typename BoxType,
			typename PointType, bool ClockWise,
			template< typename, std::size_t > typename Container
		>
		void envelope( agate_pris::noer::geometry::triangle< PointType, ClockWise, Container > const& t, BoxType& b )
		{
            namespace ng = agate_pris::noer::geometry;
            auto x = std::minmax( { ng::get< 0, 0 >( t ), ng::get< 1, 0 >( t ), ng::get< 2, 0 >( t ) } );
            auto y = std::minmax( { ng::get< 0, 1 >( t ), ng::get< 1, 1 >( t ), ng::get< 2, 1 >( t ) } );

            set< min_corner, 0 >( b, x.first );
            set< min_corner, 1 >( b, y.first );
            set< max_corner, 0 >( b, x.second );
            set< max_corner, 1 >( b, y.second );
		}

		template
		<
			typename BoxType,
			typename PointType, bool ClockWise,
			template< typename, std::size_t > typename Container
		>
		BoxType return_envelope( agate_pris::noer::geometry::triangle< PointType, ClockWise, Container > const& t )
		{
			BoxType b;
			envelope( t, b );
			return b;
		}
	}
}

#endif // AGATE_PRIS_NOER_GEOMETRY_TRIANGLE_HPP
