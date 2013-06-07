#include "tracer.h"

Tracer::Tracer()
{
    // some sane defaults
    setRenderResolution(640, 480);

    // background colour
    setRenderBackgroundColour(Colour(0, 0, 0));

    // lighting settings
    useAmbientLighting(true);
    setAmbientLightingColour(Colour(255, 255, 255));
    setAmbientLightingIntensity(0.01);

    // render stats
    m_rayCount = 0;
}

Tracer::~Tracer()
{
    // delete the screen buffer
    if (m_screenBuffer)
        delete [] m_screenBuffer;

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
    m_threads = threads;
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
    m_screenBufferSize = m_renderWidth * m_renderHeight;
    m_screenBuffer = new Colour[m_screenBufferSize];

    for (int i = 0; i < m_screenBufferSize; ++i)
        m_screenBuffer[i] = m_renderBackgroundColour;

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
    // TODO: load this from .lua file

    // render settings
    // lighting settings
    useAmbientLighting(true);
    setAmbientLightingColour(Colour(255, 255, 255));
    setAmbientLightingIntensity(0.05);

    // lights
    // create a light
    Light *light = new Light();
    light->setPosition(Vector3(500,500,0));
    light->setColour(Colour(255,255,255));
    
    // add to the scene
    addLight(light);
     
    // camera
    m_camera = new Camera();

    // configure camera
    m_camera->setLocation(Vector3(200, 200, -300));
    m_camera->setTarget(Vector3(0, 0, 0));
    m_camera->setUpDirection(Vector3(0, -1, 0));
    m_camera->setHorizontalFOV(90);
    m_camera->setRenderDimensions(m_renderWidth, m_renderHeight);

    // props
    // props need materials
    Sphere *sphere = new Sphere();
    sphere->setPosition(Vector3(0,0,100));
    sphere->setRadius(70);

    // give it a material
    Material *red = new Material();
    red->setColour(Colour(255,0,0));
    red->setPhongSpecularity(200);
    addMaterial(red);

    // apply!
    sphere->setMaterial(red);

    // add it to the scene
    addObject(sphere);

    // another sphere!
    sphere = new Sphere();
    sphere->setPosition(Vector3(-150,0,0));
    sphere->setRadius(50);

    // give it a material
    Material *blue = new Material();
    blue->setColour(Colour(0,0,255));
    blue->setSpecularReflectionCoeff(0.1);
    blue->setPhongSpecularity(8);
    addMaterial(blue);

    // apply!
    sphere->setMaterial(blue);

    // add it to the scene
    addObject(sphere);

    // another sphere!
    sphere = new Sphere();
    sphere->setPosition(Vector3(150,0,0));
    sphere->setRadius(50);

    // apply!
    sphere->setMaterial(red);

    // add it to the scene
    addObject(sphere);

    // action!
    return true;
}

