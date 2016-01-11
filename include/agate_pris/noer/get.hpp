
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

		template< typename T >
		inline decltype(auto) get( T&& arg )
		{
			return std::foward< T >( arg ).value;
		}
	}
}

#endif
