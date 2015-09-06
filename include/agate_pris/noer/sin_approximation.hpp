#ifndef AGATE_PRIS_NOER_SIN_APPROXIMATION_HPP
#define AGATE_PRIS_NOER_SIN_APPROXIMATION_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <agate_pris/noer/integer_power.hpp>
#include <agate_pris/noer/factorial.hpp>

namespace agate_pris
{
	namespace noer
	{
		template< typename ReturnValue = boost::multiprecision::cpp_rational >
		ReturnValue sin_approximation(const boost::multiprecision::cpp_rational x, const unsigned int precision)
		{
			using namespace boost::multiprecision;
			auto f = [x](const int k)->cpp_rational
			{
				const cpp_rational numerator = integer_power< int >(-1, k) * integer_power< cpp_rational >(x, 2 * k + 1);
				const cpp_rational denominator = factorial<>(2 * k + 1);
				return numerator / denominator;
			};

			cpp_rational result = 0;

			for (unsigned int k = 0; k < precision; ++k)
			{
				result += f(k);
			}

			return result;
		}
	}
}

#endif AGATE_PRIS_NOER_SIN_APPROXIMATION_HPP
