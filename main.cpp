/* ZJW simple C++ code to write out a PPM file representing an ellipse(s) */

#include <iostream>
#include <fstream>
#include <vector>
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


/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;
	color background(112, 134, 156);

	vector<shared_ptr<shape>> theShapes;

	//a triangle
	//a triangle
	theShapes.push_back(make_shared<Polygon>(vec2(10, 30), 0, color(12, 252, 54)) );
	static_pointer_cast<Polygon>(theShapes.at(0))->addVert(vec2(30, 70));
	static_pointer_cast<Polygon>(theShapes.at(0))->addVert(vec2(15, 90));

	shared_ptr<Polygon> t2 = make_shared<Polygon>(vec2(140, 130), 5, color(12, 212, 54)) ;
	t2->addVert(vec2(160, 110));
	t2->addVert(vec2(185, 120));

	shared_ptr<Polygon> t3 = make_shared<Polygon>(vec2(140, 230), 5, color(12, 252, 84)) ;
	t3->addVert(vec2(180, 210));
	t3->addVert(vec2(195, 220));

	theShapes.push_back(t2);
	theShapes.push_back(t3);
	
	for (int j=0; j < 5; j++) {
		theShapes.push_back(make_shared<Implicit2D>(nicerRand(100, 200), nicerRand(100, 200), 
								nicerRand(11, 30), nicerRand(11, 30), color(nicerRand(123, 250), 12, nicerRand(123, 250))));	
	}

	for (int i=0; i < 10; i++) {
		theShapes.push_back(make_shared<Rect>(vec2(nicerRand(0, 300), nicerRand(0, 300)), 
				nicerRand(18, 43), nicerRand(15, 36), color(nicerRand(123, 250), 12, 112), nicerRand(1, 20)));
	}


	string outFilename;
	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
	} else {
		sizeX = stoi(argv[1]);
		sizeY = stoi(argv[2]);
		image theImage(sizeX, sizeY, background);

		//create the image
		createImage(theImage, theShapes, color(12));

		//code to write the files
		outFilename.append(argv[3]);
		outFilename.append(".ppm");
		outFile.open(outFilename);

		if (outFile) {
			cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << argv[3] << endl;
			theImage.fullWriteOut(outFile);
			outFile.close();
			outFilename.erase();
		} else {
			cout << "Error cannot open outfile" << endl;
			exit(0);
		}

	} //end valid command line parameters

}
