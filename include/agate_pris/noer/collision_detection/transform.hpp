
#ifndef AGATE_PRIS_NOER_COLLISION_DETECTION_TRANSFORM_HPP
#define AGATE_PRIS_NOER_COLLISION_DETECTION_TRANSFORM_HPP

#include <boost/geometry/algorithms/transform.hpp>

namespace agate_pris
{
    namespace noer
    {
        namespace geometry
        {
            /// @brief \~english transform object from source to target
            ///        \~japanese ソースからターゲットへオブジェクトを変換します。
            /// @details \~english defaultly call `boost::geometry::transform` .
            /// When Boost.Geometry cannnot traits object well,
            /// overload this function and call it.
            /// \~japanese デフォルトでは `boost::geometry::transform` を呼び出します。
            /// Boost.Geometryが上手くオブジェクトを扱えない時、
            /// この関数をオーバロードして使用します。
            // when Boost.Geometry cannnot traits well.
            template< typename Source, typename Target >
            bool transform( Source const& s, Target& t )
            {
                return boost::geometry::transform( s, t );
            }
        }
    }
}

#endif
