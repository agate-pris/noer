
#ifndef AGATE_PRIS_NOER_SIN_HPP
#define AGATE_PRIS_NOER_SIN_HPP

#include <agate_pris/noer/sin_table.hpp>
#include <agate_pris/noer/angle.hpp>

namespace agate_pris
{
	namespace noer
	{
		template
		<
			typename SinTableElement, std::size_t SinTableDivision,
			typename AngleMagnitude, unsigned int AnglePrecision
		>
		inline auto sin
		(
			const sin_table< SinTableElement, SinTableDivision >& st,
			const angle< AngleMagnitude, AnglePrecision >& d
		)
		{
			return st.get< d.k_straight_quantity / st.k_straight >( d.get() );
		}
	}
}

#endif
