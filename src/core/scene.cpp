#include "core/scene.h"

Scene::Scene()
{
  // TODO: sane defaults
}

Scene::Scene(string sceneFile)
{
  loadScene(sceneFile);
}

Scene::~Scene()
{
  // delete the cameras
  for (auto camera : m_cameras)
    delete camera;

  // delete the lights
  for (auto light : m_lights)
    delete light;

  // delete materials
  for (auto material : m_materials)
    delete material;

  // delete objects
  for (auto object : m_objects)
    delete object;
}

void Scene::setEnvironmentColour(Colour colour)
{
  m_environmentColour = colour;
}

Colour Scene::getEnvironmentColour()
{
  return m_environmentColour;
}

void Scene::useAmbientLighting(bool enabled)
{
  m_ambientLighting = enabled;
}

bool Scene::hasAmbientLighting()
{
  return m_ambientLighting;
}

void Scene::setAmbientLightingColour(Colour colour)
{
  m_ambientLightingColour = colour;
}

Colour Scene::getAmbientLightingColour()
{
  return m_ambientLightingColour;
}

void Scene::setAmbientLightingIntensity(double intensity)
{
  m_ambientLightingIntensity = intensity;
}

double Scene::getAmbientLightingIntensity()
{
  return m_ambientLightingIntensity;
}

void Scene::addCamera(Camera* camera)
{
  m_cameras.push_back(camera);
}

void Scene::addLight(Light* light)
{
  m_lights.push_back(light);
}

void Scene::addMaterial(Material* material)
{
  m_materials.push_back(material);
}

void Scene::addObject(Object* object)
{
  m_objects.push_back(object);
}

vector<Camera*> Scene::getCameras()
{
  return m_cameras;
}

Camera* Scene::getCamera(unsigned int id)
{
  return m_cameras[id];
}

vector<Light*> Scene::getLights()
{
  return m_lights;
}

vector<Material*> Scene::getMaterials()
{
  return m_materials;
}

vector<Object*> Scene::getObjects()
{
  return m_objects;
}

bool Scene::loadScene(string sceneFile)
{
  /////////////////
  // environment //
  /////////////////

  useAmbientLighting(true);
  setAmbientLightingColour(Colour(255, 255, 255));
  setAmbientLightingIntensity(0.08);
  setEnvironmentColour(Colour(178, 207, 223));

  ///////////////////
  // light sources //
  ///////////////////

  // a single light source
  Light *light = new Light();
  light->setPosition(Vector3(0, 299, -200));
  light->setIntensity(60);
  light->setColour(Colour(255, 255, 255));
  addLight(light);

  ////////////
  // camera //
  ////////////

  Camera *camera = new Camera();
  camera->setPosition(Vector3(0, 150, -800));
  camera->setTarget(Vector3(0, 150, 0));
  camera->setHorizontalFOV(60);
  addCamera(camera);

  ///////////////
  // materials //
  ///////////////

  // white material
  Material *white = new Material();
  white->setDiffuseColour(Colour(255,255,255));
  white->setSpecularIntensity(0);
  white->setPhongSpecularity(0);
  addMaterial(white);

  // transparent material
  Material *refraction = new Material();
  refraction->setDiffuseColour(Colour(255, 255, 255));
  refraction->setOpacity(1.0);
  addMaterial(refraction);

  // reflection material
  Material *reflection = new Material();
  reflection->setDiffuseColour(Colour(255, 255, 255));
  reflection->setReflectivity(1.0);
  addMaterial(reflection);

  // red material
  Material *red = new Material();
  red->setDiffuseColour(Colour(255,0,0));
  red->setSpecularIntensity(0);
  red->setPhongSpecularity(0);
  addMaterial(red);

  // blue material
  Material *blue = new Material();
  blue->setDiffuseColour(Colour(0,0,255));
  blue->setSpecularIntensity(0);
  blue->setPhongSpecularity(0);
  addMaterial(blue);

  /////////////
  // spheres //
  /////////////

  // left sphere
  Sphere *sphere = new Sphere();
  sphere->setPosition(Vector3(-100, 100, 50));
  sphere->setRadius(100);
  sphere->setMaterial(reflection);
  addObject(sphere);

  // right sphere
  sphere = new Sphere();
  sphere->setPosition(Vector3(100, 70, -100));
  sphere->setRadius(70);
  sphere->setMaterial(reflection);
  addObject(sphere);

  // a simple triangle
  Triangle *triangle = new Triangle();
  triangle->setVerticies(
    Vector3(0, 0, -100),
    Vector3(0, 50, -100),
    Vector3(0, 0, -100)
  );

  ////////////
  // planes //
  ////////////

  // bottom plane
  Plane *plane = new Plane();
  plane->setNormal(Vector3(0, 1, 0));
  plane->setPosition(Vector3(0, 0, 0));
  plane->setMaterial(white);
  addObject(plane);

  // top plane
  plane = new Plane();
  plane->setNormal(Vector3(0, -1, 0));
  plane->setPosition(Vector3(0, 400, 0));
  plane->setMaterial(white);
  addObject(plane);

  // rear plane
  plane = new Plane();
  plane->setNormal(Vector3(0, 0, -1));
  plane->setPosition(Vector3(0, 0, 500));
  plane->setMaterial(white);
  addObject(plane);

  // left plane
  plane = new Plane();
  plane->setNormal(Vector3(1, 0, 0));
  plane->setPosition(Vector3(-350, 0, 0));
  plane->setMaterial(blue);
  addObject(plane);

  // right plane
  plane = new Plane();
  plane->setNormal(Vector3(-1, 0, 0));
  plane->setPosition(Vector3(350, 0, 0));
  plane->setMaterial(red);
  addObject(plane);

  // action!
  return true;
}
