#ifndef __TRACER_H__
#define __TRACER_H__

#include <cmath>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "cameras/camera.h"
#include "lights/light.h"
#include "materials/material.h"
#include "maths/vector3.h"
#include "objects/plane.h"
#include "objects/sphere.h"
#include "types/colour.h"
#include "types/ray.h"

using namespace std;

class Tracer
{
public:
    Tracer();
    ~Tracer();

    // core settings
    void setNumberOfThreads(int threads);
    void setMaxRayDepth(int depth);

    // render settings 
    void setRenderResolution(int width, int height);

    // background colour
    void setRenderBackgroundColour(Colour colour);

    // lighting settings
    void useAmbientLighting(bool enabled);
    void setAmbientLightingColour(Colour colour);
    void setAmbientLightingIntensity(double intensity);

    // prepare
    bool init();

    // scene management
    void addLight(Light* light);
    void addMaterial(Material* material);
    void addObject(Object* object);

    // load scene
    bool loadExampleScene();
    bool loadScene();

    // trace
    void   trace();
    void   traceImage(int threadOffset);
    Colour traceRay(Ray ray);

    // save buffer
    void writeScreenToBmp(string filename);

    // render stats
    long getRaycount();

private:
    // render settings
    int			        m_renderWidth, m_renderHeight;

    // background
    Colour              m_renderBackgroundColour;

    // ambient lighting settings
    bool                m_ambientLightingEnabled;
    Colour              m_ambientLightingColour;
    double              m_ambientLightingIntensity;

    // threading
   int                  m_threads;

    // screen buffer
    int			        m_screenBufferSize;
    Colour*             m_screenBuffer;

    // scene objects
    Camera*             m_camera;
    vector<Light*>      m_lights;
    vector<Material*>   m_materials;
    vector<Object*>     m_objects;

    // render stats
    long                m_rayCount;
};

#endif
