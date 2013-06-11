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
        m_screenBuffer[i] = Colour();

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
    // render settings
    useAmbientLighting(true);
    setAmbientLightingColour(Colour(255, 255, 255));
    setAmbientLightingIntensity(0.08);

    // first light
    Light *light = new Light();
    light->setPosition(Vector3(-300,400,-100));
    light->setIntensity(40.0);
    light->setColour(Colour(255,255,255));
    addLight(light);

    light = new Light();
    light->setPosition(Vector3(300,400,-100));
    light->setIntensity(40.0);
    light->setColour(Colour(255,255,255));
    addLight(light);
     
    // camera
    m_camera = new Camera();
    m_camera->setPosition(Vector3(0, 150, -800));
    m_camera->setTarget(Vector3(0, 50, 0));
    m_camera->setUpDirection(Vector3(0, -1, 0));
    m_camera->setHorizontalFOV(60);
    m_camera->setRenderDimensions(m_renderWidth, m_renderHeight);

    // red material
    Material *red = new Material();
    red->setDiffuseColour(Colour(255,183,182));
    red->setPhongSpecularity(200);
    red->setReflectivity(0.4);
    addMaterial(red);

    // blue material
    Material *blue = new Material();
    blue->setDiffuseColour(Colour(119,158,247));
    blue->setSpecularIntensity(0.5);
    blue->setPhongSpecularity(8);
    blue->setReflectivity(0.2);
    addMaterial(blue);

    // green material
    Material *green = new Material();
    green->setDiffuseColour(Colour(179,248,203));
    green->setSpecularIntensity(0);
    green->setPhongSpecularity(0);
    addMaterial(green);

    // green material
    Material *mirror = new Material();
    mirror->setDiffuseColour(Colour(255,255,255));
    mirror->setSpecularIntensity(0.1);
    mirror->setPhongSpecularity(50);
    mirror->setReflectivity(0.8);
    addMaterial(mirror);

    // sphere
    Sphere *sphere = new Sphere();
    sphere->setPosition(Vector3(-200,100,0));
    sphere->setRadius(100);
    sphere->setMaterial(red);
    addObject(sphere);

    // another sphere!
    sphere = new Sphere();
    sphere->setPosition(Vector3(-10,80,0));
    sphere->setRadius(80);
    sphere->setMaterial(blue);
    addObject(sphere);

    // another sphere!
    sphere = new Sphere();
    sphere->setPosition(Vector3(-80,60,-125));
    sphere->setRadius(60);
    sphere->setMaterial(mirror);
    addObject(sphere);

    // another sphere!
    sphere = new Sphere();
    sphere->setPosition(Vector3(-180,40,-125));
    sphere->setRadius(40);
    sphere->setMaterial(mirror);
    addObject(sphere);

    // create plane
    Plane *plane = new Plane();
    plane->setNormal(Vector3(0,1,0));
    plane->setPosition(Vector3(0,0,0));
    plane->setMaterial(green);
    addObject(plane);

    // action!
    return true;
}

void Tracer::trace()
{
    // threads
    thread *traceThreads = new thread[m_threads];

    // spawn threads
    for (int threadId = 0; threadId < m_threads; ++threadId) 
        traceThreads[threadId] = thread(&Tracer::traceImage, this, threadId);

    // join threads
    for (int threadId = 0; threadId < m_threads; ++threadId) 
        traceThreads[threadId].join();

    // done! clean up
    delete [] traceThreads;
}

void Tracer::traceImage(int threadOffset)
{
    for (int screenIndex = threadOffset; screenIndex < m_screenBufferSize; screenIndex += m_threads ) {
        // find which pixel this screen cell is for        
        int x = screenIndex % m_renderWidth;
        int y = (screenIndex - x) / m_renderWidth;

        // anti aliasing
        for (double offsetX = -0.25; offsetX <= 0.25; offsetX += 0.5) {
            for (double offsetY = -0.25; offsetY <= 0.25; offsetY += 0.5) {
                // get our ray from the camera
                Ray primaryRay = m_camera->getPixelRay(x, y, offsetX, offsetY);

                // get the colour of this pixel
                Colour primaryColour = traceRay(primaryRay);

                // set the colour of this pixel
                m_screenBuffer[screenIndex] += (primaryColour * 0.25);
            }
        }
    }
}

Colour Tracer::traceRay(Ray ray)
{
    // this will be the colour we return
    Colour rayColour;

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
            if (shadowCheck > 0.0f) {
                // now we check it is not in shadow
                Ray shadowRay(intersection, lightNormal);

                bool inShadow = false;

                // check all objects
                for (auto obj : m_objects) {
                    pair<bool, double> intersectionTest = obj->intersectionCheck(shadowRay);

                    // TODO: and intersection is between light and object, not behind light
                    if (intersectionTest.first && intersectionTest.second > 0.0001)
                        inShadow = true;
                }

                // only add light if not in shadow
                if (!inShadow) {
                    // we 'add' the light from the current light to the screen

                    // calculate diffuse lighting
                    rayColour += objectColour * (lightAttenuation * objectMaterial->getDiffuseIntensity() * shadowCheck);

                    // normal to camera
                    Vector3 cameraNormal(intersection, m_camera->getPosition());
                    cameraNormal.normalise();

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

        // calculate reflection ray
        if (objectMaterial->getReflectivity() > 0) {
            // first, calculation direction of reflection
            // note, the ray direction must be negated
            Vector3 reflectionDirection = (surfaceNormal * surfaceNormal.dot(-ray.getDirection()) * 2) + ray.getDirection();

            // get new ray
            Ray reflectionRay = Ray(intersection, reflectionDirection);

            // trace ray and add colour we get
            rayColour += (traceRay(reflectionRay) * objectMaterial->getReflectivity() );
        }

        // calculate refraction/transmission ray
        // WIP ;)

        // now we've done all the calculations, return what we got
        return rayColour;
    } 

    // ray does not intersect any objects     // hence ray must extend into the background of scene
    return m_renderBackgroundColour;
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