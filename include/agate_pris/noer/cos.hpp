
#ifndef AGATE_PRIS_NOER_COS_HPP
#define AGATE_PRIS_NOER_COS_HPP

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
		inline auto cos
		(
			const sin_table< SinTableElement, SinTableDivision >& st,
			const angle< AngleMagnitude, AnglePrecision >& d
		)
		{
			auto tmp = d.get();
			tmp += d.k_right_quantity;
			return st.get< d.k_straight_quantity / st.k_straight >( tmp );
		}
	}
}

#endif // AGATE_PRIS_NOER_COS_HPP
