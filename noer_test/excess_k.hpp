
#include <iostream>
#include <agate_pris/noer/excess_k.hpp>

int main()
{
	using namespace std;
	using namespace agate_pris::noer;

	excess_k< unsigned int, 1024 > e( 100 );
	cout << static_cast< int >( e ) << endl;
	cout << static_cast< int >( e.get() ) << endl;

	system( "pause" );
}
