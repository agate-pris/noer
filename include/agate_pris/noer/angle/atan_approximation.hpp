
#ifndef AGATE_PRIS_NOER_APPROXIMATION
#define AGATE_PRIS_NOER_APPROXIMATION

#include <agate_pris/noer/pow.hpp>

namespace agate_pris
{
	namespace noer
	{
		template< typename ReturnValue = boost::multiprecision::cpp_rational >
		ReturnValue atan_approximation
		(
			const boost::multiprecision::cpp_rational& arg,
			const boost::multiprecision::cpp_rational& sqrt_2,
			const boost::multiprecision::cpp_rational& pi,
			const unsigned int precision
		)
		{
			using std::abs;
			using boost::multiprecision::cpp_rational;

			auto abs_arg = abs( arg );
			if( sqrt_2 + 1 < abs_arg )
			{
				return static_cast< ReturnValue >
				(
					static_cast< cpp_rational >
					(
						pi / 2 - atan_approximation< ReturnValue >( static_cast< cpp_rational >( 1 / arg ), sqrt_2, pi, precision )
					)
				);
			}
			if( sqrt_2 - 1 < abs_arg )
			{
				return static_cast< ReturnValue >
				(
					static_cast< cpp_rational >
					(
						pi / 4 + atan_approximation< ReturnValue >( static_cast< cpp_rational >( ( arg - 1 ) / ( arg + 1 ) ), sqrt_2, pi, precision )
					)
				);
			}

			cpp_rational result = 0;
			for( unsigned int i = 0; i < precision; ++i )
			{
				cpp_rational term = pow< int >( -1, i );
				term *= pow< cpp_rational >( arg, 2 * i + 1 );
				term /= 2 * i + 1;

				result += term;
			}
			return static_cast< ReturnValue >( result );
		}
	}
}

#endif // AGATE_PRIS_NOER_APPROXIMATION
