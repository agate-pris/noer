
#ifndef AGATE_PRIS_NOER_SIN_HPP
#define AGATE_PRIS_NOER_SIN_HPP

#include <agate_pris/noer/sin_table.hpp>
#include <agate_pris/noer/degree.hpp>

namespace agate_pris
{
	namespace noer
	{
		template
		<
			typename SinTableElement, std::size_t SinTableDivision,
			typename DegreeMagnitude, unsigned int DegreePrecision
		>
		inline auto sin
		(
			const sin_table< SinTableElement, SinTableDivision >& st,
			const degree< DegreeMagnitude, DegreePrecision >& d
		)
		{
			return st.get< d.k_pi / st.k_pi >( d.get() );
		}
	}
}

#endif
