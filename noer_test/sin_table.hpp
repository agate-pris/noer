
#define NOMINMAX

#include <iostream>
#include <iomanip>

#include <agate_pris/noer/bbp_formula.hpp>
#include <agate_pris/noer/sin_table.hpp>
#include <agate_pris/noer/fixed_point.hpp>

int main()
{
	using namespace std;
	using namespace agate_pris::noer;

	auto pi = bbp_formula( 10 );
	auto f = [ &pi ]( std::size_t i )
	{
		return sin_approximation<>( pi * 2 * i / 256, 10 );
	};
	sin_table< fixed_point< int, 10 >, 256 > st( f );

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
		cout << setw( 5 ) << static_cast< double >( st.get< 256 >( d ) ) << endl;
	}

	system( "pause" );
}
