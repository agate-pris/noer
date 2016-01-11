
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
				template< typename Repr, typename = std::is_empty< Repr > >
				struct holder;

				template< typename Repr >
				struct holder< Repr, std::true_type > : Repr {};

				template< typename Repr >
				struct holder< Repr, std::false_type >
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
