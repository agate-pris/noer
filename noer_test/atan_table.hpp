
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <agate_pris/noer/atan_table.hpp>
#include <agate_pris/noer/bbp_formula.hpp>
#include <agate_pris/noer/sqrt.hpp>
#include <agate_pris/noer/atan_approximation.hpp>
#include <agate_pris/noer/angle.hpp>
#include <cmath>

int main()
{
	using namespace std;
	using boost::multiprecision::cpp_int;
	using boost::multiprecision::cpp_rational;
	using namespace agate_pris::noer;
	auto sqrt_2 = sqrt( 2, 8 );
	auto pi = bbp_formula( 8 );
	auto f = [ &pi, &sqrt_2 ]( cpp_rational arg ){ return atan_approximation( arg, sqrt_2, pi, 8 ); };
	atan_table< double, 33 > at( f );
	atan_table< double, 33 > at2( sqrt( 2, 8 ), bbp_formula( 8 ), 8 );
	for( int i = 0; i < 33; ++i )
	{
		cout << at2.at( i ) << endl;
		cout << at.at( i ) << endl;
	}
	cout << "========" << endl;
	for( int i = 0; i < 50; ++i )
	{
		auto x = cos( i * 6.28 / 48 );
		auto y = sin( i * 6.28 / 48 );
		cout << at.get( y, x ) << endl;
	}
	system( "pause" );
}
