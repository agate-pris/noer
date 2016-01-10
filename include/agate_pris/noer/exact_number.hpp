
#ifndef AGATE_PRIS_NOER_EXACT_NUMBER_HPP
#define AGATE_PRIS_NOER_EXACT_NUMBER_HPP

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
			exact_number() = default;
			exact_number( const exact_number< Repr >& ) = default;
			exact_number( exact_number< Repr >&& ) = default;

			//@{
			/// @brief \~japanese 保持している変数の参照を戻すアクセサ
			///        \~english  accessor return reference to holding variable
			Repr&       get()       { return m_repr; }
			/// @brief \~japanese 保持している変数の `const` 参照を戻すアクセサ
			///        \~english  accessor return `const` reference to holding variable
			Repr const& get() const { return m_repr; }
			//@}
		};
	}
}

#endif
