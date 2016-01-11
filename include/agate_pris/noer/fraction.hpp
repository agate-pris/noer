
#ifndef AGATE_PRIS_NOER_FRACTION_HPP
#define AGATE_PRIS_NOER_FRACTION_HPP

#include <type_traits>

namespace agate_pris
{
	namespace noer
	{
		namespace detail
		{
			namespace fraction
			{
				template< typename Repr, bool = std::is_empty< Repr >::value >
				struct holder;

				template< typename Repr >
				struct holder< Repr, true > : Repr {};

				template< typename Repr >
				struct holder< Repr, false >
				{
					Repr value;
				};

				template< typename Repr > struct numerator   : holder< Repr > {};
				template< typename Repr > struct denominator : holder< Repr > {};
			}
		}

		template< typename Numerator, typename Denominator >
		class fraction 
		: detail::fraction::numerator< Numerator >
		, detail::fraction::denominator< Denominator >
		{
		};
	}
}

#endif
