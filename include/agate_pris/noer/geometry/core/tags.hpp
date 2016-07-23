
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_TAGS_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_TAGS_HPP

#include <boost/geometry/core/tags.hpp>
#include <boost/mpl/long.hpp>
#include <agate_pris/noer/geometry/core/overload_priolity.hpp>

namespace agate_pris {
namespace noer {
namespace geometry {

using point_tag = boost::geometry::point_tag;
using box_tag = boost::geometry::box_tag;
using segment_tag = boost::geometry::segment_tag;
struct triangle_tag {};
struct polymorphic_tag {};
struct stl_container_tag {};
struct boost_fusion_container_tag {};

namespace traits {

template<>
struct overload_priolity< point_tag >
    : boost::mpl::long_< 1000 >
{};

template<>
struct overload_priolity< box_tag >
    : boost::mpl::long_< 2000 >
{};

template<>
struct overload_priolity< segment_tag >
    : boost::mpl::long_< 3000 >
{};

template<>
struct overload_priolity< triangle_tag >
    : boost::mpl::long_< 4000 >
{};

template<>
struct overload_priolity< polymorphic_tag >
    : boost::mpl::long_< 5000 >
{};

template<>
struct overload_priolity< stl_container_tag >
    : boost::mpl::long_< 6000 >
{};

template<>
struct overload_priolity< boost_fusion_container_tag >
    : boost::mpl::long_< 7000 >
{};

} // traits

} // geometry
} // noer
} // agate_pris

#endif
