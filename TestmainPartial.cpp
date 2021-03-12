/* ZJW simple C++ code for lab08 - full tests  NOT FULL CODE!!! */

#include <iostream>
#include <fstream>
#include <vector>
#include <typeinfo>
#include <memory>
#include "shape.h"
#include "color.h"
#include "rect.h"
#include "implicit2D.h"
#include "polygon.h"
#include "util.h"
#include "image.h"
#include "createImage.h"


using namespace std;

/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */

//TODO you must do this portion
//void createImage


/*read command line arguments and write output - covers all tests for lab08*/
int main(int argc, char *argv[]) {
    // cout<<"using new main"<<endl;

	ofstream outFile0, outFile1, outFile2, outFile3;
	int sizeX, sizeY;

	vector<shared_ptr<shape>> theShapes;

	/* four polygons - 2 concave */
	shared_ptr<Polygon> t2 = make_shared<Polygon>(vec2(50, 50), 5, color(250)) ;
	t2->addVert(vec2(75, 25));
	t2->addVert(vec2(100, 50));
	t2->addVert(vec2(100, 100));
	t2->addVert(vec2(50, 100));

	shared_ptr<Polygon> t3 = make_shared<Polygon>(vec2(200, 50), 5, color(250)) ;
	t3->addVert(vec2(225, 75));
	t3->addVert(vec2(250, 50));
	t3->addVert(vec2(250, 100));
	t3->addVert(vec2(200, 100));

	shared_ptr<Polygon> t4 = make_shared<Polygon>(vec2(50, 200), 5, color(250)) ;
	t4->addVert(vec2(100, 200));
	t4->addVert(vec2(100, 250));
	t4->addVert(vec2(50, 250));

	shared_ptr<Polygon> t5 = make_shared<Polygon>(vec2(200, 200), 5, color(250)) ;
	t5->addVert(vec2(210, 240));
	t5->addVert(vec2(250, 250));
	t5->addVert(vec2(200, 250));

	theShapes.push_back(t2);
	theShapes.push_back(t3);
	theShapes.push_back(t4);
	theShapes.push_back(t5);
	
	/*ellipse with zero divisor*/
	theShapes.push_back(make_shared<Implicit2D>(vec2(150, 150), 0.0, 14, color(250)));	
	
	//rect with reversed corners
	theShapes.push_back(make_shared<Rect>(vec2(170, 80), vec2(120, 60), color(250), 8));

	/*polygon out of bounds */
	shared_ptr<Polygon> t6 = make_shared<Polygon>(vec2(-10, 150), 5, color(250)) ;
	t6->addVert(vec2(10, 130));
	t6->addVert(vec2(10, 170));
	theShapes.push_back(t6);

	/*ellipse out of bounds*/
	theShapes.push_back(make_shared<Implicit2D>(vec2(150, -2), 4, 28, color(250)));	

	//rect out of bounds and inverted vertices */
	theShapes.push_back(make_shared<Rect>(vec2(10, 210), vec2(-10, 240), color(250), 4));

	/*ellipse out of bounds and zero radius! */
	theShapes.push_back(make_shared<Implicit2D>(vec2(-2, 50), 40, 0, color(250)));	

	/*polygon out of bounds  and concave!*/
	shared_ptr<Polygon> t7 = make_shared<Polygon>(vec2(-10, 250), 5, color(250)) ;
	t7->addVert(vec2(50, 290));
	t7->addVert(vec2(140, 300));
	t7->addVert(vec2(-10, 300));
	theShapes.push_back(t7);

	string outFilename0, outFilename1, outFilename2, outFilename3;

	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
	} else {
		sizeX = stoi(argv[1]);
		sizeY = stoi(argv[2]);
		outFilename0.append(argv[3]);
		outFilename1.append(argv[3]);
		outFilename2.append(argv[3]);
		outFilename3.append(argv[3]);
		//color image
		
		image<color> theImage0(sizeX, sizeY, color(112, 134, 156));
		outFilename0.append(".ppm");
		
		//greyscale image
		image<int> theImage1(sizeX, sizeY, 0);
		outFilename1.append(".pgm");

		//black and white image
		image<bool> theImage2(sizeX, sizeY, false);
		outFilename2.append(".pbm");
		//ascii image
		image<char> theImage3(sizeX, sizeY, 'o');
		outFilename3.append(".txt");
		
		outFile0.open(outFilename0);
		outFile1.open(outFilename1);
		outFile2.open(outFilename2);
		outFile3.open(outFilename3);

		//prior to creating image test all valid
		for (auto s : theShapes) {
			s->validate();
		}

		//create the images
		// commented out because you must do this for TASK 1 !!
		createImage(theImage0, theShapes, color(12));
		createImage(theImage1, theShapes, 128);
		createImage(theImage2, theShapes, true);
		createImage(theImage3, theShapes, '%');

		if (outFile0 && outFile1 && outFile2 && outFile3) {
			// cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
			theImage0.fullWriteOut(outFile0);
			theImage1.fullWriteOut(outFile1);
			theImage2.fullWriteOut(outFile2);
			theImage3.fullWriteOut(outFile3);
			outFile0.close();
			outFile1.close();
			outFile2.close();
			outFile3.close();
		} else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
		}

	} //end valid command line parameters

}
