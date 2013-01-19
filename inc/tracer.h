#ifndef __TRACER_H__
#define __TRACER_H__

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "camera.h"
#include "colour.h"
#include "light.h"
#include "material.h"
#include "ray.h"
#include "sphere.h"
#include "vector3.h"

using namespace std;

class Tracer
{
public:
    Tracer();
    ~Tracer();

    // render settings 
    void setRenderResolution(int width, int height);

    // lighting settings
    void useAmbientLighting(bool enabled);
    void setAmbientLightingColour(Colour colour);
    void setAmbientLightingIntensity(double intensity);

    // prepare
    bool init();

    // scene loading
    // TODO: add a scene handler
    bool loadExampleScene();
    bool loadScene();

    // trace
    void trace();

    // save buffer
    void writeScreenToBmp(string filename);

private:
    // render settings
    int			        renderWidth, renderHeight;

    // lighting settings
    bool                ambientLightingEnabled;
    Colour              ambientLightingColour;
    double              ambientLightingIntensity;

    int			        screenBufferSize;
    Colour*             screenBuffer;

    // scene objects
    Camera*             camera;
    vector<Sphere*>     spheres;
    vector<Light*>      lights;
};

#endif
