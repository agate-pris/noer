
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_HPP

#include <boost/numeric/ublas/vector.hpp>
namespace agate_pris
{
	namespace noer
	{
		namespace collision_detection
		{
			namespace detail
			{
				template< std::size_t DimensionCount, std::size_t Index >
				struct array_assign
				{
					template< typename CoordinateType, typename ArrayType >
					static inline void apply( boost::numeric::ublas::vector< CoordinateType, ArrayType >& values, CoordinateType const& value )
					{
						values( Index ) = value;
					}
				};

				template<> struct array_assign< 2, 2 >
				{
					template< typename CoordinateType, typename ArrayType >
					static inline void apply( boost::numeric::ublas::vector< CoordinateType, ArrayType >&, CoordinateType const& ) {}
				};

				template<> struct array_assign< 1, 1 >
				{
					template< typename CoordinateType, typename ArrayType >
					static inline void apply( boost::numeric::ublas::vector< CoordinateType, ArrayType >&, CoordinateType const& ) {}
				};

				template<> struct array_assign< 1, 2 >
				{
					template< typename CoordinateType, typename ArrayType >
					static inline void apply( boost::numeric::ublas::vector< CoordinateType, ArrayType >&, CoordinateType const& ) {}
				};
			}

			template
			<
				typename CoordinateType,
				std::size_t DimensionCount,
				typename ArrayType = boost::numeric::ublas::bounded_array
				<
					CoordinateType,
					DimensionCount
				>
			>
			class point
			{
				private:
				boost::numeric::ublas::vector< CoordinateType, ArrayType > m_values;

				public:
				point()
					: m_values( DimensionCount )
				{}

				/// @brief Constructor to set one value
				explicit inline point( CoordinateType const& v0 )
					: m_values( DimensionCount )
				{
					detail::array_assign< DimensionCount, 0 >::apply( m_values, v0 );
					detail::array_assign< DimensionCount, 0 >::apply( m_values, CoordinateType() );
					detail::array_assign< DimensionCount, 0 >::apply( m_values, CoordinateType() );
				}

				/// @brief Constructor to set two values
				inline point( CoordinateType const& v0, CoordinateType const& v1 )
					: m_values( DimensionCount )
				{
					detail::array_assign< DimensionCount, 0 >::apply( m_values, v0 );
					detail::array_assign< DimensionCount, 0 >::apply( m_values, v1 );
					detail::array_assign< DimensionCount, 0 >::apply( m_values, CoordinateType() );
				}

				/// @brief Constructor to set three values
				inline point( CoordinateType const& v0, CoordinateType const& v1, CoordinateType const& v2 )
					: m_values( DimensionCount )
				{
					detail::array_assign< DimensionCount, 0 >::apply( m_values, v0 );
					detail::array_assign< DimensionCount, 0 >::apply( m_values, v1 );
					detail::array_assign< DimensionCount, 0 >::apply( m_values, v2 );
				}

				/// @brieft Get a coordinate
				/// @tparam Index coordinate to get
				/// @return the coordinate
				template< unsigned int Index >
				inline CoordinateType const& get() const
				{
					static_assert( Index < DimensionCount, "Index < DimensionCount must be true." );
					return m_values( Index );
				}

				/// @brief Set a coordinate
				/// @tparam Index coordinate to set
				/// @param value value to set
				template< std::size_t Index >
				void set( CoordinateType const& value )
				{
					static_assert( Index < DimensionCount, "Index < DimensionCount must be true." );
					m_values( Index ) = value;
				}
			};
		}
	}
}

#endif
