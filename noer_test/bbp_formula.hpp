
#include <iostream>
#include <iomanip>
#include <agate_pris/noer/bbp_formula.hpp>

int main()
{
	using namespace std;
	using namespace agate_pris::noer;

	for( int i = 0; i < 10; ++i )
	{
		auto result = bbp_formula( i + 1 );
		cout << fixed << setprecision( 16 ) << result.convert_to< double >();
		cout << "(" << setw( 32 ) << numerator( result ) << "/" << setw( 32 ) << denominator( result ) << ")" << endl;
	}

	system( "pause" );
}
