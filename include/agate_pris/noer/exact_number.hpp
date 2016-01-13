
#ifndef AGATE_PRIS_NOER_EXACT_NUMBER_HPP
#define AGATE_PRIS_NOER_EXACT_NUMBER_HPP

#include <type_traits>
#include <limits>

namespace agate_pris
{
	namespace noer
	{
		// forward declation for free function
		template< typename Repr > class exact_number;

		// hide a function from ADL
		namespace exact_number_hide
		{
			template< typename Repr >
			struct get_impl
			{
				static inline auto const& get( exact_number< Repr > const& n );
				static inline auto&       get( exact_number< Repr >&       n );
			};


			/// @brief \~japanese `exact_number` の内部表現にアクセス
			///        \~english  access to the internal representation of `exact_number`

			/// @attention \~japanese この関数はADLによって発見されない。
			///            \~english  This function cannnod be found by ADL.

			/// @details \~japanese 以下のように呼び出す。
			///          \~english  call as below.
			/// \~
			/// ~~~{.cpp}
			/// auto i = agate_pris::noer::get( num );
			/// ~~~

			/// @relates agate_pris::noer::exact_number
			
			/// @{
			template< typename Repr >
			inline auto const& get( const exact_number< Repr >& n )
			{
				return get_impl< Repr >::get( n );
			}
			template< typename Repr >
			inline auto& get( exact_number< Repr >& n )
			{
				return get_impl< Repr >::get( n );
			}
			/// @}
		}

		/// @class exact_number

		/// @brief \~japanese 厳密な数値を取り扱うためのクラステンプレート
		///        \~english  class template for traiting exact numbers

		/// @attention \~japanese `numeric_limits< Repr >::is_exact` は `true` でなければならない。
		///            \~english  `numeric_limits< Repr >::is_exact` must be `true` .

		/// @tparam Repr \~japanese 内部で保持する値を表現する型
		///              \~english  represent number as implemention

		/// @details \~japanese `exact_number` は以下のように使う  
		///          \~english  Use `exact_number` like this
		///          \~
		/// ~~~{.cpp}
		/// exact_number< int > v;
		/// ~~~
		template< typename Repr >
		class exact_number
		{
			friend exact_number_hide::get_impl< Repr >;
			private:
			Repr m_repr;
			public:
			/// @brief \~japanese テンプレート引数 `Repr` の using declation
			///        \~english  declation of template argument `Repr`
			using value_type = Repr;

			//@{
			/// @brief \~japanese デフォルトコンストラクタ
			///        \~english  default constructor
			exact_number() = default;
			/// @brief \~japanese コピーコンストラクタ
			///        \~ensligh  copy constructor
			exact_number( const exact_number< Repr >& ) = default;
			/// @brief \~japanese ムーブコンストラクタ
			///        \~english  move constructor
			exact_number( exact_number< Repr >&& ) = default;
			/// @brief \~japanese コピー代入演算子
			///        \~english  copy assignment operator
			exact_number< Repr >& operator = ( const exact_number< Repr >& ) = default;
			/// @brief \~japanese ムーブ代入演算子
			///        \~english  move assignment operator
			exact_number< Repr >& operator = ( exact_number< Repr >&& ) = default;
			//@}

			//@{
			template< typename Arg >
			exact_number( const exact_number< Arg >& arg );
			template< typename Rhs >
			exact_number< Repr >& operator = ( const exact_number< Rhs >& rhs );
			//@}

			//@{
			template< typename Arg, std::enable_if_t< std::is_fundamental< std::decay_t< Arg > >::value >* = nullptr >
			exact_number( Arg&& arg );
			template< typename Rhs, std::enable_if_t< std::is_fundamental< std::decay_t< Rhs > >::value >* = nullptr >
			exact_number< Repr >& operator = ( Rhs&& rhs );
			//@}

			//@{
			template< typename Target >
			inline operator Target() const;
			//@}

			//@{
			template< typename Rhs, std::enable_if_t< std::is_fundamental< Rhs >::value >* = nullptr >
			exact_number< Repr >& operator += ( const Rhs& rhs );
			template< typename Rhs, std::enable_if_t< std::is_fundamental< Rhs >::value >* = nullptr >
			exact_number< Repr >& operator -= ( const Rhs& rhs );
			template< typename Rhs, std::enable_if_t< std::is_fundamental< Rhs >::value >* = nullptr >
			exact_number< Repr >& operator *= ( const Rhs& rhs );
			template< typename Rhs, std::enable_if_t< std::is_fundamental< Rhs >::value >* = nullptr >
			exact_number< Repr >& operator /= ( const Rhs& rhs );
			//@}
		};

