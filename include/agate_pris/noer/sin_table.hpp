
#ifndef AGATE_PRIS_NOER_SIN_TABLE_HPP
#define AGATE_PRIS_NOER_SIN_TABLE_HPP

#include <cstddef>
#include <array>
#include <boost/multiprecision/cpp_int.hpp>

#include <agate_pris/noer/sin_approximation.hpp>
#include <agate_pris/noer/pow.hpp>

namespace agate_pris
{
	namespace noer
	{
		// Element :保持する値の型
		// Division:円周を何分割するか
		template< typename Element, std::size_t Division >
		class sin_table
		{
			static_assert( Division % 8 == 0, "Division must be a factor of 8." );
			public:
			// constructor
			template< typename Func >
			sin_table( const Func& approximation_func );
			sin_table( boost::multiprecision::cpp_rational pi, unsigned int precision );

			// eval sin
			template< std::size_t Subdivision > inline Element get( std::size_t arg )const;
			inline Element get( std::size_t arg )const;

			// constants
			static constexpr const std::size_t k_pi   = Division / 2;
			static constexpr const std::size_t k_pi_2 = Division / 4;
			static constexpr const std::size_t k_pi_4 = Division / 8;

			private:
			static constexpr const std::size_t k_size = Division / 4 + 1;
			std::array< Element, k_size > m_array;
			template< typename Func >
			void initialize( const Func& approximation_func );
		};

		// constructor
		template< typename Element, std::size_t Division >
		template< typename Func >
		sin_table< Element, Division >::sin_table( const Func& approximation_func )
		{
			initialize( approximation_func );
		}

		template< typename Element, std::size_t Division >
		inline sin_table< Element, Division >::sin_table( boost::multiprecision::cpp_rational pi, unsigned int precision )
		{
			auto l = [ &pi, precisoin ]( int i )
			{
				return static_cast< Element >( sin_approximation<>( pi * 2 * i / Division, precision ) );
			};
			initialize( l );
		}

		template< typename Element, std::size_t Division >
		template< std::size_t Subdivision >
		inline Element sin_table< Element, Division >::get( std::size_t arg )const
		{
			constexpr int subdivision = static_cast< int >( Subdivision );
			auto i = arg / subdivision;
			auto m = arg % subdivision;

			auto diff = get( i + 1 ) - get( i );
			diff *= m;
			diff /= subdivision;

			return get( i ) + diff;
		}

		template<typename Element, std::size_t Division>
		template<typename Func>
		inline void sin_table<Element, Division>::initialize( const Func & approximation_func )
		{
			m_array[ 0 ] = static_cast< Element >( 0 );
			for( int i = 1; i < k_size - 1; ++i )
			{
				m_array[ i ] = static_cast< Element >( approximation_func( i ) );
			}
			m_array[ k_size - 1 ] = static_cast< Element >( 1 );
		}

		template< typename Element, std::size_t Division >
		inline Element sin_table< Element, Division >::get( std::size_t arg )const
		{
			constexpr int division = static_cast< int >( Division );
			auto v = static_cast< int >( arg % division );
			if( v <= Division / 2 )
			return  m_array[ division / 4 - std::abs( division     / 4 - v ) ];
			else
			return -m_array[ division / 4 - std::abs( division * 3 / 4 - v ) ];
		}
	}
}

#endif // AGATE_PRIS_NOER_SIN_TABLE_HPP
