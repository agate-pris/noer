﻿
#ifndef AGATE_PRIS_NOER_ANGLE_HPP
#define AGATE_PRIS_NOER_ANGLE_HPP

#include <type_traits>
#include <utility>
#include <boost/math/constants/constants.hpp>
#include <boost/operators.hpp>
#include <agate_pris\noer\pow.hpp>

namespace agate_pris
{
	namespace noer
	{
		// Quantity : 角度の大きさを保持するための型です
		// Precision : 角度の大きさの精度です。一周を2のPrecision乗に分割します。
		template< typename Quantity, unsigned int Precision >
		class angle
		: public boost::additive< angle< Quantity, Precision > >
		{
			static_assert(std::is_integral< Quantity >::value, "angle::quantity_type は整数型でなければなりません。あるいは、angleを特殊化する必要があります。");
			static_assert(3 < Precision, "Precisionは3より大きい値でなければなりません。");
			private:
			Quantity m_quantity;
		public:
			angle() = default;

			constexpr angle( const Quantity& q ) : m_quantity( q ) {}

			// constants
			static constexpr const Quantity k_full_quantity     = pow< Quantity, 2, Precision >();
			static constexpr const Quantity k_straight_quantity = pow< Quantity, 2, Precision - 1 >();
			static constexpr const Quantity k_right_quantity    = pow< Quantity, 2, Precision - 2 >();

			// constants as function
			static constexpr angle< Quantity, Precision > full();
			static constexpr angle< Quantity, Precision > straight();
			static constexpr angle< Quantity, Precision > right();

			inline const Quantity& get()const
			{
				return m_quantity;
			}
			inline Quantity& get()
			{
				return m_quantity;
			}

			// conversion to radian
			template< typename FloatingPoint, std::enable_if_t< std::is_floating_point< FloatingPoint >::value >* = nullptr >
			operator FloatingPoint()const
			{
				return boost::math::constants::pi< FloatingPoint >() * m_quantity / k_straight_quantity;
			}

			// operator += and -=
			angle< Quantity, Precision >& operator += ( const angle< Quantity, Precision >& rhs )
			{
				m_quantity += rhs.get();
				return *this;
			}

			angle< Quantity, Precision >& operator -= ( const angle< Quantity, Precision >& rhs )
			{
				m_quantity += rhs.get();
				return *this;
			}

			// operator *-
			template< typename Rhs >
			angle< Quantity, Precision >& operator *= ( const Rhs& rhs )
			{
				m_quantity *= rhs;
				return *this;
			}

			// operator *
			template< typename Rhs >
			auto operator * ( const Rhs& rhs )const
			{
				return angle< decltype( std::declval< Quantity >() * std::declval< Rhs >() ), Precision >( m_quantity * rhs );
			}
		};

		template< typename Quantity, unsigned int Precision, 
			      std::enable_if_t< std::is_signed< Quantity >::value >* = nullptr >
		void bound_to_minor( angle< Quantity, Precision >& a )
		{
			a.get() %= a.k_full_quantity;
			if( a.k_straight_quantity <= a.get() )
			{
				a.get() -= a.k_straight_quantity;
				return;
			}
			if( -a.k_straight_quantity > a.get() )
			{
				a.get() += a.k_straight_quantity;
			}
		}

		template<typename Quantity, unsigned int Precision>
		inline constexpr angle<Quantity, Precision> angle<Quantity, Precision>::full()
		{
			return angle<Quantity, Precision>( k_full_quantity );
		}

		template<typename Quantity, unsigned int Precision>
		inline constexpr angle<Quantity, Precision> angle<Quantity, Precision>::straight()
		{
			return angle<Quantity, Precision>( k_straight_quantity );
		}

		template<typename Quantity, unsigned int Precision>
		inline constexpr angle<Quantity, Precision> angle<Quantity, Precision>::right()
		{
			return angle<Quantity, Precision>( k_right_quantity );
		}
	}
}

#endif // AGATE_PRIS_NOER_ANGLE_HPP
