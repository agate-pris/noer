
#ifndef AGATE_PRIS_NOER_DUPLICATE_HPP
#define AGATE_PRIS_NOER_DUPLICATE_HPP

#include <utility>

namespace agate_pris
{
	namespace noer
	{
		template< typename Arg >
		inline Arg duolicate( Arg&& arg )noexcept( noexcept( Arg(Arg&&) ) )
		{
			using std::forward;
			return forward< Arg >( arg );
		}
	}
}

#endif // AGATE_PRIS_NOER_DUPLICATE_HPP
