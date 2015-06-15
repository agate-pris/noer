#ifndef AGATE_PRIS_NOER_FIXED_POINT_NUMBER_HPP
#define AGATE_PRIS_NOER_FIXED_POINT_NUMBER_HPP

#include <boost/operators.hpp>

#include <cstdint>

namespace agate_pris
{
	namespace noer
	{
		template< int FractionalBitsNum, typename ValueType = std::int_fast32_t, typename TemporaryType = std::int_fast64_t >
		class fixed_point_number
		: boost::addable< fixed_point_number< FractionalBitsNum, ValueType, TemporaryType >
		, boost::subtractable< fixed_point_number< FractionalBitsNum, ValueType, TemporaryType >
		, boost::multipliable< fixed_point_number< FractionalBitsNum, ValueType, TemporaryType >
		, boost::dividable< fixed_point_number< FractionalBitsNum, ValueType, TemporaryType >
		, boost::less_than_comparable< fixed_point_number< FractionalBitsNum, ValueType, TemporaryType >
		, boost::equivalent< fixed_point_number< FractionalBitsNum, ValueType, TemporaryType >
		, boost::equality_comparable< fixed_point_number< FractionalBitsNum, ValueType, TemporaryType >
		> > > > > > >
		{
		private:
			static_assert(1 <= FractionalBitsNum, "error: 0 >= FractionalBitsNum");
			static const int k_scaling_factor = 1 << (FractionalBitsNum - 1);
			ValueType m_value;
		public:
			using type = fixed_point_number < FractionalBitsNum, ValueType, TemporaryType > ;
			type& operator+=(const type& rhs);
			type& operator-=(const type& rhs);
			type& operator*=(const type& rhs);
			type& operator/=(const type& rhs);
			bool operator<(const type& rhs);
		};

		template< int FractionalBitsNum, typename ValueType, typename TemporaryType >
		fixed_point_number < FractionalBitsNum, ValueType, TemporaryType >&
		fixed_point_number < FractionalBitsNum, ValueType, TemporaryType >::operator+=
		(const fixed_point_number < FractionalBitsNum, ValueType, TemporaryType >& rhs)
		{
			m_value += rhs.m_value;
			return *this;
		}

		template< int FractionalBitsNum, typename ValueType, typename TemporaryType >
		fixed_point_number < FractionalBitsNum, ValueType, TemporaryType >&
		fixed_point_number < FractionalBitsNum, ValueType, TemporaryType >::operator-=
		(const fixed_point_number< FractionalBitsNum, ValueType, TemporaryType >& rhs)
		{
			m_value -= rhs.m_value;
			return *this;
		}

		template< int FractionalBitsNum, typename ValueType, typename TemporaryType >
		fixed_point_number < FractionalBitsNum, ValueType, TemporaryType >&
		fixed_point_number < FractionalBitsNum, ValueType, TemporaryType >::operator*=
		(const fixed_point_number< FractionalBitsNum, ValueType, TemporaryType >& rhs)
		{
			m_value = (static_cast<TemporaryType>(m_value)* rhs.m_value) / k_scaling_factor;
			return *this;
		}

		template< int FractionalBitsNum, typename ValueType, typename TemporaryType >
		fixed_point_number < FractionalBitsNum, ValueType, TemporaryType >&
		fixed_point_number < FractionalBitsNum, ValueType, TemporaryType >::operator/=
		(const fixed_point_number< FractionalBitsNum, ValueType, TemporaryType >& rhs)
		{
			m_value = ( static_cast< TemporaryType >( m_value ) * k_scaling_factor ) / rhs.m_value;
			return *this;
		}

		template< int FractionalBitsNum, typename ValueType, typename TemporaryType >
		bool fixed_point_number < FractionalBitsNum, ValueType, TemporaryType >::operator<
		(const fixed_point_number < FractionalBitsNum, ValueType, TemporaryType >& rhs)
		{
			return m_value < rhs.m_value;
		}
	}
}

#endif // AGATE_PRIS_NOER_FIXED_POINT_NUMBER_HPP
