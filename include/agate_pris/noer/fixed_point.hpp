
#ifndef AGATE_PRIS_NOER_FIXED_POINT_HPP
#define AGATE_PRIS_NOER_FIXED_POINT_HPP

#include <utility>
#include <type_traits>
#include <limits>
#include <boost/assert.hpp>
#include <boost/operators.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <agate_pris/noer/pow.hpp>

namespace agate_pris
{
	namespace noer
	{
		// fixed_point definition
		// ======================
		template< typename Repr, int Exp >
		class fixed_point
			: public boost::additive< fixed_point< Repr, Exp > >
			, public boost::multiplicative< fixed_point< Repr, Exp > >
			, public boost::equality_comparable< fixed_point< Repr, Exp > >
			, public boost::less_than_comparable< fixed_point< Repr, Exp > >
		{
		private:
			// member variable
			// ---------------
			Repr m_repr;

		public:
			// constants
			// ---------
			static constexpr const int k_scaling_factor = pow< int, 2, Exp >();

			// static functions
			// ----------------
			template< typename T > static T convertible_max();
			template< typename T > static T mul_scaling_factor( T arg );
			template< typename T > static T div_scaling_factor( T arg );

			// constructor
			// -----------
			fixed_point()noexcept( std::is_nothrow_default_constructible< Repr >::value ) = default;
			template< typename Arg > fixed_point( const Arg& arg );

			// conversion
			// ----------
			template< typename T > explicit operator T ()const;
			operator std::make_signed_t< Repr >()const;
			operator std::make_unsigned_t< Repr >()const;

			// unary operator
			// --------------
			auto operator - ()const -> fixed_point< typename std::negate< Repr >::result_type, Exp >;

			// binary operator templates
			// -------------------------
			template< typename Rhs > fixed_point< Repr, Exp >& operator = ( const Rhs& rhs );
			template< typename Rhs > fixed_point< Repr, Exp >& operator += ( const Rhs& rhs );
			template< typename Rhs > fixed_point< Repr, Exp >& operator -= ( const Rhs& rhs );
			template< typename Rhs > fixed_point< Repr, Exp >& operator *= ( const Rhs& rhs );
			template< typename Rhs > fixed_point< Repr, Exp >& operator /= ( const Rhs& rhs );

			// binary operator for fixed_point< Repr, Exp >
			// --------------------------------------------
			inline bool operator == ( const fixed_point< Repr, Exp >& rhs )const;
			inline bool operator < ( const fixed_point< Repr, Exp >& rhs )const;
			fixed_point< Repr, Exp >& operator += ( const fixed_point< Repr, Exp >& rhs );
			fixed_point< Repr, Exp >& operator -= ( const fixed_point< Repr, Exp >& rhs );
			fixed_point< Repr, Exp >& operator *= ( const fixed_point< Repr, Exp >& rhs );
			fixed_point< Repr, Exp >& operator /= ( const fixed_point< Repr, Exp >& rhs );

			// other public functions
			// ----------------------
			inline const Repr& get()const{ return m_repr; }
			inline       Repr& get()     { return m_repr; }
		};

		// static functions
		// ----------------
		template< typename Repr, int Exp >
		template< typename T >
		T fixed_point< Repr, Exp >::convertible_max()
		{
			using std::numeric_limits;
			auto max = numeric_limits< T >::max();
			return max /= k_scaling_factor;
		}

		template< typename Repr, int Exp >
		template< typename T >
		T fixed_point< Repr, Exp >::mul_scaling_factor( T arg )
		{
			BOOST_ASSERT( convertible_max< T >() == 0 || arg <= convertible_max< T >() );
			return arg *= k_scaling_factor;
		}

		template< typename Repr, int Exp >
		template< typename T >
		T fixed_point< Repr, Exp >::div_scaling_factor( T arg )
		{
			return arg /= k_scaling_factor;
		}

		// constructor
		// -----------
		template< typename Repr, int Exp >
		template< typename Arg >
		fixed_point< Repr, Exp >::fixed_point( const Arg& arg )
			: m_repr( static_cast< Repr >( mul_scaling_factor( arg ) ) )
		{
		}

		// conversion
		// ----------
		template< typename Repr, int Exp >
		template< typename T >
		fixed_point< Repr, Exp >::operator T ()const
		{
			return div_scaling_factor( static_cast< T >( m_repr ) );
		}

		template<typename Repr, int Exp>
		inline fixed_point<Repr, Exp>::operator std::make_signed_t<Repr>() const
		{
			return div_scaling_factor( m_repr );
		}

		template<typename Repr, int Exp>
		inline fixed_point<Repr, Exp>::operator std::make_unsigned_t<Repr>() const
		{
			return div_scaling_factor( m_repr );
		}

		// binary operator templates
		// -------------------------

		// oprator =
		template< typename Repr, int Exp >
		template< typename Rhs >
		fixed_point< Repr, Exp >& fixed_point< Repr, Exp >::operator = ( const Rhs& rhs )
		{
			m_repr = static_cast< Repr >( mul_scaling_factor( rhs ) );
			return *this;
		}

