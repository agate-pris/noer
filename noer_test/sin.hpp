
#include <iostream>
#include <agate_pris/noer/degree.hpp>
#include <agate_pris/noer/bbp_formula.hpp>
#include <agate_pris/noer/sin.hpp>
#include <Windows.h>

int main()
{
	using namespace std;
	using namespace agate_pris::noer;
	degree< unsigned int, 16 > d;
	const sin_table< double, 256 > st( bbp_formula( 10 ), 10 );
	d.get() = d.k_pi * 2 / 3;
	cout << sin( st, d ) << endl;
	system( "pause" );
}
