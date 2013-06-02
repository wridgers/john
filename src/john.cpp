#include "john.h"

using namespace std;

int main() 
{
    // print stuff
    cout << "john - v0.1" << endl;

    // TODO: command line arguments
    
	// load tracer, apply some settings
	Tracer *tracer = new Tracer();
	tracer->setRenderResolution(640, 480);
    tracer->setRenderBackgroundColour(Colour(255, 255, 255));

    // TODO: threading and CPU core detection
    // LINK: http://stackoverflow.com/questions/150355/programmatically-find-the-number-of-cores-on-a-machine
    tracer->setNumberOfThreads(8);

	tracer->init();
	tracer->loadExampleScene();
	tracer->trace();

    // TODO: render stats, % complete, log file
    // TODO: opengl window showing render progress

    // TODO: move this to a seperate lib
    // save screen buffer
	tracer->writeScreenToBmp("image.bmp");

	// clean up
	delete tracer;

    // mscv : check for memory leaks
#if defined _WIN32 || defined _WIN64
    _CrtDumpMemoryLeaks();
#endif

	return 0;
}