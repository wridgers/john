#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include <vector>

#include "types/colour.h"

#include "cameras/camera.h"
#include "lights/light.h"
#include "materials/material.h"

#include "objects/object.h"
#include "objects/plane.h"
#include "objects/sphere.h"
#include "objects/triangle.h"

using namespace std;

class Scene
{
public:
  Scene();
  Scene(string sceneFile);
  ~Scene();

  // background colour
  void   setEnvironmentColour(Colour colour);
  Colour getEnvironmentColour();

  // lighting settings
  void useAmbientLighting(bool enabled);
  void setAmbientLightingColour(Colour colour);
  void setAmbientLightingIntensity(double intensity);

  bool   hasAmbientLighting();
  Colour getAmbientLightingColour();
  double getAmbientLightingIntensity();

  // scene management
  void addCamera(Camera* camera);
  void addLight(Light* light);
  void addMaterial(Material* material);
  void addObject(Object* object);

  // get cameras
  vector<Camera*>   getCameras();
  Camera*           getCamera(unsigned int id);

  // get lights
  vector<Light*>    getLights();
  Light*            getLight(unsigned int id);

  // get materials
  vector<Material*> getMaterials();
  Material*         getMaterial(unsigned int id);

  // get objects
  vector<Object*>   getObjects();
  Object*           getObject(unsigned int id);

  // load scene
  bool loadScene(string sceneFile);

private:

  // scene elements
  vector<Camera*>     m_cameras;
  vector<Light*>      m_lights;
  vector<Material*>   m_materials;
  vector<Object*>     m_objects;

  // background
  Colour              m_environmentColour;

  // ambient lighting settings
  bool                m_ambientLighting;
  Colour              m_ambientLightingColour;
  double              m_ambientLightingIntensity;

};

#endif
