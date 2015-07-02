#ifndef AGATE_PRIS_NOER_INTEGER_POWER_HPP
#define AGATE_PRIS_NOER_INTEGER_POWER_HPP

#include <boost/multiprecision/cpp_int.hpp>

namespace agate_pris
{
	namespace noer
	{
		template< typename ReturnType, typename Base >
		ReturnType integer_power(Base m, unsigned int k)
		{
			ReturnType result = 1;

			while (k--)
			{
				result *= m;
			}

			return result;
		}
	}
}

#endif // AGATE_PRIS_NOER_INTEGER_POWER_HPP
