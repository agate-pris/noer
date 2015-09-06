
#ifndef AGATE_PRIS_NOER_INTERPOLATION_HPP
#define AGATE_PRIS_NOER_INTERPOLATION_HPP

namespace agate_pris
{
	namespace noer
	{
		enum class interpolation
		{
			k_nearest_neighbor,	// 0次補間 最近傍補間
			k_linear			// 1次補間 線形補間
		};
	}
}

#endif
