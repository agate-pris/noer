
#include <iostream>
#include <agate_pris/noer/sqrt.hpp>

int main()
{
	using namespace std;
	using namespace agate_pris::noer;
	for( unsigned int i = 0; i < 24; ++i )
	{
		cout << static_cast< double >( sqrt( i, 10 ) ) << endl;
	}
}