		namespace exact_number_hide
		{
			template< typename Repr >
			auto& get_impl< Repr >::get( exact_number< Repr >& num )
			{
				return num.m_repr;
			}
			template< typename Repr >
			auto const& get_impl< Repr >::get( exact_number< Repr > const& num )
			{
				return num.m_repr;
			}
		}

		using exact_number_hide::get;

		/// @brief \~japanese テンプレート引数 `Repr` の異なる `exact_number` 用コンストラクタ
		///        \~english  constructor for `exact_number` with different template argument `Repr`

		/// @details \~japanese メンバ変数 `m_repr` は以下の式によって初期化される。
		///          \~english  member variable `m_repr` is initialized by the following expression.
		///          \~
		/// ~~~{.cpp}
		/// m_repr( static_cast< Repr >( arg ) )
		/// ~~~
		template< typename Repr >
		template< typename Arg >
		exact_number< Repr >::exact_number( const exact_number< Arg >& arg )
		: m_repr( static_cast< Repr >( arg ) )
		{}

		/// @brief \~japanese テンプレート引数 `Repr` の異なる `exact_number` 用コピー代入演算子
		///        \~english  copy assignment operator for `exact_number` with different template argument `Repr`

		/// @details \~japanese 以下の式によって引数 `rhs` をメンバ変数 `m_repr` に代入する。
		///          \~english  assign argument rhs for member variable `m_repr` by the following expression.
		///          \~
		/// ~~~{.cpp}
		/// m_repr = static_cast< Repr >( arg );
		/// ~~~
		template< typename Repr >
		template< typename Rhs >
		exact_number< Repr >& exact_number< Repr >::operator = ( const exact_number< Rhs >& arg )
		{
			m_repr = static_cast< Repr >( arg );
		}

		/// @brief \~japanese 基本型に対するコンストラクタ
		///        \~english  constructor for fundamental type

		/// @attention \~japanese `numeric_limits< std::decay_t< Arg > >::is_exact` は `true` でなければならない。
		///            \~english  `numeric_limits< std::decay_t< Arg > >::is_exact` must be `true` .

		/// @tparam Arg \~japanese 引数の型
		///             \~english  Argument's type

		/// @details \~japanese メンバ変数 `m_repr` は以下の式によって初期化される。
		///          \~english  member variable `m_repr` is initialized by the following expression.
		///          \~
		/// ~~~{.cpp}
		/// m_repr( std::forward< Arg >( arg ) )
		/// ~~~
		template<typename Repr>
		template<typename Arg, std::enable_if_t< std::is_fundamental< std::decay_t< Arg > >::value >* >
		inline exact_number< Repr >::exact_number( Arg&& arg )
		: m_repr( std::forward< Arg >( arg ) )
		{
			using std::numeric_limits;
			static_assert( numeric_limits< std::decay_t< Arg > >::is_exact, "Arg must be exact!" );
		}

		/// @brief \~japanese 基本型に対するコピー/ムーブ代入演算子
		///        \~english  copy/move assignment operator for fundamental type

		/// @attention \~japanese `numeric_limits< std::decay_t< Rhs > >::is_exact` は `true` でなければならない。
		///            \~english  `numeric_limits< std::decay_t< Rhs > >::is_exact` must be `true` .

		/// @tparam Rhs \~japanese 右辺の型
		///             \~english  type of right hand side

		/// @details \~japanese 以下の式によって引数 `rhs` をメンバ変数 `m_repr` に代入する。
		///          \~english  assign argument rhs for member variable `m_repr` by the following expression.
		///          \~
		/// ~~~{.cpp}
		/// m_repr = std::forward< Repr >( rhs );
		/// ~~~
		template<typename Repr>
		template< typename Rhs, std::enable_if_t< std::is_fundamental< std::decay_t< Rhs > >::value >* >
		inline exact_number< Repr >& exact_number< Repr >::operator = ( Rhs&& rhs )
		{
			using std::numeric_limits;
			static_assert( numeric_limits< std::decay_t< Rhs > >::is_exact, "Rhs must be exact!" );
			m_repr = std::forward< Repr >( rhs );
			return *this;
		}

		/// @brief \~japanese 任意の型への変換演算子
		///        \~english  conversion operator for any type

