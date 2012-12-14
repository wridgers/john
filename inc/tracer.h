#ifndef __TRACER_H__
#define __TRACER_H__

#include <fstream>
#include <iostream>
#include <string>

#include "colour.h"
#include "vector3.h"

using namespace std;

class Tracer
{
public:
	Tracer();
	~Tracer();

	// set some options
	void setRenderResolution(int width, int height);

	// prepare
	bool init();

	// scene loading
	bool loadExampleScene();
	bool loadScene();

	// trace
	void trace();

	// save screen
	void writeScreenToBmp(string filename);

private:
	int			renderWidth, renderHeight;

	int			screenSize;
	Colour*		screen;

	// scene objects
		// objects
		// lights
		// camera
};

#endif