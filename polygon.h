#ifndef POLY_H
#define POLY_H
#include <vector>
#include "vec2.h"
#include "color.h"
#include "shape.h"
#include <algorithm>

/* simple data representation of an implicit ellipse */
class Polygon : public shape {
  public:

	Polygon(vec2 v1, double d, color C) : shape{C,d} {
		theVerts.push_back(v1);
	}

	bool eval(double x, double y) override;
	void addVert(vec2 inV) { theVerts.push_back(inV); }

	double getMinX() {
		return min_element(theVerts.begin(), theVerts.end(), [](vec2 l, vec2 r){
					return l.x() < r.x();
      				}
      			)->x();
	}

	double getMinY() {
		vec2 min 
      		= *min_element(theVerts.begin(), theVerts.end(), [](vec2 l, vec2 r){
					return l.y() < r.y();
      				}
      			);
      	return min.y();
	}

	double getMaxX() {
		vec2 max 
      		= *max_element(theVerts.begin(), theVerts.end(), [](vec2 l, vec2 r){
					return l.x() < r.x();
      				}
      			);
      	return max.x();
	}

	double getMaxY(){
		vec2 max 
      		= *max_element(theVerts.begin(), theVerts.end(), [](vec2 l, vec2 r){
					return l.y() < r.y();
      				}
      			);
      	return max.y();
	}

  private:
	std::vector<vec2> theVerts;

};

#endif
