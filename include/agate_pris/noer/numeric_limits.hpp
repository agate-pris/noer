
#ifndef AGATE_PRIS_NOER_NUMERIC_LIMITS_HPP
#define AGATE_PRIS_NOER_NUMERIC_LIMITS_HPP

#include <limits>
#include <type_traits>
#include <agate_pris/noer/empty.hpp>

namespace agate_pris
{
	namespace noer
	{
		template< typename Number >
		struct numeric_limits
		: public std::conditional_t< std::is_fundamental< Number >::value, std::numeric_limits< Number >, empty >
		{
		};
	}
}

#endif
