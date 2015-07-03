#ifndef AGATE_PRIS_NOER_LERP_HPP
#define AGATE_PRIS_NOER_LERP_HPP

namespace agate_pris
{
	namespace noer
	{
		template< typename X, typename Y >
		Y lerp(const X& x, const X& x0, const X& x1, const Y& y0, const Y& y1)
		{
			const X a = (x - x0) / (x1 - x0);
			return y0 - a * y0 + a * y1;
		}
	}
}

#endif // AGATE_PRIS_NOER_LERP_HPP
