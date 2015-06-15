#ifndef AGATE_PRIS_NOER_INTEGER_POWER_HPP
#define AGATE_PRIS_NOER_INTEGER_POWER_HPP

#include <boost/multiprecision/cpp_int.hpp>

namespace agate_pris
{
	namespace noer
	{
		boost::multiprecision::cpp_int integer_power( int m, unsigned int k );
	}
}

#endif // AGATE_PRIS_NOER_INTEGER_POWER_HPP
