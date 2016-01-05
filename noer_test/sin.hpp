
#include <iostream>
#include <agate_pris/noer/angle.hpp>
#include <agate_pris/noer/bbp_formula.hpp>
#include <agate_pris/noer/sin.hpp>
#include <agate_pris/noer/fixed_point.hpp>
#include <Windows.h>

int main()
{
	using namespace std;
	using namespace agate_pris::noer;
	angle< unsigned int, 16 > d;
	const sin_table< fixed_point< int, 10 >, 256 > st( bbp_formula( 10 ), 10 );
	d.get() = d.k_straight_quantity * 2 / 3;
	auto result = sin( st, d );
	cout << static_cast< double >( result ) << endl;
	system( "pause" );
}
