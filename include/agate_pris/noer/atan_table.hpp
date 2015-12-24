
#ifndef AGATE_PRIS_NOER_ATAN_TABLE_HPP
#define AGATE_PRIS_NOER_ATAN_TABLE_HPP

#include <cstddef>
#include <agate_pris/noer/function_traits.hpp>

namespace agate_pris
{
	namespace noer
	{
		template< typename Element, std::size_t Size >
		class atan_table
		{
			public:
			// constructor
			template< typename Func >
			atan_table( Func approximation_func );

			// acesss
			inline Element&       operator[]( std::size_t i );
			inline Element const& operator[]( std::size_t i )const;
			inline Element&       at(         std::size_t i );
			inline Element const& at(         std::size_t i )const;

			private:
			std::array< Element, Size > m_array;
		};

		// constructor
		template<typename Element, std::size_t Size>
		template< typename Func >
		inline atan_table< Element, Size >::atan_table( Func approximation_func )
		{
			using boost::multiprecision::cpp_rational;
			using arg_type = typename function_traits< Func >::argument_type;

			for( int i = 0; i < Size; ++i )
			{
				arg_type arg( i );
				arg /= Size - 1;
				m_array[ i ] = static_cast< Element >( approximation_func( arg ) );
			}
		}

		// access
		template<typename Element, std::size_t Size>
		inline Element const& atan_table<Element, Size>::operator[]( std::size_t i ) const
		{
			return m_array[ i ];
		}
		template<typename Element, std::size_t Size>
		inline Element & atan_table<Element, Size>::operator[]( std::size_t i )
		{
			return m_array[ i ];
		}
		template<typename Element, std::size_t Size>
		inline Element const& atan_table<Element, Size>::at( std::size_t i ) const
		{
			return m_array.at( i );
		}
		template<typename Element, std::size_t Size>
		inline Element & atan_table<Element, Size>::at( std::size_t i )
		{
			return m_array.at( i );
		}
	}
}

#endif // AGATE_PRIS_NOER_ATAN_TABLE_HPP
