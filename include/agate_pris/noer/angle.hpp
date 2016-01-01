
#ifndef AGATE_PRIS_NOER_ANGLE_HPP
#define AGATE_PRIS_NOER_ANGLE_HPP

#include <type_traits>

#include <agate_pris\noer\pow.hpp>

namespace agate_pris
{
	namespace noer
	{
		// Quantity : 角度の大きさを保持するための型です
		// Precision : 角度の大きさの精度です。一周を2のPrecision乗に分割します。
		template< typename Quantity, unsigned int Precision >
		class angle
		{
			static_assert(std::is_integral< Quantity >::value, "angle::quantity_type は整数型でなければなりません。あるいは、angleを特殊化する必要があります。");
			static_assert(3 < Precision, "Precisionは3より大きい値でなければなりません。");
		private:
			Quantity m_quantity;
		public:
			static constexpr const Quantity k_full     = pow< Quantity, 2, Precision >();
			static constexpr const Quantity k_straight = pow< Quantity, 2, Precision - 1 >();
			static constexpr const Quantity k_right    = pow< Quantity, 2, Precision - 2 >();

			inline const Quantity& get()const
			{
				return m_quantity;
			}
			inline Quantity& get()
			{
				return m_quantity;
			}
			inline void normalize()
			{
				m_quantity %= k_full;
			}
		};
	}
}

#endif // AGATE_PRIS_NOER_ANGLE_HPP
