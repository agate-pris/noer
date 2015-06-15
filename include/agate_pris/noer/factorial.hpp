#ifndef AGATE_PRIS_NOER_FACTORIAL_HPP
#define AGATE_PRIS_NOER_FACTORIAL_HPP

#include <boost/multiprecision/cpp_int.hpp>

namespace agate_pris
{
	namespace noer
	{
		template< typename ReturnValue = boost::multiprecision::cpp_int, typename Arg >
		ReturnValue factorial(Arg arg)
		{
			ReturnValue result = arg;

			while (--arg > 0)
			{
				result *= arg;
			}

			return result;
		}
	}
}

#endif // AGATE_PRIS_NOER_FACTORIAL_HPP
