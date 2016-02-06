
#ifndef AGATE_PRIS_NOER_CONFIG_DEPRECATED_HPP
#define AGATE_PRIS_NOER_CONFIG_DEPRECATED_HPP

#include <boost/config/compiler/visualc.hpp>

#ifdef BOOST_MSVC
#define AGATE_PRIS_NOER_DEPRECATED __declspec( deprecated )
#else
#deinfe AGATE_PRIS_NOER_DEPRECATED [[deprecated]]
#endif

#endif
