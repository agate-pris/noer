
#define NOMINMAX

#include <iostream>
#include <iomanip>

#include <agate_pris/noer/bbp_formula.hpp>
#include <agate_pris/noer/sin_table.hpp>

int main()
{
	using namespace std;
	using namespace agate_pris::noer;

	sin_table< double, 256 > st( bbp_formula( 10 ), 10 );

	cout << st.k_pi   << endl;
	cout << st.k_pi_2 << endl;
	cout << st.k_pi_4 << endl;

	for( int i = 0; i <= 24; ++i )
	{
		auto d = 65536 * i / 24;
		cout << right << fixed << setprecision( 2 );
		cout << "sin( ";
		cout << setw( 5 ) << d;
		cout << " / 32768 pi rad ) = ";
		cout << setw( 5 ) << st.get< 256 >( d ) << endl;
	}

	system( "pause" );
}
