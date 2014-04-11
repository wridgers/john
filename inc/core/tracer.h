#ifndef __TRACER_H__
#define __TRACER_H__

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "core/scene.h"
#include "types/colour.h"
#include "types/ray.h"
#include "types/vector3.h"

// thread render statistics struct
struct threadStats
{
  long    raysCast;
};

// render setting enums
enum sampleType {
  // no sampling. worst quality, fastest
  SAMPLE_NONE,

  // exact number of samples, best quality but slowest
  SAMPLE_FULL,

  // change number of samples based on fewer initial samples
  // faster, potentially lower quality
  SAMPLE_ADAPTIVE
};

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

  // sampling settings
  void setPixelSampleType(sampleType type);
  void setPixelSamples(unsigned short samples);

  void setShadowSampleType(sampleType type);
  void setShadowSamples(unsigned short samples);

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

  // pixel sampling
  sampleType          m_pixelSampleType;
  unsigned short      m_pixelSamples;

  // shadow sampling
  sampleType          m_shadowSampleType;
  unsigned short      m_shadowSamples;

  // screen buffer
  int                 m_frameBufferSize;
  Colour*             m_frameBuffer;

  // scene to render
  Scene*              m_scene;

  // threading
  int                 m_numberOfThreads;

  // render stats
  threadStats*        m_stats;
};

#endif
