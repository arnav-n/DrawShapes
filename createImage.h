
/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */

//2 createImages
template <typename T>
//general template for grayscale, ascii and bool
void createImage(image<T>& theImg, 
				vector<shared_ptr<shape>> theShapes, T inC) {
	float res;
	T drawC;
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
					//for grayscale
					if(typeid(inC)==typeid(int)) {
						inC = eq->getInC().bright();
						// cout<<"greyscale ";
						// inC=0;
					}
					inTrue = true;
					curDepth = eq->getDepth();
				}
			}
			if (inTrue) theImg.setPixel(x, y, inC);
			// if(typeid(inC)==typeid(int))cout<<inC<<" ";
		}
	}
}
template <>
void createImage(image<color>& theImg, vector<shared_ptr<shape>> theShapes, color inC) {
	// cout<<"spec color"<<endl;
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
					//set inC to the color of the shape
					inC = eq->getInC();
					inTrue = true;
					curDepth = eq->getDepth();
				}
			}		
			if (inTrue) theImg.setPixel(x, y, inC);
		}
	}
}