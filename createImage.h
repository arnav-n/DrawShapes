
/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */
void createImage(image& theImg, 
				vector<shared_ptr<shape>> theShapes, color inC) {

	float res;
	color drawC;

	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theImg.h(); y++) {
		for (int x =0; x < theImg.w(); x++) {

			inTrue = false;
			curDepth = -1;
			//iterate through all possible equations
			for (auto eq : theShapes) {
				if (eq->eval(x, y) && eq->getDepth() > curDepth) {
					inC = eq->getInC();
					inTrue = true;
					curDepth = eq->getDepth();
				}
			}
					
			if (inTrue) {			
				theImg.setPixel(x, y, inC);
			}
		}
	}
}