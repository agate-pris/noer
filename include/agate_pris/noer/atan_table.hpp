
#ifndef AGATE_PRIS_NOER_ATAN_TABLE_HPP
#define AGATE_PRIS_NOER_ATAN_TABLE_HPP

#include <cstddef>
#include <agate_pris/noer/function_traits.hpp>
#include <agate_pris/noer/duplicate.hpp>

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
			atan_table( const Func& approximation_func );

			// acesss
			inline Element&       operator[]( std::size_t i );
			inline Element const& operator[]( std::size_t i )const;
			inline Element&       at(         std::size_t i );
			inline Element const& at(         std::size_t i )const;

			template< typename Arg >
			Element get( const Arg& arg )const
			{
				if( arg < static_cast< Arg >( 0 ) )
					return straight() - get( -arg );
				if( arg <= static_cast< Arg >( 1 ) )
				{
					auto tmp = arg;
					return m_array[ static_cast< std::size_t >( tmp *= ( Size - 1 ) ) ];
				}
				auto tmp = Arg( 1 );
				return right() - get( tmp /= arg );
			}

			template< typename Arg >
			Element get( const Arg& y, const Arg& x )const
			{
				if( y < 0 )
					return straight() + get( -y, -x );
				if( x < 0 )
					return straight() - get(  y, -x );
				return                  get(  y / x );
			}

			private:
			Element right()const;
			Element straight()const;
			Element full()const;
			std::array< Element, Size > m_array;
		};

		// constructor
		template<typename Element, std::size_t Size>
		template< typename Func >
		inline atan_table< Element, Size >::atan_table( const Func& approximation_func )
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

		// 直角
		template<typename Element, std::size_t Size>
		inline Element atan_table<Element, Size>::right()const
		{
			auto b = m_array.back();
			return b *= 2;
		}

		// 平角
		template<typename Element, std::size_t Size>
		inline Element atan_table<Element, Size>::straight()const
		{
			auto b = m_array.back();
			return b *= 4;
		}

		// 周角
		template<typename Element, std::size_t Size>
		inline Element atan_table<Element, Size>::full()const
		{
			auto b = m_array.back();
			return b *= 8;
		}
	}
}

#endif // AGATE_PRIS_NOER_ATAN_TABLE_HPP
