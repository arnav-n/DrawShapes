#ifndef COLOR_H
#define COLOR_H

#include <cmath>
#include <iostream>

#include "util.h"

using std::sqrt;

/* A color for a PPM file is red, green blue amounts as whole numbers 0-255 */
class color {
public:
		color(double in1, double in2, double in3) : val{in1, in2, in3} {}
		color() : val{0,0,0} {} //default constructor
		color(double in) : val{in,in,in} {} //alt constructor

		//getters
		double r() const { return val[0]; }
		double g() const { return val[1]; }
		double b() const { return val[2]; }
		double bright() const { return val[0]+val[1]+val[2]; }
		
		void setR(double inX) { val[0] = inX; }
		void setG(double inY) { val[1] = inY; }
		void setB(double inZ) { val[2] = inZ; }
		void setC(color inC) {val[0] = inC.r(); val[1] = inC.g(); val[2] = inC.b();}

		//overload operators
		color& operator+=(const color &v) {
			val[0] += v.val[0];
			val[1] += v.val[1];
			val[2] += v.val[2];
			return *this;
		}

		//mult by scalar
		color& operator*=(const double Sc) {
			val[0] *=Sc; 
			val[1] *=Sc;
			val[2] *=Sc;
			return *this;
		}

		virtual bool operator==(const color& other) const {
        	if (typeid(*this) != typeid(other))
            	return false;

        	return (val[0] == other.val[0] && val[1] == other.val[1] && val[2] == other.val[2]);
    	}

	
		inline static color random() {
			return color(niceRand(), niceRand(), niceRand());
		}
		
		inline static color random(double min, double max) {
			return color(nicerRand(min, max), nicerRand(min, max), nicerRand(min, max));
		}


	private:
		double val[3];
};


#endif
