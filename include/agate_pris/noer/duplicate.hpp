
#ifndef AGATE_PRIS_NOER_DUPLICATE_HPP
#define AGATE_PRIS_NOER_DUPLICATE_HPP

#include <utility>
#include <type_traits>

namespace agate_pris
{
	namespace noer
	{
		template< typename Arg >
		inline auto duplicate( Arg&& arg )noexcept
		(
			!std::is_reference<        Arg >::value && std::is_nothrow_move_assignable<                  Arg   >::value ||
			 std::is_lvalue_reference< Arg >::value && std::is_nothrow_copy_constructible< std::decay_t< Arg > >::value
		)
		{
			return std::decay_t< Arg >( std::forward< Arg >( arg ) );
		}
	}
}

#endif // AGATE_PRIS_NOER_DUPLICATE_HPP
