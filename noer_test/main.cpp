#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <Windows.h>

#undef max
#undef min

#include <agate_pris/noer/pow.hpp>
#include <agate_pris/noer/bbp_formula.hpp>
#include <agate_pris/noer/fixed_point_number.hpp>
#include <agate_pris\noer\degree.hpp>
#include <agate_pris/noer/excess_k.hpp>


#include "factorial.hpp"

int main()
{
	using namespace std;
	using namespace agate_pris::noer;

	excess_k< unsigned int, 1024 > e( 100 );
	cout << static_cast< int >( e ) << endl;
	cout << static_cast< int >( e.get() ) << endl;

	fixed_point_number< 8, int > fpn;
	fpn = fpn / fpn;

	for (int i = 0; i < 10; ++i)
	{
		auto result = bbp_formula(i + 1);
		cout << fixed << setprecision( 16 ) << result.convert_to< double >() << "(" << result << ")" << endl;
	}

	test::factorial(5);
	degree<int, 8> d;
	system("pause");
}
