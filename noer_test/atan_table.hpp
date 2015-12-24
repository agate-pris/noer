
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <agate_pris/noer/atan_table.hpp>
#include <agate_pris/noer/bbp_formula.hpp>
#include <agate_pris/noer/sqrt.hpp>
#include <agate_pris/noer/atan_approximation.hpp>
#include <agate_pris/noer/angle.hpp>

int main()
{
	using namespace std;
	using boost::multiprecision::cpp_int;
	using namespace agate_pris::noer;
	auto pi = bbp_formula( 8 );
	auto sqrt_2 = sqrt( 2, 8 );
	auto f = [ &pi, &sqrt_2 ]( double arg ){ return atan_approximation( arg, sqrt_2, pi, 8 ); };
	atan_table< double, 33 > at( f );
	for( int i = 0; i < 33; ++i )
	{
		cout << at.at( i ) << endl;
	}
	system( "pause" );
}
