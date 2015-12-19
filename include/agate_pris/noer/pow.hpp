
#ifndef AGATE_PRIS_NOER_POW_HPP
#define AGATE_PRIS_NOER_POW_HPP

#include <boost/multiprecision/cpp_int.hpp>

namespace agate_pris
{
	namespace noer
	{
		// コンパイル時 pow
		template< typename ReturnType, long long Base, unsigned long long Exponent >
		constexpr ReturnType pow()
		{
			return Exponent == 0 ?
				(1) :
				(Exponent == 1 ?
					(Base) :
					(pow< ReturnType, Base, Exponent / 2 >() * pow< ReturnType, Base, Exponent - Exponent / 2 >())
					);
		}

		// 実行時 pow
		template< typename ReturnType, typename Base >
		ReturnType pow(Base m, unsigned int k)
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

#endif // AGATE_PRIS_NOER_POW_HPP
