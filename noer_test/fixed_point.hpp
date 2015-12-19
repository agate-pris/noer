
#define _USE_MATH_DEFINES
#define NOMINMAX

#include <iostream>
#include <cmath>
#include <agate_pris/noer/fixed_point.hpp>

int main()
{
	using namespace std;
	using namespace agate_pris::noer;

	fixed_point< int, 8 > fp( M_PI );
	cout << static_cast< double >( fp ) << endl;
	cout << static_cast< double >( fp.get() ) << endl;

	system( "pause" );
}
