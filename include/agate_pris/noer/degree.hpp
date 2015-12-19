
#ifndef AGATE_PRIS_NOER_DEGREE_HPP
#define AGATE_PRIS_NOER_DEGREE_HPP

#include <type_traits>

#include <agate_pris\noer\pow.hpp>

namespace agate_pris
{
	namespace noer
	{
		// Magnitude : 角度の大きさを保持するための型です
		// Precision : 角度の大きさの精度です。一周を2のPrecision乗に分割します。
		template< typename Magnitude, unsigned int Precision >
		class degree
		{
			static_assert(std::is_integral< Magnitude >::value, "degree::magnitude_type は整数型でなければなりません。あるいは、degreeを特殊化する必要があります。");
			static_assert(3 < Precision, "Precisionは3より大きい値でなければなりません。");
		private:
			Magnitude m_magnitude;
		public:
			static constexpr const Magnitude k_pi = pow< Magnitude, 2, Precision - 1 >();
			inline const Magnitude& get()const
			{
				return m_magnitude;
			}
			inline Magnitude& get()
			{
				return m_magnitude;
			}
			inline void normalize()
			{
				m_magnitude %= k_pi;
			}
		};
	}
}

#endif // AGATE_PRIS_NOER_DEGREE_HPP
