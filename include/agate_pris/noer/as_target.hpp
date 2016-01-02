
#ifndef AGATE_PRIS_NOER_AS_TARGET_HPP
#define AGATE_PRIS_NOER_AS_TARGET_HPP

#include <utility>
#include <agate_pris/noer/eval.hpp>

namespace agate_pris
{
	namespace noer
	{
		template< typename Arg >
		class target
		{
			private:
			Arg&& m_holded;

			public:
			target( Arg&& arg )
				: m_holded( std::forward< Arg >( arg ) )
			{}
			Arg&& get()
			{
				return m_holded;
			}
		};

		template< typename Arg >
		inline target< Arg > as_target( Arg&& arg )
		{
			return target< Arg >( std::forward< Arg >( arg ) );
		}

		// operator +
		template< typename Lhs, typename Rhs >
		auto operator + ( target< Lhs >& l, const Rhs& r )
		{
			return add_l( lhs.get(), rhs );
		}
		template< typename Lhs, typename Rhs >
		auto operator + ( const Lhs& l, target< Rhs >& r )
		{
			return add_r( lhs.get(), rhs );
		}

		// operator -
		template< typename Lhs, typename Rhs >
		auto operator - ( target< Lhs >& l, const Rhs& r )
		{
			return sub_l( l, r );
		}
		template< typename Lhs, typename Rhs >
		auto operator - ( const Lhs& l, target< Rhs >& r )
		{
			return sub_r( l, r );
		}

		// operator *
		template< typename Lhs, typename Rhs >
		auto operator * ( target< Lhs >& l, const Rhs& r )
		{
			return mul_l( l, r );
		}
		template< typename Lhs, typename Rhs >
		auto operator * ( const Lhs& l, target< Rhs >& r )
		{
			return mul_r( l, r );
		}

		// operator /
		template< typename Lhs, typename Rhs >
		auto operator / ( target< Lhs >& l, const Rhs& r )
		{
			return div_l( l, r );
		}
	}
}

#endif
