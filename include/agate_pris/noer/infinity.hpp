
#ifndef AGATE_PRIS_NOER_INFINITY_HPP
#define AGATE_PRIS_NOER_INFINITY_HPP

#include <type_traits>

namespace agate_pris
{
	namespace noer
	{
		template< typename Coefficient = int >
		struct infinity
		{
			Coefficient m_coefficient = 1;
		};

		template<> struct infinity< void >{};

		template< typename             > struct is_infinity                           { static constexpr const bool value = false; };
		template< typename Coefficient > struct is_infinity< infinity< Coefficient > >{ static constexpr const bool value = true;  };

		bool operator < ( const infinity< void >&, const infinity< void >& ) = delete;
		bool operator > ( const infinity< void >&, const infinity< void >& ) = delete;

		template< typename Coefficient > std::enable_if_t< !std::is_void< Coefficient >::value, bool > operator < ( const infinity< void >&, const infinity< Coefficient >& ){ return false; }
		template< typename Coefficient > std::enable_if_t< !std::is_void< Coefficient >::value, bool > operator > ( const infinity< void >&, const infinity< Coefficient >& ){ return true;  }
		template< typename Coefficient > std::enable_if_t< !std::is_void< Coefficient >::value, bool > operator < ( const infinity< Coefficient >&, const infinity< void >& ){ return true;  }
		template< typename Coefficient > std::enable_if_t< !std::is_void< Coefficient >::value, bool > operator > ( const infinity< Coefficient >&, const infinity< void >& ){ return false; }

		template< typename Lhs, typename Rhs > std::enable_if_t< !std::is_void< Lhs >::value && !std::is_void< Rhs >::value, bool > operator < ( const infinity< Lhs >& lhs, const infinity< Rhs >& rhs ){ return lhs.m_coefficient < rhs.m_coefficient; }
		template< typename Lhs, typename Rhs > std::enable_if_t< !std::is_void< Lhs >::value && !std::is_void< Rhs >::value, bool > operator > ( const infinity< Lhs >& lhs, const infinity< Rhs >& rhs ){ return lhs.m_coefficient > rhs.m_coefficient; }

		template< typename Rhs > std::enable_if_t< std::is_arithmetic< Rhs >::value, bool > operator < ( const infinity< void >&, const Rhs& ){ return false; }
		template< typename Rhs > std::enable_if_t< std::is_arithmetic< Rhs >::value, bool > operator > ( const infinity< void >&, const Rhs& ){ return true;  }

		template< typename Rhs, typename Coefficient > std::enable_if_t< std::is_arithmetic< Rhs >::value, bool > operator >= ( const infinity< Coefficient >& lhs, const Rhs& rhs ){ return !( lhs <  rhs ); }
		template< typename Rhs, typename Coefficient > std::enable_if_t< std::is_arithmetic< Rhs >::value, bool > operator <= ( const infinity< Coefficient >& lhs, const Rhs& rhs ){ return !( lhs >  rhs ); }
		template< typename Lhs, typename Coefficient > std::enable_if_t< std::is_arithmetic< Lhs >::value, bool > operator <  ( const Lhs& lhs, const infinity< Coefficient >& rhs ){ return rhs >  lhs; }
		template< typename Lhs, typename Coefficient > std::enable_if_t< std::is_arithmetic< Lhs >::value, bool > operator >  ( const Lhs& lhs, const infinity< Coefficient >& rhs ){ return rhs <  lhs; }
		template< typename Lhs, typename Coefficient > std::enable_if_t< std::is_arithmetic< Lhs >::value, bool > operator <= ( const Lhs& lhs, const infinity< Coefficient >& rhs ){ return rhs >= lhs; }
		template< typename Lhs, typename Coefficient > std::enable_if_t< std::is_arithmetic< Lhs >::value, bool > operator >= ( const Lhs& lhs, const infinity< Coefficient >& rhs ){ return rhs <= lhs; }
	}
}

#endif // AGATE_PRIS_NOER_INFINITY_HPP
