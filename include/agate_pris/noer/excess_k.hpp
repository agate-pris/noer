
#ifndef AGATE_PRIS_NOER_EXCESS_K_HPP
#define AGATE_PRIS_NOER_EXCESS_K_HPP

#include <utility>
#include <type_traits>
#include <limits>
#include <boost/assert.hpp>
#include <boost/operators.hpp>
#include <boost/multiprecision/cpp_int.hpp>

namespace agate_pris
{
	namespace noer
	{
		// excess_k definition
		// ===================
		template< typename Repr, unsigned int K >
		class excess_k
			: public boost::additive< excess_k< Repr, K > >
			, public boost::multiplicative< excess_k< Repr, K > >
			, public boost::equality_comparable< excess_k< Repr, K > >
			, public boost::less_than_comparable< excess_k< Repr, K > >
		{
		private:
			// member variable
			// ---------------
			Repr m_repr;

		public:
			// constants
			// ---------
			static constexpr const int k_offset = static_cast< int >( K );

			// static functions
			// ----------------
			template< typename T > static T convertible_max();
			template< typename T > static T convertible_lowest();
			template< typename T > static inline T add_offset( T arg );
			template< typename T > static inline T sub_offset( T arg );

			// constructor
			// -----------
			template< typename Arg >
			explicit excess_k( const Arg& arg );

			// conversion
			// ----------
			template< typename T >
			explicit operator T ()const;

			// binary operator templates
			// -------------------------
			template< typename Rhs > excess_k< Repr, K >& operator = ( const Rhs& rhs );
			template< typename Rhs > excess_k< Repr, K >& operator += ( const Rhs& rhs );
			template< typename Rhs > excess_k< Repr, K >& operator -= ( const Rhs& rhs );
			template< typename Rhs > excess_k< Repr, K >& operator *= ( const Rhs& rhs );
			template< typename Rhs > excess_k< Repr, K >& operator /= ( const Rhs& rhs );

			// binary operator for excess_k< Repr, K >
			// ---------------------------------------
			inline bool operator == ( const excess_k< Repr, K >& rhs )const;
			inline bool operator < ( const excess_k< Repr, K >& rhs )const;
			excess_k< Repr, K >& operator += ( const excess_k< Repr, K >& rhs );
			excess_k< Repr, K >& operator -= ( const excess_k< Repr, K >& rhs );
			excess_k< Repr, K >& operator *= ( const excess_k< Repr, K >& rhs );
			excess_k< Repr, K >& operator /= ( const excess_k< Repr, K >& rhs );

			// other public functions
			// ----------------------
			inline const Repr& get()const{ return m_repr; }
			inline       Repr& get()     { return m_repr; }
		};

		// static functions
		// ----------------

		// get max value convertible from T to excess_k< Repr, K >
		template< typename Repr, unsigned int K >
		template< typename T >
		T excess_k< Repr, K >::convertible_max()
		{
			using std::numeric_limits;
			auto max = numeric_limits< T >::max();
			return max -= k_offset;
		}

		// get lowest value convertible from excess_k< Repr, K > to T
		template< typename Repr, unsigned int K >
		template< typename T >
		T excess_k< Repr, K >::convertible_lowest()
		{
			using std::numeric_limits;
			auto lowest = numeric_limits< T >::lowest();
			return lowest += k_offset;
		}

		template< typename Repr, unsigned int K >
		template< typename T >
		inline T excess_k< Repr, K >::add_offset( T arg )
		{
			BOOST_ASSERT( arg <= convertible_max< T >() );
			return arg += k_offset;
		}

		template< typename Repr, unsigned int K >
		template< typename T >
		inline T excess_k< Repr, K >::sub_offset( T arg )
		{
			BOOST_ASSERT( convertible_lowest< T >() <= arg );
			return arg -= k_offset;
		}

