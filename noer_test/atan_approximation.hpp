
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <agate_pris/noer/atan_approximation.hpp>
#include <agate_pris/noer/sqrt.hpp>
#include <agate_pris/noer/bbp_formula.hpp>

int main()
{
	using namespace std;
	using namespace boost::multiprecision;
	using namespace agate_pris::noer;

	auto sqrt_2 = sqrt( 2, 8 );
	auto pi = bbp_formula( 32 );

	for( int i = 0; i <= 100; ++i )
	{
		cpp_rational ratio = i;
		ratio /= 32;
		cout << "atan( " << i << "/" << 32 << " ) = " << static_cast< double >( atan_approximation< double >( ratio, sqrt_2, pi, i ) ) << endl;
	}
	for( int i = 0; i <= 100; ++i )
	{
		cpp_rational ratio = i;
		ratio /= 32;
		cout << "atan( " << i << "/" << 32 << " ) = " << static_cast< double >( atan_approximation( ratio, sqrt_2, pi, i ) ) << endl;
	}
	system( "pause" );
}
