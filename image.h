#ifndef IMAGE_H
#define IMAGE_H

#include <math.h>
#include "color.h"

using namespace std;

class image  {

	public:
		image(int w, int h, color backGround) : width(w), height(h) {
			for(int i=0; i <width*height; i++)
				thePixels.push_back(backGround);
		}

		int w() const {return width; }
		int h() const {return height; }
	    void writePixel(ostream& out, int x, int y, color cOut) const;
	    void writeHeader(ostream& out) const;
	    void writeNewLine(ostream& out) const;
	    void setPixel(int x, int y, color in) {
	    	thePixels.at(mapXY(x,y)) = in;
	    }
	    void fullWriteOut(ostream& out);

	private:
		int mapXY(int x, int y) {return y*(width-1) + x; }
		int width;
		int height;
		vector<color> thePixels;
};

void image::fullWriteOut(ostream& out) {

	writeHeader(out);
	//for ach pixel, write out its color
	for (int y=0; y < height; y++) {
		for (int x =0; x < width; x++) {
			writePixel(out, x, y, thePixels.at(mapXY(x, y)));
		}
		writeNewLine(out);
	}
}

void image::writePixel(ostream& out, int x, int y, color cOut) const {

 	out << static_cast<int>(clamp(cOut.r(), 0.0, 255)) << " "
 					<< static_cast<int>(clamp(cOut.g(), 0.0, 255)) << " "
 					<< static_cast<int>(clamp(cOut.b(), 0.0, 255)) << endl; 
 		
}

void image::writeNewLine(ostream& out) const {
 	out << "\n"; 
 }

void image::writeHeader(ostream& out) const {
	//PPM format header
 	out << "P3\n" << width << " " << height << "\n255\n"; 
 }

#endif


