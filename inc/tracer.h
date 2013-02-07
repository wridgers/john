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
    void addLight(Light* light);
    void addObject(Object* object);
    bool loadExampleScene();
    bool loadScene();

    // trace
    void trace();

    // save buffer
    void writeScreenToBmp(string filename);

private:
    // render settings
    int			        m_renderWidth, m_renderHeight;

    // lighting settings
    bool                m_ambientLightingEnabled;
    Colour              m_ambientLightingColour;
    double              m_ambientLightingIntensity;

    int			        m_screenBufferSize;
    Colour*             m_screenBuffer;

    // scene objects
    Camera*             m_camera;
    vector<Object*>     m_objects;
    vector<Light*>      m_lights;
};

#endif
