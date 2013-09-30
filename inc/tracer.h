#ifndef __TRACER_H__
#define __TRACER_H__

#include <cmath>
#include <fstream>
#include <iostream>
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

// thread render statistics struct
struct threadStats 
{
    long    raysCast;
};

// render setting enums
enum antiAliasType { AA_TYPE_NONE, AA_TYPE_SUPERSAMPLE, AA_TYPE_ADAPTIVE, AA_TYPE_STOCHASTIC};
enum antiAliasQuality { AA_QUALITY_1, AA_QUALITY_4, AA_QUALITY_16 };

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

    // anti alias settings
    void setAntiAliasType(antiAliasType type);
    void setAntiAliasQuality(antiAliasQuality quality);

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
    void   traceThread(int threadOffset);
    Colour traceRay(int threadId, Ray ray, int rayDepth);

    // save buffer
    void writeScreenToBmp(string filename);

    // render stats
    long getRaycount();

private:

    // threading
   int                  m_numberOfThreads;

    // render settings
    int                 m_renderWidth, m_renderHeight;
    int                 m_maxRayDepth;
    antiAliasType       m_antiAliasType;
    antiAliasQuality    m_antiAliasQuality;

    // background
    Colour              m_renderBackgroundColour;

    // ambient lighting settings
    bool                m_ambientLightingEnabled;
    Colour              m_ambientLightingColour;
    double              m_ambientLightingIntensity;

    // screen buffer
    int                 m_screenBufferSize;
    Colour*             m_screenBuffer;

    // scene objects
    Camera*             m_camera;
    vector<Light*>      m_lights;
    vector<Material*>   m_materials;
    vector<Object*>     m_objects;

    // render stats
    threadStats*        m_stats;
};

#endif
