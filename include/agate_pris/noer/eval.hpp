
#ifndef AGATE_PRIE_NOER_EVAL_HPP
#define AGATE_PRIE_NOER_EVAL_HPP

namespace agate_pris
{
	namespace noer
	{
		namespace eval
		{
			template< typename Lhs, typename Rhs >
			inline auto add_l( Lhs l, const Rhs& r )
			{
				return l += r;
			}

			template< typename Lhs, typename Rhs >
			inline auto add_r( const Lhs& l, Rhs r )
			{
				return r += l;
			}

			template< typename Lhs, typename Rhs >
			inline auto sub_l( Lhs l, const Rhs& r )
			{
				return l -= r;
			}

			template< typename Lhs, typename Rhs >
			inline auto mul_l( Lhs l, const Rhs& r )
			{
				return l *= r;
			}

			template< typename Lhs, typename Rhs >
			inline auto mul_r( const Lhs& l, Rhs r )
			{
				return r *= l;
			}
		}
	}
}

#endif
