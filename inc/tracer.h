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

    // scene loading
    // TODO: add a scene handler
    void addLight(Light* light);
    void addMaterial(Material* material);
    void addObject(Object* object);

    bool loadExampleScene();
    bool loadScene();

    // trace
    void   trace();
    Colour traceRay(Ray *ray, int depth);

    // save buffer
    void writeScreenToBmp(string filename);

private:
    // render settings
    int			        m_renderWidth, m_renderHeight;

    // background
    Colour              m_renderBackgroundColour;

    // ambient lighting settings
    bool                m_ambientLightingEnabled;
    Colour              m_ambientLightingColour;
    double              m_ambientLightingIntensity;

    // tracing settings
    int                 m_threads, m_maxRayDepth;

    // screen buffer
    int			        m_screenBufferSize;
    Colour*             m_screenBuffer;

    // scene objects
    Camera*             m_camera;
    vector<Light*>      m_lights;
    vector<Material*>   m_materials;
    vector<Object*>     m_objects;
};

#endif
