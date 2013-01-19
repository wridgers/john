#include "john.h"

using namespace std;

int main() 
{
	// load tracer, apply some settings
	Tracer *tracer = new Tracer();
	tracer->setRenderResolution(1280, 720);

	tracer->init();
	tracer->loadExampleScene();
	tracer->trace();
	tracer->writeScreenToBmp("image.bmp");

	// clean up
	delete tracer;

	return 0;
}