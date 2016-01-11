
#ifndef AGATE_PRIS_NOER_FRACTION_HPP
#define AGATE_PRIS_NOER_FRACTION_HPP

#include <type_traits>
#include <agate_pris/noer/get.hpp>

namespace agate_pris
{
	namespace noer
	{
		namespace detail
		{
			namespace fraction
			{
				/// @brief \~japanese 分子または分母を保持する構造体
				///        \~english  struct for hold numerator or denominator
				template< typename Repr, bool = std::is_empty< Repr >::value >
				struct holder;

				template< typename Repr >
				struct holder< Repr, true >
				{
					inline           auto&       get();
					inline constexpr auto const& get() const;
				};
				template< typename Repr >
				struct holder< Repr, false >
				{
					using value_type = Repr;
					Repr value;
					inline           auto&       get();
					inline constexpr auto const& get() const;
				};

				/// @brief \~japanese 分子または分母の値を得る。
				///        \~ensligh  get numerator or denominator.

				/// @{
				template< typename Repr >
				inline auto& holder< Repr, true >::get()
				{
					using agate_pris::noer::get;
					return get< Repr >();
				}
				template< typename Repr >
				inline constexpr auto const& get()const
				{
					using agate_pris::noer::get;
					return get< Repr >();
				}
				template< typename Repr >
				inline auto& holder< Repr, false >::get()
				{
					return value;
				}
				template< typename Repr >
				inline constexpr auto const& holder< Repr, false >::get()const
				{
					return value;
				}
				/// @}

				/// @brief \~japanese 分子を保持する構造体
				///        \~ensligh  struct for hold numerator
				template< typename Repr > struct numerator   : holder< Repr > {};

				/// @brief \~japanese 分母を保持する構造体
				///        \~ensligh  struct for hold denominator
				template< typename Repr > struct denominator : holder< Repr > {};
			}
		}

		template< typename Numerator, typename Denominator >
		class fraction 
		: detail::fraction::numerator< Numerator >
		, detail::fraction::denominator< Denominator >
		{
			public:
			inline           auto&       get_numerator();
			inline constexpr auto const& get_numerator() const;
			inline           auto&       get_denominator();
			inline constexpr auto const& get_denominator() const;
		};

		/// @brief \~japanese 分子を得る
		///        \~ensligh  get numerator

		/// @{
		template< typename Numerator, typename Denominator >
		inline auto& fraction< Numerator, Denominator >::get_numerator()
		{
			return detail::fraction::numerator< Numerator >::get();
		}
		template< typename Numerator, typename Denominator >
		inline constexpr auto const& fraction< Numerator, Denominator >::get_numerator()const
		{
			return detail::fraction::numerator< Numerator >::get();
		}
		/// @}

		/// @brief \~japanese 分母を得る
		///        \~ensligh  get denominator

		/// @{
		template< typename Numerator, typename Denominator >
		inline auto& fraction< Numerator, Denominator >::get_denominator()
		{
			return detail::fraction::denominator< Denominator >::get();
		}
		template< typename Numerator, typename Denominator >
		inline constexpr auto const& fraction< Numerator, Denominator >::get_denominator()const
		{
			return detail::fraction::denominator< Denominator >::get();
		}
		/// @}
	}
}

#endif
