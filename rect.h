#ifndef RECT_H
#define RECT_H

#include "vec2.h"
#include "shape.h"
using namespace std;


/* simple data representation of a rectangle */
class Rect : public shape {
  public:
	Rect(double lX, double lY, double rX, double rY, color C, double deep) : shape{C, deep},
		upperL(lX, lY), lowerR(rX, rY) {}
	
	Rect(vec2(left), vec2(right), color C, double deep) : shape{C, deep},
		upperL(left), lowerR(right) {}
	Rect(vec2(left), double width, double height, color C, double deep) : shape{C, deep},
		upperL(left), lowerR(left.x()+width,left.y()+height) {}

	bool eval(double x, double y) override {
		if ((x >= upperL.x() && x <= lowerR.x()) && (y >= upperL.y() && y <= lowerR.y())) {
			return true;
		}
		return false;
	}

	void setColor(color col) { inC = color{0, 0, col.b()}; }

	void translate(vec2 offset) {
		upperL += offset;
		lowerR += offset;
	}

	double getWidth() const {return lowerR.x() - upperL.x(); }
	double getHeight() const {return lowerR.y() - upperL.y(); }
	double getArea() const {return (lowerR.x() - upperL.x())*(lowerR.y() - upperL.y());}

	void setLCorner(vec2 inLCor) { upperL = inLCor; }
	void setRCorner(vec2 inRCor) {lowerR = inRCor;}

	void validate() override{
		try{
			if(upperL.x()<0||upperL.y()<0||lowerR.x()<0||lowerR.y()<0) throw "rect vert less zero";
		}
		catch(const char* msg){
			inC.setC(color(0));
			// setColor(color(0));
			cout<<msg<<endl;
		}
		try{
			if(upperL.x()>lowerR.x()||upperL.y()>lowerR.y()) 
				throw "rect order incorrect";
		}
		catch(const char* msg){
			if(upperL.x()>lowerR.x()){
				double temp = upperL.x();
				upperL.setX(lowerR.x());
				lowerR.setX(temp);
			}
			if(upperL.y()>lowerR.y()){
				double temp = upperL.y();
				upperL.setY(lowerR.y());
				lowerR.setY(temp);
			}
			// cout<<"setting red"<<endl;
			inC.setC(color(255,0,0));
			cout<<msg<<endl;
		}

	}
  private:
	vec2 upperL;
	vec2 lowerR;

};

#endif
