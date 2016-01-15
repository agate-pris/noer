
#include <agate_pris/noer/collision_detection/point.hpp>
#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/algorithms/intersects.hpp>
#include <agate_pris/noer/exact_number.hpp>
#include <iostream>

int main()
{
	using coordinate = agate_pris::noer::exact_number< int >;
	using point      = agate_pris::noer::collision_detection::point< coordinate, 2 >;
	using box        = boost::geometry::model::box< point >;

	point x( 0, 0 );
	point y( 3, 3 );
	box b1( x, y );
	box b2( point( 2, 2 ), point( 5, 5 ) );

	std::cout << boost::geometry::intersects( b1, b2 ) << std::endl;
}
