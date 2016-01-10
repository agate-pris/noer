﻿
#ifndef AGATE_PRIS_NOER_EXACT_NUMBER_HPP
#define AGATE_PRIS_NOER_EXACT_NUMBER_HPP

#include <type_traits>
#include <limits>

namespace agate_pris
{
	namespace noer
	{
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
			//@}

			//@{
			/// @brief \~japanese 保持している変数の参照を戻すアクセサ
			///        \~english  accessor return reference to holding variable
			Repr&       get()       { return m_repr; }
			/// @brief \~japanese 保持している変数の `const` 参照を戻すアクセサ
			///        \~english  accessor return `const` reference to holding variable
			Repr const& get() const { return m_repr; }
			//@}

			template< typename Arg, std::enable_if_t< std::is_fundamental< std::decay_t< Arg > >::value	>* = nullptr >
			exact_number( Arg&& arg );
		};

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
		template<typename Arg, std::enable_if_t< std::is_fundamental< std::decay_t< Arg > >::value	>* >
		inline exact_number< Repr >::exact_number( Arg&& arg )
		: m_repr( std::forward< Arg >( arg ) )
		{
			using std::numeric_limits;
			static_assert( numeric_limits< std::decay_t< Arg > >::is_exact, "Arg must be exact!" );
		}
	}
}

#endif
