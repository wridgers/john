#include "john.h"

using namespace std;

int main(int argc, char **argv) 
{
  // print stuff
  cout << "john - v0.1.1 - a Will Ridgers project\n" << endl;

  // load tracer
  Tracer *tracer = new Tracer();

  // configure tracer
  tracer->setRenderResolution(640, 480);
  tracer->setAntiAliasType(AA_TYPE_SUPERSAMPLE);
  tracer->setAntiAliasQuality(AA_QUALITY_1);

  // guess number of threads to use
  unsigned threads = thread::hardware_concurrency();
  tracer->setNumberOfThreads(threads);
  cout << "threads: " << threads << endl;

  // load scene
  Scene *scene = new Scene();
  scene->loadScene("simple.scene");

  // prepare
  tracer->setScene(scene);
  tracer->prepare();

  // get time of start
  chrono::high_resolution_clock::time_point traceStart = chrono::high_resolution_clock::now();

  // trace!
  tracer->trace();

  // get time of stop
  chrono::high_resolution_clock::time_point traceStop = chrono::high_resolution_clock::now();
  unsigned traceMilliseconds = (unsigned)chrono::duration_cast<chrono::milliseconds>(traceStop - traceStart).count();

  cout << "trace complete in " << (traceMilliseconds/1000.0) << " seconds" << endl;
  cout << "total rays: " << tracer->getRaycount() << endl;
  cout << fixed << "rays per second: " << (tracer->getRaycount()) / (traceMilliseconds/1000.0) << endl;

  // save screen buffer
  tracer->writeScreenToBmp("image.bmp");

  // clean up
  delete scene;
  delete tracer;

  // return okay!
  return 0;
}
