
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
		};
	}
}

#endif