		/// @attention \~japanese この関数は変換先の型が厳密な数値型であるか否かを問わない。
		///                       厳密な数値演算が必要な時、型合わせのためだけに本関数を使用してはならない。
		///            \~english  This funtion does not matter weather destination type of conversion is exact or not.
		///                       It should never be used only for type matching when exact arithmetic operation is necessary.

		/// @details \~japanese 以下の式によって型変換を行う。
		///          \~english  convet by following expression.
		///          \~
		/// ~~~{.cpp}
		/// return static_cast< Target >( m_repr );
		/// ~~~
		template<typename Repr>
		template< typename Target >
		inline exact_number< Repr >::operator Target() const
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Target >::is_exact, "Target must be exact!" );
			return static_cast< Target >( m_repr );
		}

		//@{

		/// @brief \~japanese 基本型に対する複合代入演算子
		///        \~english  compound assignment operator for any fundamental type

		/// @attention \~japanese `numeric_limits< Rhs >::is_exact` は `true` でなければならない。
		///            \~english  `numeric_limits< Rhs >::is_exact` must be `true` .

		/// @param rhs \~japanese 右辺
		///            \~english  right hand side

		/// @tparam Rhs \~japanese 右辺の型
		///             \~english  type of right hand side
		template< typename Repr >
		template< typename Rhs, std::enable_if_t< std::is_fundamental< Rhs >::value >* >
		exact_number< Repr >& exact_number< Repr >::operator += ( const Rhs& rhs )
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
			m_repr += rhs
			return *this;
		}
		template< typename Repr >
		template< typename Rhs, std::enable_if_t< std::is_fundamental< Rhs >::value >* >
		exact_number< Repr >& exact_number< Repr >::operator -= ( const Rhs& rhs )
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
			m_repr -= rhs
			return *this;
		}
		template< typename Repr >
		template< typename Rhs, std::enable_if_t< std::is_fundamental< Rhs >::value >* >
		exact_number< Repr >& exact_number< Repr >::operator *= ( const Rhs& rhs )
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
			m_repr *= rhs
			return *this;
		}
		template< typename Repr >
		template< typename Rhs, std::enable_if_t< std::is_fundamental< Rhs >::value >* >
		exact_number< Repr >& exact_number< Repr >::operator /= ( const Rhs& rhs )
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
			m_repr /= rhs
			return *this;
		}
		//@}

		/// @relates agate_pris::noer::exact_number

		/// @brief \~japanese 基本型または `exact_number` と `exact_number` の演算
		///        \~english  operation for fundamental type or `exact_number` and `exact_number
		
		/// @attention \~japanese `numeric_limits< Lhs >::is_exact` または同 `Rhs` は `true` でなければならない。
		///            \~english  `numeric_limits< Lhs >::is_exact` or same of `Rhs` must be `true` .
		
		/// @param lhs \~japanese 左辺
		///            \~english  left hand side
		
		/// @param rhs \~japanese 右辺
		///            \~english  right hand side
		
		/// @tparam Lhs \~japanese 左辺の型またはそのメンバの型
		///             \~english  type of left hand side or member of it
		
		/// @tparam Rhs \~japanese 右辺の型またはそのメンバの型
		///             \~english  type of right hand side or member of it
		
		/// @details \~japanese 戻り値の型は演算結果を保持する `exact_number` になる。
		///          \~english  Return value type is `exact_number` holding result type of arithmetic operation.

		/// @{
		template< typename Lhs, typename Rhs, std::enable_if_t< std::is_fundamental< Lhs >::value >* = nullptr >
		auto operator + ( const Lhs& lhs, const exact_number< Rhs >& rhs ) -> exact_number< decltype( std::declval< Lhs >() + std::declval< Rhs >() ) >
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Lhs >::is_exact, "Lhs must be exact!" );
			return exact_number< decltype( std::declval< Lhs >() + std::declval< Rhs >() ) >( lhs + get( rhs ) );
		}
		template< typename Lhs, typename Rhs, std::enable_if_t< std::is_fundamental< Lhs >::value >* = nullptr >
		auto operator - ( const Lhs& lhs, const exact_number< Rhs >& rhs ) -> exact_number< decltype( std::declval< Lhs >() - std::declval< Rhs >() ) >
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Lhs >::is_exact, "Lhs must be exact!" );
			return exact_number< decltype( std::declval< Lhs >() - std::declval< Rhs >() ) >( lhs - get( rhs ) );
		}
		template< typename Lhs, typename Rhs, std::enable_if_t< std::is_fundamental< Lhs >::value >* = nullptr >
		auto operator * ( const Lhs& lhs, const exact_number< Rhs >& rhs ) -> exact_number< decltype( std::declval< Lhs >() * std::declval< Rhs >() ) >
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Lhs >::is_exact, "Lhs must be exact!" );
			return exact_number< decltype( std::declval< Lhs >() * std::declval< Rhs >() ) >( lhs * get( rhs ) );
		}
		template< typename Lhs, typename Rhs, std::enable_if_t< std::is_fundamental< Lhs >::value >* = nullptr >
		auto operator / ( const Lhs& lhs, const exact_number< Rhs >& rhs ) -> exact_number< decltype( std::declval< Lhs >() / std::declval< Rhs >() ) >
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Lhs >::is_exact, "Lhs must be exact!" );
			return exact_number< decltype( std::declval< Lhs >() / std::declval< Rhs >() ) >( lhs / get( rhs ) );
		}

		template< typename Lhs, typename Rhs, std::enable_if_t< std::is_fundamental< Rhs >::value >* = nullptr >
		auto operator + ( const exact_number< Lhs >& lhs, const Rhs& rhs ) -> exact_number< decltype( std::declval< Lhs >() + std::declval< Rhs >() ) >
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
			return exact_number< decltype( std::declval< Lhs >() + std::declval< Rhs >() ) >( get( lhs ) + rhs );
		}
		template< typename Lhs, typename Rhs, std::enable_if_t< std::is_fundamental< Rhs >::value >* = nullptr >
		auto operator - ( const exact_number< Lhs >& lhs, const Rhs& rhs ) -> exact_number< decltype( std::declval< Lhs >() - std::declval< Rhs >() ) >
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
			return exact_number< decltype( std::declval< Lhs >() - std::declval< Rhs >() ) >( get( lhs ) - rhs );
		}
		template< typename Lhs, typename Rhs, std::enable_if_t< std::is_fundamental< Rhs >::value >* = nullptr >
		auto operator * ( const exact_number< Lhs >& lhs, const Rhs& rhs ) -> exact_number< decltype( std::declval< Lhs >() * std::declval< Rhs >() ) >
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
			return exact_number< decltype( std::declval< Lhs >() * std::declval< Rhs >() ) >( get( lhs ) * rhs );
		}
		template< typename Lhs, typename Rhs, std::enable_if_t< std::is_fundamental< Rhs >::value >* = nullptr >
		auto operator / ( const exact_number< Lhs >& lhs, const Rhs& rhs ) -> exact_number< decltype( std::declval< Lhs >() / std::declval< Rhs >() ) >
		{
			using std::numeric_limits;
			static_assert( numeric_limits< Rhs >::is_exact, "Rhs must be exact!" );
			return exact_number< decltype( std::declval< Lhs >() / std::declval< Rhs >() ) >( get( lhs ) / rhs );
		}

		template< typename Lhs, typename Rhs >
		auto operator + ( const exact_number< Lhs >& lhs, const exact_number< Rhs >& rhs ) -> exact_number< decltype( std::declval< Lhs >() + std::declval< Rhs >() ) >
		{
			return exact_number< decltype( std::declval< Lhs >() + std::declval< Rhs >() ) >( get( lhs ) + get( rhs ) );
		}
		template< typename Lhs, typename Rhs >
		auto operator - ( const exact_number< Lhs >& lhs, const exact_number< Rhs >& rhs ) -> exact_number< decltype( std::declval< Lhs >() - std::declval< Rhs >() ) >
		{
			return exact_number< decltype( std::declval< Lhs >() - std::declval< Rhs >() ) >( get( lhs ) - get( rhs ) );
		}
		template< typename Lhs, typename Rhs >
		auto operator * ( const exact_number< Lhs >& lhs, const exact_number< Rhs >& rhs ) -> exact_number< decltype( std::declval< Lhs >() * std::declval< Rhs >() ) >
		{
			return exact_number< decltype( std::declval< Lhs >() * std::declval< Rhs >() ) >( get( lhs ) * get( rhs ) );
		}
		template< typename Lhs, typename Rhs >
		auto operator / ( const exact_number< Lhs >& lhs, const exact_number< Rhs >& rhs ) -> exact_number< decltype( std::declval< Lhs >() / std::declval< Rhs >() ) >
		{
			return exact_number< decltype( std::declval< Lhs >() / std::declval< Rhs >() ) >( get( lhs ) / get( rhs ) );
		}
		/// @}
	}
}

#endif
