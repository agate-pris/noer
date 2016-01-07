
#ifndef AGATE_PRIS_NOER_ATAN_TABLE_HPP
#define AGATE_PRIS_NOER_ATAN_TABLE_HPP

#include <cstddef>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/serialization/access.hpp>
#include <agate_pris/noer/function_traits.hpp>
#include <agate_pris/noer/duplicate.hpp>
#include <agate_pris/noer/atan_approximation.hpp>

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
			atan_table
			(
				const boost::multiprecision::cpp_rational& sqrt_2,
				const boost::multiprecision::cpp_rational& pi,
				const unsigned int precision
			);
			atan_table() = default;

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
				if( y <= x )
				{
					auto i = y;
					i *= Size - 1;
					i /= x;
					return m_array[ static_cast< std::size_t >( i ) ];
				}
				return right() - get( x, y );
			}

			private:
			Element right()const;
			Element straight()const;
			Element full()const;
			std::array< Element, Size > m_array;
			template< typename Func >
			void initialize( const Func& approximation_func );

			// serialize
			friend boost::serialization::access;
			template< class Archive >
			void serialize( Archive& ar, unsigned int ver );
		};

		// constructor
		template<typename Element, std::size_t Size>
		template< typename Func >
		inline atan_table< Element, Size >::atan_table( const Func& approximation_func )
		{
			initialize( approximation_func );
		}

		template<typename Element, std::size_t Size>
		inline atan_table< Element, Size >::atan_table
		(
			const boost::multiprecision::cpp_rational& sqrt_2,
			const boost::multiprecision::cpp_rational& pi,
			const unsigned int precision
		)
		{
			auto f = [ &sqrt_2, &pi, precision ]( const boost::multiprecision::cpp_rational& arg )
			{
				return atan_approximation( arg, sqrt_2, pi, precision ); 
			};
			initialize( f );
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

		// 初期化
		template<typename Element, std::size_t Size>
		template<typename Func>
		inline void atan_table<Element, Size>::initialize( const Func & approximation_func )
		{
			using arg_type = std::decay_t< typename function_traits< Func >::argument_type >;
			for( int i = 0; i < Size; ++i )
			{
				arg_type arg( i );
				arg /= Size - 1;
				m_array[ i ] = static_cast< Element >( approximation_func( arg ) );
			}
		}

		// serialization
		template< typename Element, std::size_t Size >
		template< class Archive >
		inline void atan_table< Element, Size >::serialize( Archive& ar, unsigned int ver )
		{
			ar & boost::serialization::make_array( m_array.data(), m_array.size() );
		}
	}
}

#endif // AGATE_PRIS_NOER_ATAN_TABLE_HPP
