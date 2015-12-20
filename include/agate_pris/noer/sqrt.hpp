
#ifndef AGATE_PRIS_NOER_SQRT_HPP
#define AGATE_PRIS_NOER_SQRT_HPP

#include <boost/multiprecision/cpp_int.hpp>
#include <agate_pris/noer/pow.hpp>

namespace agate_pris
{
	namespace noer
	{
		boost::multiprecision::cpp_rational sqrt( unsigned long long int x, unsigned int precision )
		{
			using namespace boost::multiprecision;

			cpp_rational result = 1;

			while( result * result < x )
			{
				++result;
			}

			for( unsigned int i = 0; i < precision; ++i )
			{
				result = ( result + x / result ) / 2;
			}

			return result;
		}
	}
}

#endif // AGATE_PRIS_NOER_SQRT_HPP
