#include <agate_pris/noer/integer_power.hpp>

namespace agate_pris
{
	namespace noer
	{
		boost::multiprecision::cpp_int integer_power( int m, unsigned int k )
		{
			boost::multiprecision::cpp_int result = 1;

			while( k-- )
			{
				result *= m;
			}

			return result;
		}
	}
}
