
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_CHECK_ZERO_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_CHECK_ZERO_HPP

#include <cstddef>
#include <boost/config.hpp>
#include <agate_pris/noer/collision_detection/point/shared.hpp>

namespace agate_pris {
namespace noer {
namespace collision_detection {
namespace point {
namespace shared {

template< typename Point >
class check_zero
    : public entity< Point >
{
    // constuctor
    public:
    // construct empty shared_ptr
    BOOST_CONSTEXPR check_zero() BOOST_NOEXCEPT_OR_NOTHROW;
    // construct empty shared_ptr
    BOOST_CONSTEXPR check_zero( std::nullptr_t ) BOOST_NOEXCEPT_OR_NOTHROW;

    // construct shared_ptr object that owns same resource as r
    check_zero( check_zero< Point > const& r ) BOOST_NOEXCEPT_OR_NOTHROW;
};

// constructor
// ---------------------------------------------------------------------

// construct empty shared_ptr
template< typename Point >
inline check_zero< Point >::check_zero() BOOST_NOEXCEPT_OR_NOTHROW
    : entity< Point >()
{}

// construct empty shared_ptr
template< typename Point >
inline check_zero< Point >::check_zero( std::nullptr_t ) BOOST_NOEXCEPT_OR_NOTHROW
    : entity< Point >()
{}

// construct shared_ptr object that owns same resource as r
template< typename Point >
inline check_zero< Point >::check_zero( check_zero< Point > const& r ) BOOST_NOEXCEPT_OR_NOTHROW
    : entity< Point >( r.data() )
{}

} // shared
} // point
} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_CHECK_ZERO_HPP
