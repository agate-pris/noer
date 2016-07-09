
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_CHECK_ZERO_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_CHECK_ZERO_HPP

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
};

} // shared
} // point
} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_COLLISION_DETECTION_POINT_SHARED_CHECK_ZERO_HPP