		// constructor
		// -----------
		template< typename Repr, unsigned int K >
		template< typename Arg >
		excess_k< Repr, K >::excess_k( const Arg& arg )
			: m_repr( static_cast< Repr >( add_offset( arg ) ) )
		{
		}

		// conversion
		// ----------
		template< typename Repr, unsigned int K >
		template< typename T >
		excess_k< Repr, K >::operator T ()const
		{
			return sub_offset( static_cast< T >( m_repr ) );
		}

		// binary operator templates
		// -------------------------

		// operator =
		template< typename Repr, unsigned int K >
		template< typename Rhs >
		excess_k< Repr, K >&
			excess_k< Repr, K >::operator = ( const Rhs& rhs )
		{
			m_repr = static_cast< Repr >( add_offset( rhs ) );
			return *this;
		}

		// operator +=
		template< typename Repr, unsigned int K >
		template< typename Rhs >
		excess_k< Repr, K >& excess_k< Repr, K >::operator += ( const Rhs& rhs )
		{
			m_repr += rhs;
			return *this;
		}

		// operator -=
		template< typename Repr, unsigned int K >
		template< typename Rhs >
		excess_k< Repr, K >& excess_k< Repr, K >::operator -= ( const Rhs& rhs )
		{
			m_repr -= rhs;
			return *this;
		}

		// operator *=
		template< typename Repr, unsigned int K >
		template< typename Rhs >
		excess_k< Repr, K >& excess_k< Repr, K >::operator *= ( const Rhs& rhs )
		{
			auto repr = static_cast< Repr >( *this );
			repr *= rhs;
			*this = repr;
			return *this;
		}

		// operator /=
		template< typename Repr, unsigned int K >
		template< typename Rhs >
		excess_k< Repr, K >& excess_k< Repr, K >::operator /= ( const Rhs& rhs )
		{
			auto repr = static_cast< Repr >( *this );
			repr /= rhs;
			*this = repr;
			return *this;
		}

		// binary operator for excess_k< Repr, K >
		// ---------------------------------------

		// operator ==
		template< typename Repr, unsigned int K >
		inline bool excess_k< Repr, K >::operator == ( const excess_k< Repr, K >& rhs )const
		{
			return m_repr == rhs.get();
		}

		// operator <
		template< typename Repr, unsigned int K >
		inline bool excess_k< Repr, K >::operator < ( const excess_k< Repr, K >& rhs )const
		{
			return m_repr < rhs.get();
		}

		// operator +=
		template< typename Repr, unsigned int K >
		excess_k< Repr, K >& excess_k< Repr, K >::operator += ( const excess_k< Repr, K >& rhs )
		{
			using std::numeric_limits;
			BOOST_ASSERT( m_repr <= numeric_limits< Repr >::max() - rhs.get() );
			m_repr += rhs.get();
			m_repr -= k_offset;
			return *this;
		}

		// operator -=
		template< typename Repr, unsigned int K >
		excess_k< Repr, K >& excess_k< Repr, K >::operator -= ( const excess_k< Repr, K >& rhs )
		{
			using std::numeric_limits;
			BOOST_ASSERT( m_repr <= convertible_max< Repr >() );
			m_repr += k_offset;
			m_repr -= rhs.get();
			return *this;
		}

		// operator *=
		template< typename Repr, unsigned int K >
		excess_k< Repr, K >& excess_k< Repr, K >::operator *= ( const excess_k< Repr, K >& rhs )
		{
			auto l = static_cast< Repr >( *this );
			auto r = static_cast< Repr >( rhs );
			*this = l * r;
			return *this;
		}

		// operator /=
		template< typename Repr, unsigned int K >
		excess_k< Repr, K >& excess_k< Repr, K >::operator /= ( const excess_k< Repr, K >& rhs )
		{
			m_repr /= static_cast< Repr >( rhs );
			return *this;
		}
	}
}

#endif // AGATE_PRIS_NOER_EXCESS_K_HPP
