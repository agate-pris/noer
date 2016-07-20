
#ifndef AGATE_PRIS_NOER_GEOMETRY_ALGORITHMS_INTERSECTS_POLYMORPHIC_POLYMOCPHIC_HPP
#define AGATE_PRIS_NOER_GEOMETRY_ALGORITHMS_INTERSECTS_POLYMORPHIC_POLYMOCPHIC_HPP

#include <agate_pris/noer/geometry/core/tags.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

template< typename Lhs, typename Rhs >
inline bool intersects( Lhs const& lhs, Rhs const& rhs, polymorphic_tag, polymorphic_tag  )
{
    return lhs.intersects( rhs );
}

} // collision_detection
} // noer
} // agate_pris

#endif // AGATE_PRIS_NOER_GEOMETRY_ALGORITHMS_INTERSECTS_POLYMORPHIC_POLYMOCPHIC_HPP
