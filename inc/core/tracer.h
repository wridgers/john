#ifndef __TRACER_H__
#define __TRACER_H__

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "core/scene.h"

#include "maths/vector3.h"
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

  // prepare
  bool prepare();

  // scene
  void setScene(Scene* scene);

  // trace
  void   trace();
  void   traceThread(int threadOffset);
  Colour traceRay(int threadId, Ray ray, int rayDepth);

  // save buffer
  void writeScreenToBmp(string filename);

  // render stats
  long getRaycount();

private:
  // render settings
  int                 m_renderWidth, m_renderHeight;
  int                 m_maxRayDepth;
  antiAliasType       m_antiAliasType;
  antiAliasQuality    m_antiAliasQuality;

  // screen buffer
  int                 m_frameBufferSize;
  Colour*             m_frameBuffer;

  // scene to render
  Scene*              m_scene;

  // threading
  int                  m_numberOfThreads;

  // render stats
  threadStats*        m_stats;
};

#endif
