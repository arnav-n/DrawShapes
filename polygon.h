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
	bool concave();

  private:
	std::vector<vec2> theVerts;

};

#endif