		// operator +=
		template< typename Repr, int Exp >
		template< typename Rhs >
		fixed_point< Repr, Exp >& fixed_point< Repr, Exp >::operator += ( const Rhs& rhs )
		{
			m_repr += mul_scaling_factor( rhs );
			return *this;
		}

		// operator -=
		template< typename Repr, int Exp >
		template< typename Rhs >
		fixed_point< Repr, Exp >& fixed_point< Repr, Exp >::operator -= ( const Rhs& rhs )
		{
			m_repr -= mul_scaling_factor( rhs );
			return *this;
		}

		// operator *=
		template< typename Repr, int Exp >
		template< typename Rhs >
		fixed_point< Repr, Exp >& fixed_point< Repr, Exp >::operator *= ( const Rhs& rhs )
		{
			m_repr *= rhs;
			return *this;
		}

		// operator /=
		template< typename Repr, int Exp >
		template< typename Rhs >
		fixed_point< Repr, Exp >& fixed_point< Repr, Exp >::operator /= ( const Rhs& rhs )
		{
			m_repr /= rhs;
			return *this;
		}
		
		// unary operator
		// --------------

		template<typename Repr, int Exp>
		inline auto fixed_point<Repr, Exp>::operator-() const -> fixed_point< typename std::negate<Repr>::result_type, Exp>
		{
			return fixed_point<std::negate<Repr>::result_type, Exp>(*this) *= -1;
		}

		// binary operator for fixed_point< Repr, Exp >
		// --------------------------------------------

		// operator ==
		template< typename Repr, int Exp >
		inline bool fixed_point< Repr, Exp >::operator == ( const fixed_point< Repr, Exp >& rhs )const
		{
			return m_repr == rhs.get();
		}

		// operator <
		template< typename Repr, int Exp >
		inline bool fixed_point< Repr, Exp >::operator < ( const fixed_point< Repr, Exp >& rhs )const
		{
			return m_repr < rhs.get();
		}

		// operator +=
		template< typename Repr, int Exp >
		fixed_point< Repr, Exp >& fixed_point< Repr, Exp >::operator += ( const fixed_point< Repr, Exp >& rhs )
		{
			m_repr += rhs.get();
			return *this;
		}

		// operator -=
		template< typename Repr, int Exp >
		fixed_point< Repr, Exp >& fixed_point< Repr, Exp >::operator -= ( const fixed_point< Repr, Exp >& rhs )
		{
			m_repr -= rhs.get();
			return *this;
		}

		// operator *=
		template< typename Repr, int Exp >
		fixed_point< Repr, Exp >& fixed_point< Repr, Exp >::operator *= ( const fixed_point< Repr, Exp >& rhs )
		{
			using std::numeric_limits;
			using boost::multiprecision::cpp_rational;
			BOOST_ASSERT
				(
					static_cast< cpp_rational >( numeric_limits< Repr >::lowest() ) <=
					static_cast< cpp_rational >( m_repr ) *
					static_cast< cpp_rational >( rhs.get() ) &&
					static_cast< cpp_rational >( m_repr ) *
					static_cast< cpp_rational >( rhs.get() ) <=
					static_cast< cpp_rational >( numeric_limits< Repr >::max() )
					);
			m_repr *= rhs.get();
			m_repr /= k_scaling_factor;
			return *this;
		}

		// operator /=
		template< typename Repr, int Exp >
		fixed_point< Repr, Exp >& fixed_point< Repr, Exp >::operator /= ( const fixed_point< Repr, Exp >& rhs )
		{
			m_repr = mul_scaling_factor( m_repr );
			m_repr /= rhs.get();
			return *this;
		}

		// non-member function
		// -------------------
		template< typename Repr, int Exp >
		Repr numerator( const fixed_point< Repr, Exp >& num )
		{
			return num.get();
		}

		template< typename Repr, int Exp >
		constexpr const int denominator( const fixed_point< Repr, Exp >& )
		{
			return fixed_point< Repr, Exp >::k_scaling_factor;
		}

		// non-member operators
		// --------------------
		template< typename Lhs, typename Repr, int Exp >
		std::enable_if_t< std::is_arithmetic< Lhs >::value, Lhs >& operator += ( Lhs& lhs, const fixed_point< Repr, Exp >& rhs )
		{
			return lhs += static_cast< Lhs >( rhs );
		}

		template< typename Lhs, typename Repr, int Exp >
		std::enable_if_t< std::is_arithmetic< Lhs >::value, Lhs >& operator -= ( Lhs& lhs, const fixed_point< Repr, Exp >& rhs )
		{
			return lhs -= static_cast< Lhs >( rhs );
		}

		template< typename Lhs, typename Repr, int Exp >
		std::enable_if_t< std::is_arithmetic< Lhs >::value, Lhs >& operator *= ( Lhs& lhs, const fixed_point< Repr, Exp >& rhs )
		{
			lhs *= numerator( rhs );
			return lhs /= denominator( rhs );
		}

		template< typename Lhs, typename Repr, int Exp >
		std::enable_if_t< std::is_arithmetic< Lhs >::value, Lhs >& operator /= ( Lhs& lhs, const fixed_point< Repr, Exp >& rhs )
		{
			lhs *= denominator( rhs );
			return lhs /= numerator( rhs );
		}
	}
}

#endif // AGATE_PRIS_NOER_FIXED_POINT_HPP
