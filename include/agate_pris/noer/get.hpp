
#ifndef AGATE_PRIS_NOER_GET_HPP
#define AGATE_PRIS_NOER_GET_HPP

namespace agate_pris
{
	namespace noer
	{
		template< typename T >
		inline auto& get()
		{
			return T::value;
		}
	}
}

#endif