void Tracer::traceImage()
{
    // light setup
    double  lightIntensity = 100.0;
    Vector3 lightLocation(0, 500, -100);

    for (int screenIndex = 0; screenIndex < m_screenBufferSize; ++screenIndex ) {
        // find which pixel this screen cell is for        
        int x = screenIndex % m_renderWidth;
        int y = (screenIndex - x) / m_renderWidth;

        // TODO: anti aliasing

        // get our ray from the camera
        Ray pixelRay = m_camera->getPixelRay(x, y);
        ++m_rayCount;

        // find closest point of intersection and object
        Object*     object = NULL;
        double      objectDistance = 0.0f;

        // for every sphere
        for (auto obj : m_objects) {
            // now, check if ray intersects the sphere
            pair<bool, double> intersectionTest = obj->intersectionCheck(pixelRay);

            // check for intersection
            if (intersectionTest.first) {
                // now find out if this is the closest.
                if ((!object || intersectionTest.second < objectDistance) 
                        && intersectionTest.second > 0.0) {

                    // we've found at least one intersection
                    objectDistance  = intersectionTest.second;
                    object = obj;
                }
            }
        }

        // if we found an intersection
        if (object) {
            // the coordinates of intersection
            Vector3 intersection = pixelRay.at(objectDistance);

            // we calculate the direction of the normal at this intersection
            Vector3 surfaceNormal = object->surfaceNormal(intersection);

            // this will be the eventual pixel colour
            Colour pixelColour;

            // get sphere's material
            Material *objectMaterial = object->getMaterial();
            Colour objectColour      = objectMaterial->getColour();

            // calculate ambient lighting
            pixelColour += objectColour * (objectMaterial->getAmbientReflectionCoeff() * m_ambientLightingIntensity);

            // TODO: multiple lights
            // for (auto light : m_lights) {

            // calculate Phong attenuation
            double lightDistance = Vector3(intersection, lightLocation).magnitude();
            double lightAttenuation = lightIntensity / (pow(lightDistance, objectMaterial->getPhongAttenuation()) + 0.01);

            // get direction from intersection to lightLocation
            Vector3 lightNormal(intersection, lightLocation);
            lightNormal.normalise();

            // if the dot product is negative, it is in shadow
            double shadowCheck = surfaceNormal.dot(lightNormal);

            if (shadowCheck > 0.0f) {
                // not in shadow
                // we 'add' the light from the current light to the screen

                // calculate diffuse lighting
                pixelColour += objectColour * (lightAttenuation * objectMaterial->getDiffuseReflectionCoeff() * shadowCheck);

                // normal to camera
                Vector3 cameraNormal(intersection, m_camera->getLocation());
                cameraNormal.normalise();

                // normal to light
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
                pixelColour += (255 * lightAttenuation * objectMaterial->getSpecularReflectionCoeff() * specular);
            }

            // TODO: ADD REFLECTION RAY

            // TODO: ADD REFRACTION RAY

            // set it
            m_screenBuffer[screenIndex] = pixelColour;
        }
    }
}

void Tracer::writeScreenToBmp(string filename)
{
    struct BitMapFileHeader
    {
        short	magic;
        int		size;
        short	reserved1;
        short	reserved2;
        int		offbits;
    };

    struct BitMapInfoHeader
    {
        int		size;
        int		width;
        int		height;
        short	planes;
        short	bitCount;
        int		compression;
        int		sizeImage;
        int		xPixelsPerMeter;
        int		yPixelsPerMeter;
        int		clrUsed;
        int		clrImportant;
    };

    struct BitMapFileHeader	header;
    struct BitMapInfoHeader	info;

    // magic bytes
    int extraBytes = (4 - (m_renderWidth * 3) % 4) % 4; // each row must be multiple of four
    int imageBufferSize = (m_renderWidth * 3 + extraBytes) * m_renderHeight;

    header.magic = 0x4d42; // 'BM'
    header.size	= 14 + 40 + imageBufferSize;
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

    for (int i = 0; i < m_screenBufferSize; ++i ) {
        int x = i % m_renderWidth;
        int y = (i - x) / m_renderWidth;

        // use x and y to find offset n
        // this is because the bitmap format expects the last row first
        int n = (m_renderHeight - 1 - y) * (m_renderWidth * 3 + extraBytes) + (x * 3);

        // set blue, green, and red byte
        imageBuffer[n]		= (char)m_screenBuffer[i].getBlueRGB();
        imageBuffer[n+1]	= (char)m_screenBuffer[i].getGreenRGB();
        imageBuffer[n+2]	= (char)m_screenBuffer[i].getRedRGB();
    }

    // write to file
    ofstream outputFile(filename, ios::binary);

    // file header
    // we write each member of the struct one by one
    // this is to avoid some packing issues
    outputFile.write((char*)&header.magic, sizeof(header.magic));
    outputFile.write((char*)&header.size, sizeof(header.size));
    outputFile.write((char*)&header.reserved1, sizeof(header.reserved1));
    outputFile.write((char*)&header.reserved2, sizeof(header.reserved2));
    outputFile.write((char*)&header.offbits, sizeof(header.offbits));

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
    return m_rayCount;
}