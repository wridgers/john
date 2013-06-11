#include "john.h"

using namespace std;

int main() 
{
    // print stuff
    cout << "john - v0.1 - a Will Ridgers project\n" << endl;

	// load tracer, apply some settings
	Tracer *tracer = new Tracer();
	tracer->setRenderResolution(1920, 1080);
    tracer->setRenderBackgroundColour(Colour(178, 207, 223));

    // guess number of threads to use
    unsigned threads = thread::hardware_concurrency();
    tracer->setNumberOfThreads(threads);

    // load stuff
	tracer->init();
	tracer->loadExampleScene();

    // get time of start
    chrono::high_resolution_clock::time_point traceStart = chrono::high_resolution_clock::now();
    
    // trace frame
    tracer->trace();

    // get time of stop
    chrono::high_resolution_clock::time_point traceStop = chrono::high_resolution_clock::now();
    unsigned traceMilliseconds = (unsigned)chrono::duration_cast<chrono::milliseconds>(traceStop - traceStart).count();

    // TODO: render stats, % complete, log file
    cout << "trace complete in " << (traceMilliseconds/1000.0) << " seconds" << endl;
    // cout << "total rays: " << tracer->getRaycount() << endl;

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