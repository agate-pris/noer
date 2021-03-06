#include <boost/multiprecision/cpp_int.hpp>

#include <agate_pris/noer/pow.hpp>
#include <agate_pris/noer/angle/bbp_formula.hpp>

namespace agate_pris
{
	namespace noer
	{
		boost::multiprecision::cpp_rational bbp_formula( const unsigned int precision )
		{
			using namespace boost::multiprecision;

			auto f = [](int k) -> cpp_rational
			{
				const cpp_rational a(4, 8 * k + 1);
				const cpp_rational b(2, 8 * k + 4);
				const cpp_rational c(1, 8 * k + 5);
				const cpp_rational d(1, 8 * k + 6);

				return ( a - b - c - d ) / pow< cpp_int >( 16, k );
			};

			cpp_rational result = 0;

			for (unsigned int i = 0; i < precision; ++i)
			{
				result += f(i);
			}

			return result;
		}
	}
}
