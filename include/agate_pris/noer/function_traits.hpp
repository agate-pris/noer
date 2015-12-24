
#ifndef AGATE_PRIS_NOER_FUNCTION_TRAITS_HPP
#define AGATE_PRIS_NOER_FUNCTION_TRAITS_HPP

#include <utility>
#include <type_traits>
#include <tuple>

namespace agate_pris
{
	namespace noer
	{
		namespace detail
		{
			template< typename P > struct function_pointer
			{
				template< typename R                               > static auto argument( R( * )( void       ) ) -> void;
				template< typename R                               > static auto result(   R( * )( void       ) ) -> void;
				template< typename R, typename A                   > static auto argument( R( * )( A          ) ) -> A;
				template< typename R, typename A                   > static auto result(   R( * )( A          ) ) -> R;
				template< typename R, typename A, typename... Args > static auto argument( R( * )( A, Args... ) ) -> std::tuple< A, Args... >;
				template< typename R, typename A, typename... Args > static auto result(   R( * )( A, Args... ) ) -> R;
				using argument_type = decltype( argument( std::declval< P >() ) );
				using result_type   = decltype( result(   std::declval< P >() ) );
			};

			template< typename P > struct member_function_pointer
			{
				template< typename R, typename C                               > static auto argument( R( C::* )( void       )      ) -> void;
				template< typename R, typename C                               > static auto result(   R( C::* )( void       )      ) -> R;
				template< typename R, typename C                               > static auto argument( R( C::* )( void       )const ) -> void;
				template< typename R, typename C                               > static auto result(   R( C::* )( void       )const ) -> R;
				template< typename R, typename C, typename A                   > static auto argument( R( C::* )( A          )      ) -> A;
				template< typename R, typename C, typename A                   > static auto result(   R( C::* )( A          )      ) -> R;
				template< typename R, typename C, typename A                   > static auto argument( R( C::* )( A          )const ) -> A;
				template< typename R, typename C, typename A                   > static auto result(   R( C::* )( A          )const ) -> R;
				template< typename R, typename C, typename A, typename... Args > static auto argument( R( C::* )( A, Args... )      ) -> std::tuple< A, Args... >;
				template< typename R, typename C, typename A, typename... Args > static auto result(   R( C::* )( A, Args... )      ) -> R;
				template< typename R, typename C, typename A, typename... Args > static auto argument( R( C::* )( A, Args... )const ) -> std::tuple< A, Args... >;
				template< typename R, typename C, typename A, typename... Args > static auto result(   R( C::* )( A, Args... )const ) -> R;
				using argument_type = decltype( argument( std::declval< P >() ) );
				using result_type   = decltype( result(   std::declval< P >() ) );
			};

			template< typename C > struct function_object
			{
				using argument_type = typename member_function_pointer< decltype( &C::operator() ) >::argument_type;
				using result_type   = typename member_function_pointer< decltype( &C::operator() ) >::result_type;
			};
		}

		template< typename F > struct function_traits
		: public std::conditional_t
		<
			std::is_member_function_pointer< F >::value,
			detail::member_function_pointer< F >,
			std::conditional_t
			<
				std::is_pointer< F >::value,
				detail::function_pointer< F >,
				detail::function_object< F >
			>
		>
		{};
	}
}

#endif // AGATE_PRIS_NOER_FUNCTION_TRAITS_HPP
