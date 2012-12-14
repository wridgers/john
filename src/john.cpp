#include "john.h"

int main() 
{
	// load tracer, apply some settings
	Tracer *tracer = new Tracer();
	tracer->setRenderResolution(640, 480);

	tracer->init();
	tracer->loadExampleScene();
	tracer->trace();
	tracer->writeScreenToBmp("image.bmp");

	// clean up
	delete tracer;

	return 0;
}