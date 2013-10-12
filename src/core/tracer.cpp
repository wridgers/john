#include "core/tracer.h"

Tracer::Tracer()
{
  // some sane defaults
  setNumberOfThreads(2);
  setMaxRayDepth(100);
  setRenderResolution(640, 480);

  // default anti aliasing
  setAntiAliasType(AA_TYPE_SUPERSAMPLE);
  setAntiAliasQuality(AA_QUALITY_4);

  // background colour
  setRenderBackgroundColour(Colour(0, 0, 0));

  // lighting settings
  useAmbientLighting(true);
  setAmbientLightingColour(Colour(255, 255, 255));
  setAmbientLightingIntensity(0.01);
}

Tracer::~Tracer()
{
  // delete the screen buffer
  if (m_screenBuffer)
    delete [] m_screenBuffer;

  // delete the stats
  delete [] m_stats;

  // delete the camera
  delete m_camera;

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

void Tracer::setNumberOfThreads(int threads)
{
  m_numberOfThreads = threads;
}

void Tracer::setMaxRayDepth(int depth)
{
  m_maxRayDepth = depth;
}

void Tracer::setRenderResolution(int width, int height)
{
  m_renderWidth   = width;
  m_renderHeight  = height;
}

void Tracer::setRenderBackgroundColour(Colour colour)
{
  m_renderBackgroundColour = colour;
}

void Tracer::setAntiAliasType(antiAliasType type)
{
  m_antiAliasType = type;
}

void Tracer::setAntiAliasQuality(antiAliasQuality quality)
{
  m_antiAliasQuality = quality;
}

void Tracer::useAmbientLighting(bool enabled)
{
  m_ambientLightingEnabled = enabled;
}

void Tracer::setAmbientLightingColour(Colour colour)
{
  m_ambientLightingColour = colour;
}

void Tracer::setAmbientLightingIntensity(double intensity)
{
  m_ambientLightingIntensity = intensity;
}

bool Tracer::init()
{
  // initialise screen buffer
  m_screenBufferSize = m_renderWidth * m_renderHeight;
  m_screenBuffer = new Colour[m_screenBufferSize];

  for (int i = 0; i < m_screenBufferSize; ++i)
    m_screenBuffer[i] = Colour();

  // initialise statistics struct
  m_stats = new threadStats[m_numberOfThreads];

  // stats are fun!
  for (int i = 0; i < m_numberOfThreads; ++i)
    m_stats[i].raysCast = 0;

  return true;
}

void Tracer::addLight(Light* light)
{
  m_lights.push_back(light);
}

void Tracer::addMaterial(Material* material)
{
  m_materials.push_back(material);
}

void Tracer::addObject(Object* object)
{
  m_objects.push_back(object);
}

bool Tracer::loadExampleScene()
{
  /////////////////////
  // render settings //
  /////////////////////

  useAmbientLighting(true);
  setAmbientLightingColour(Colour(255, 255, 255));
  setAmbientLightingIntensity(0.08);
  setRenderBackgroundColour(Colour(178, 207, 223));

  ///////////////////
  // light sources //
  ///////////////////

  // a single light source
  Light *light;
  light = new Light();
  light->setPosition(Vector3(0, 299, -200));
  light->setIntensity(80);
  light->setColour(Colour(255, 255, 255));
  addLight(light);

  ////////////
  // camera //
  ////////////

  // camera
  m_camera = new Camera();
  m_camera->setPosition(Vector3(0, 150, -800));
  m_camera->setTarget(Vector3(0, 150, 0));
  m_camera->setUpDirection(Vector3(0, -1, 0));
  m_camera->setHorizontalFOV(60);
  m_camera->setRenderDimensions(m_renderWidth, m_renderHeight);

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
  refraction->setDiffuseColour(Colour(255,183,182));
  refraction->setOpacity(1.0);
  addMaterial(refraction);

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
  sphere->setMaterial(white);
  addObject(sphere);

  // right sphere
  sphere = new Sphere();
  sphere->setPosition(Vector3(100, 70, -100));
  sphere->setRadius(70);
  sphere->setMaterial(refraction);
  addObject(sphere);

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

void Tracer::trace()
{
  // threads
  thread *traceThreads = new thread[m_numberOfThreads];

  // spawn threads
  for (int threadId = 0; threadId < m_numberOfThreads; ++threadId)
    traceThreads[threadId] = thread(&Tracer::traceThread, this, threadId);

  // join threads
  for (int threadId = 0; threadId < m_numberOfThreads; ++threadId)
    traceThreads[threadId].join();

  // done! clean up
  delete [] traceThreads;
}

void Tracer::traceThread(int threadId)
{
  for (int screenIndex = threadId; screenIndex < m_screenBufferSize; screenIndex += m_numberOfThreads ) {
    // find which pixel this screen cell is for
    int x = screenIndex % m_renderWidth;
    int y = (screenIndex - x) / m_renderWidth;

    // if no anti aliasing, set the quality to 1
    if (m_antiAliasType == AA_TYPE_NONE)
      m_antiAliasQuality = AA_QUALITY_1;

    // anti alias values
    // this is how we split up the pixel
    double offsetStart;
    double offsetStop;
    double offsetStep;

    // this is to what degree we randomly jitter the ray
    // double jitter;

    // precalculated values for anti aliasing
    switch(m_antiAliasQuality) {
      case AA_QUALITY_1:
        offsetStart = 0.0;
        offsetStop  = 0.0;
        offsetStep  = 1.0;

        break;

      case AA_QUALITY_4:
        offsetStart = -0.25;
        offsetStop  = 0.25;
        offsetStep  = 0.5;

        break;

      case AA_QUALITY_16:
        offsetStart = -0.375;
        offsetStop  = 0.375;
        offsetStep  = 0.25;

        break;

      default:
        // this should never happen...
        break;
    };

    // list of colour results
    vector<Colour> colours;

    // anti aliasing
    for (double offsetX = offsetStart; offsetX <= offsetStop; offsetX += offsetStep) {
      for (double offsetY = -offsetStart; offsetY <= offsetStop; offsetY += offsetStep) {
        // get our ray from the camera
        Ray primaryRay = m_camera->getPixelRay(x + offsetX, y + offsetY);

        // increment ray count
        m_stats[threadId].raysCast++;

        // get the colour of this pixel
        Colour colour = traceRay(threadId, primaryRay, m_maxRayDepth);
        colours.push_back(colour);
      }
    }

    // set the colour of this pixel
    m_screenBuffer[screenIndex] = Colour(colours);
  }
}

Colour Tracer::traceRay(int threadId, Ray ray, int rayDepth)
{
  // find closest point of intersection and object
  Object*     object = NULL;
  double      objectDistance = 0.0;

  // for every object
  for (auto obj : m_objects) {
    // now, check if ray intersects the sphere
    pair<bool, double> intersectionTest = obj->intersectionCheck(ray);

    // check for intersection
    if (intersectionTest.first) {

      // now find out if this is the closest.
      if ((!object || intersectionTest.second < objectDistance)
          && intersectionTest.second > 0.0001) {

        // we've found at least one intersection
        objectDistance  = intersectionTest.second;
        object = obj;
      }
    }
  }

  // if we found an intersection
  if (object) {
    // we will need to calculate the colours generated by this ray
    Colour rayColour;
    Colour reflectionRayColour;
    Colour refractionRayColour;

    // the coordinates of intersection
    Vector3 intersection = ray.at(objectDistance);

    // we calculate the direction of the normal at this intersection
    Vector3 surfaceNormal = object->surfaceNormal(intersection);

    // get sphere's material
    Material *objectMaterial = object->getMaterial();
    Colour objectColour      = objectMaterial->getDiffuseColour();

    // calculate ambient lighting
    rayColour += objectColour * (objectMaterial->getAmbientIntensity() * m_ambientLightingIntensity);

    // for each light
    for (auto light : m_lights) {

      // calculate Phong attenuation
      double lightDistance = Vector3(intersection, light->getPosition()).magnitude();
      double lightAttenuation = light->getIntensity() / (pow(lightDistance, objectMaterial->getPhongAttenuation()) + 0.01);

      // get direction from intersection to lightLocation
      Vector3 lightNormal(intersection, light->getPosition());
      lightNormal.normalise();

      // if the dot product is negative, it is not facing the light
      double shadowCheck = surfaceNormal.dot(lightNormal);

      // if facing the light
      if (shadowCheck > 0.0) {
        // now we check it is not in shadow
        Ray shadowRay(intersection, lightNormal);

        // increment ray count
        m_stats[threadId].raysCast++;

        // distance to light
        double distanceToLight = Vector3(intersection, light->getPosition()).magnitude();

        // TODO: shadows need to work nicely with transparent objects…
        // update this every loop
        bool inShadow = false;

        // check all objects
        for (auto obj : m_objects) {
          pair<bool, double> intersectionTest = obj->intersectionCheck(shadowRay);

          // does this object lie on our intersection ray?
          if (intersectionTest.first && intersectionTest.second > 0.0001 && intersectionTest.second < distanceToLight) {

            if (obj->getMaterial()->getOpacity() == 0.0)
              inShadow = true;
          }

          if (inShadow)
            break;
        }

        // only add light if not in shadow
        if (!inShadow) {
          // we 'add' the light from the current light to the screen

          // lambertian reflectance
          // calculate diffuse lighting
          rayColour += objectColour * (lightAttenuation * objectMaterial->getDiffuseIntensity() * shadowCheck);

          // normal to camera
          // OLD AND SLOW: Vector3 cameraNormal(intersection, m_camera->getPosition());
          // OLD AND SLOW: cameraNormal.normalise();
          // this optimisation saved around 5% in my test. :)
          Vector3 cameraNormal = - ray.getDirection();

          // reflect light normal around surface normal
          // NOTE: we can just use shadowCheck here because it's
          //   surfaceNormal.dot(lightNormal)
          // also, this is already normalise, don't normalise again!
          Vector3 lightNormalReflection = (surfaceNormal * shadowCheck * 2) - lightNormal;

          // now find the angle between these normal vectors
          // note, these are unit so the magnitude is 1 ;)
          double cosAlpha = lightNormalReflection.dot(cameraNormal);

          // calculate phong specular stuff
          double specular = pow(cosAlpha, objectMaterial->getPhongSpecularity());

          // TODO: find out why it's occasionally negative
          if (specular < 0)
            specular = 0;

          // add to pixel
          rayColour += (255 * lightAttenuation * objectMaterial->getSpecularIntensity() * specular);
        }
      }
    }

    // only do reflection and/or transmission if we haven't hit a ray limit
    if (rayDepth > 0) {

      // calculate reflection ray
      if (objectMaterial->getReflectivity() > 0) {
        // first, calculation direction of reflection
        // note, the ray direction must be negated
        Vector3 reflectionDirection = (surfaceNormal * surfaceNormal.dot(-ray.getDirection()) * 2) + ray.getDirection();

        // get new ray
        Ray reflectionRay = Ray(intersection, reflectionDirection);

        // increment ray count
        m_stats[threadId].raysCast++;

        // trace ray and store colour we get
        reflectionRayColour = (traceRay(threadId, reflectionRay, rayDepth - 1) * objectMaterial->getReflectivity() );
      }

      // calculate transmission ray
      if (objectMaterial->getOpacity() > 0.0) {
        // for now ignore indices of refraction of the media, we're just looking at light going through.

        // get the ratio of indices of refraction
        double refractiveIndexRatio = 1.0/1.03;
        double surfaceNormalDotRayDirection = surfaceNormal.dot(ray.getDirection());
        double transmissionCheck = refractiveIndexRatio * refractiveIndexRatio * (1.0 - (surfaceNormalDotRayDirection * surfaceNormalDotRayDirection));

        // TODO: what if the ray is exiting the object?
        // we could test this by checking the direction of the surface normal

        // does transmission occur?
        if (transmissionCheck <= 1.0) {
          // calculate direction of transmission
          Vector3 transmissionDirection = (ray.getDirection() * refractiveIndexRatio) - (surfaceNormal * (refractiveIndexRatio + sqrt(1.0 - transmissionCheck)));

          // get new ray through the object
          Ray transmissionRay = Ray(intersection, transmissionDirection);

          // increment ray count
          m_stats[threadId].raysCast++;

          // trace ray and store colour we get
          refractionRayColour = (traceRay(threadId, transmissionRay, rayDepth - 1) * 2.0);
        }
      }
    }

    // now we've done all the calculations, combine the colours and return what we get
    // TODO: this is ugly…
    double objectOpacity = objectMaterial->getOpacity();
    Colour finalRayColour = (rayColour * (1.0 - objectOpacity)) + reflectionRayColour + (refractionRayColour * objectOpacity);

    // hand it back!
    return finalRayColour;
  }

  // ray does not intersect any objects hence ray must extend into the background of scene
  return m_renderBackgroundColour;
}

void Tracer::writeScreenToBmp(string filename)
{
  // BMP file format header
  struct BitMapFileHeader
  {
    short  magic;
    int    size;
    short  reserved1;
    short  reserved2;
    int    offbits;
  };

  // BMP file format header
  struct BitMapInfoHeader
  {
    int    size;
    int    width;
    int    height;
    short  planes;
    short  bitCount;
    int    compression;
    int    sizeImage;
    int    xPixelsPerMeter;
    int    yPixelsPerMeter;
    int    clrUsed;
    int    clrImportant;
  };

  struct BitMapFileHeader  header;
  struct BitMapInfoHeader  info;

  // magic bytes
  // note, rows must be a multiple of four
  int extraBytes = (4 - (m_renderWidth * 3) % 4) % 4;
  int imageBufferSize = (m_renderWidth * 3 + extraBytes) * m_renderHeight;


  // BMP header, magic number is 'BM'
  header.magic = 0x4d42;
  header.size  = 14 + 40 + imageBufferSize;
  header.reserved1 = 0;
  header.reserved2 = 0;
  header.offbits = 14 + 40;

  info.size = 40;
  info.width = m_renderWidth;
  info.height = m_renderHeight;
  info.planes = 1;
  info.bitCount = 24;
  info.compression = 0;
  info.sizeImage = imageBufferSize;
  info.xPixelsPerMeter = 2952;
  info.yPixelsPerMeter = 2952;
  info.clrUsed = 0;
  info.clrImportant = 0;

  char *imageBuffer = new char[imageBufferSize];

  // zero everything (make it black, zero the extra bytes)
  memset(imageBuffer, 0, sizeof(char)*imageBufferSize);

  // for every pixel index
  for (int i = 0; i < m_screenBufferSize; ++i ) {
    int x = i % m_renderWidth;
    int y = (i - x) / m_renderWidth;

    // use x and y to find offset n
    // this is because the bitmap format expects the last row first
    int n = (m_renderHeight - 1 - y) * (m_renderWidth * 3 + extraBytes) + (x * 3);

    // set blue, green, and red byte
    imageBuffer[n]    = (char)m_screenBuffer[i].getBlueRGB();
    imageBuffer[n+1]  = (char)m_screenBuffer[i].getGreenRGB();
    imageBuffer[n+2]  = (char)m_screenBuffer[i].getRedRGB();
  }

  // write to file
  ofstream outputFile(filename, ios::binary);

  // file header
  // we write each member of the struct one by one
  // this is to avoid some packing issues
  outputFile.write((char*)&header.magic,      sizeof(header.magic));
  outputFile.write((char*)&header.size,       sizeof(header.size));
  outputFile.write((char*)&header.reserved1,  sizeof(header.reserved1));
  outputFile.write((char*)&header.reserved2,  sizeof(header.reserved2));
  outputFile.write((char*)&header.offbits,    sizeof(header.offbits));

  // info header and imageBuffer
  // we can write these directly because they're the correct size
  outputFile.write((char*)&info, sizeof(info));
  outputFile.write(imageBuffer, imageBufferSize);

  // close file handle
  outputFile.close();

  // clean up
  delete [] imageBuffer;
}

long Tracer::getRaycount()
{
  long output = 0;

  // add all the raysCast values together
  for (int i = 0; i < m_numberOfThreads; ++i)
    output += m_stats[i].raysCast;

  return output;
}
