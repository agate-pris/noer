#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <Windows.h>
#include <agate_pris/noer/integer_power.hpp>
#include <agate_pris/noer/bbp_formula.hpp>
#include <agate_pris/noer/fixed_point_number.hpp>

#include "factorial.hpp"

int main()
{
	using namespace std;
	using namespace agate_pris::noer;

	fixed_point_number< 8, int > fpn;
	fpn = fpn / fpn;

	for (int i = 0; i < 10; ++i)
	{
		auto result = bbp_formula(i + 1);
		cout << fixed << setprecision( 16 ) << result.convert_to< double >() << "(" << result << ")" << endl;
	}

	test::factorial(5);
	system("pause");
}
