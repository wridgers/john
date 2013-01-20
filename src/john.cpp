#include "john.h"

using namespace std;

int main() 
{
	// load tracer, apply some settings
	Tracer *tracer = new Tracer();
	tracer->setRenderResolution(1280, 720);

    // TODO: command line arguments
    // TODO: threading and CPU core detection
    // LINK: http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine

	tracer->init();
	tracer->loadExampleScene();

	tracer->trace();
    // TODO: render stats, % complete

	tracer->writeScreenToBmp("image.bmp");

	// clean up
	delete tracer;

	return 0;
}