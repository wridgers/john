#include "john.h"

using namespace std;

int main(int argc, char **argv) 
{
    // print stuff
    cout << "john - v0.1.1 - a Will Ridgers project\n" << endl;

    // config
    int renderWidth = 1280;
    int renderHeight = 720;

	// load tracer, apply some settings
	Tracer *tracer = new Tracer();
	tracer->setRenderResolution(renderWidth, renderHeight);
    tracer->setRenderBackgroundColour(Colour(178, 207, 223));

    // guess number of threads to use
    unsigned threads = thread::hardware_concurrency();
    tracer->setNumberOfThreads(threads);
    cout << "threads: " << threads << endl;

    // load stuff
	tracer->init();
	tracer->loadExampleScene();

    // get time of start
    chrono::high_resolution_clock::time_point traceStart = chrono::high_resolution_clock::now();
    
    // trace!
    tracer->trace();

    // get time of stop
    chrono::high_resolution_clock::time_point traceStop = chrono::high_resolution_clock::now();
    unsigned traceMilliseconds = (unsigned)chrono::duration_cast<chrono::milliseconds>(traceStop - traceStart).count();

    cout << "trace complete in " << (traceMilliseconds/1000.0) << " seconds" << endl;
    cout << "total rays: " << tracer->getRaycount() << endl;

    // save screen buffer
	tracer->writeScreenToBmp("image.bmp");

	// clean up
	delete tracer;

	return 0;
}