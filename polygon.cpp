#include "polygon.h"
#include <cassert>

using namespace std;

//f(x; y) = (y0 - y1) * x + (x1 - x0)*y + x0 * y1 - x1 *y0 = 0
double implicitLine(vec2 v0, vec2 v1, vec2 p) {
	return( (v0.y()-v1.y())*p.x() + (v1.x()-v0.x())*p.y()  + v0.x()*v1.y() - v1.x()*v0.y() );
}

bool Polygon::eval(double x, double y) {
	//init as inside
	bool inside = true;
	vec2 v1, v2;
	float d1;
	//must at least be a triangle (assuming closed polygon not line)
	assert(theVerts.size() >=3);

	std::vector<vec2>::iterator nxt = theVerts.begin();
	vec2 start = theVerts.at(0);

	v1 = start;
	//cout << "start: " << start <<  " point " << x << " " << y << endl;
	//use iterator loop
	for (std::vector<vec2>::iterator it = theVerts.begin() ; 
		it != theVerts.end(); ++it) {

		//advance to the next vertex
		nxt++;
		//if it is valid process the line
		if (nxt != theVerts.end()){
			v2 = *nxt;
			//cout <<  "v1: " << v1 << endl;
			//cout <<  "v2: " << v2 << endl;
			//if point falls outside any line
			d1 = implicitLine(v1, v2, vec2(x, y));
			//cout << "dist: " << d1 << endl;
			if ( d1 < 0) {
				inside = false;
			}
		} 
		//if valid set up for the next line
		v1 = v2;
	}
	//do final line
	//cout << "final line: (v2, s): " << v2 << "  " << start << endl;
	d1 = implicitLine(v2, start, vec2(x, y));
	//cout << "dist: " << d1 << endl;
	if (d1 < 0) {
		inside = false;
	}
	
	return inside;
}
