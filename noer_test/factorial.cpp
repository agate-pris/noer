#include <iostream>
#include <agate_pris/noer/factorial.hpp>

#include "factorial.hpp"

namespace test
{
	void factorial(int n)
	{
		using namespace agate_pris;
		using namespace std;
		for (int i = 0; i < n; ++i)
		{
			cout << "!" << i << " = " << noer::factorial<>(i) << endl;
		}
	}
}
