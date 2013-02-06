#include "tracer.h"

Tracer::Tracer()
{
    // some sane defaults
    Tracer::setRenderResolution(640, 480);

    // lighting settings
    Tracer::useAmbientLighting(true);
    Tracer::setAmbientLightingColour(Colour(255, 255, 255));
    Tracer::setAmbientLightingIntensity(0.01);
}

Tracer::~Tracer()
{
    if (screenBuffer)
        delete [] screenBuffer;

    // delete the scene correctly
    // TODO: fix all these deletes
}

void Tracer::setRenderResolution(int width, int height)
{
    Tracer::renderWidth = width;
    Tracer::renderHeight = height;
}

void Tracer::useAmbientLighting(bool enabled)
{
    Tracer::ambientLightingEnabled = enabled;
}

void Tracer::setAmbientLightingColour(Colour colour)
{
    Tracer::ambientLightingColour = colour;
}

void Tracer::setAmbientLightingIntensity(double intensity)
{
    Tracer::ambientLightingIntensity = intensity;
}

bool Tracer::init()
{
    Tracer::screenBufferSize = Tracer::renderWidth * Tracer::renderHeight;
    Tracer::screenBuffer = new Colour[Tracer::screenBufferSize];

    return true;
}

void Tracer::addLight(Light* light)
{
    Tracer::lights.push_back(light);
}

void Tracer::addObject(Object* object)
{
    Tracer::objects.push_back(object);
}

bool Tracer::loadExampleScene()
{
    // TODO: load this from .lua file

    // render settings
    // lighting settings
    Tracer::useAmbientLighting(true);
    Tracer::setAmbientLightingColour(Colour(255, 255, 255));
    Tracer::setAmbientLightingIntensity(0.05);

    // lights
    // create a light
    Light *light = new Light();
    light->setPosition(Vector3(500,500,0));
    light->setColour(Colour(255,255,255));
    
    // add to the scene
    Tracer::addLight(light);
     
    // camera
    Tracer::camera = new Camera();

    // props
    // props need materials
    Sphere *sphere = new Sphere();
    sphere->setPosition(Vector3(150,0,200));
    sphere->setRadius(100);

    // give it a material
    Material *red = new Material();
    red->setColour(Colour(255,0,0));

    // apply!
    sphere->setMaterial(red);

    // add it to the scene
    Tracer::addObject(sphere);

    // another sphere!
    sphere = new Sphere();
    sphere->setPosition(Vector3(-150,0,200));
    sphere->setRadius(100);

    // give it a material
    Material *blue = new Material();
    blue->setColour(Colour(0,0,255));
    blue->setSpecularReflectionCoeff(0);

    // apply!
    sphere->setMaterial(blue);

    // add it to the scene
    Tracer::addObject(sphere);

    // another sphere!
    sphere = new Sphere();
    sphere->setPosition(Vector3(0,0,800));
    sphere->setRadius(100);

    // apply!
    sphere->setMaterial(red);

    // add it to the scene
    Tracer::addObject(sphere);

    // action!
    return true;

    // TODO: delete scene
}

void Tracer::trace()
{
    // camera setup
    Vector3 cameraLocation(0, 0, -800);

    // light setup
    double  lightIntensity = 100.0;
    Vector3 lightLocation(0, 500, 0);

    for (int screenIndex = 0; screenIndex < Tracer::screenBufferSize; ++screenIndex ) {
        // find which pixel this screen cell is for        
        int x = screenIndex % Tracer::renderWidth;
        int y = (screenIndex - x) / Tracer::renderWidth;

        // find location of pixel, and get a ray projecting through pixel into scene
        // TODO: better camera system with Camera class, FOV, etc.
        Vector3 pixelLocation((double)(x-(Tracer::renderWidth/2)), (double)((Tracer::renderHeight/2)-y), 0.0f);

        // direction of ray
        Vector3 rayDirection(cameraLocation, pixelLocation);
        rayDirection.normalise();

        // create ray to trace
        Ray         pixelRay(pixelLocation, rayDirection);

        // find closest point of intersection and object
        Object*     object = 0;
        double      objectDistance = 0.0f;

        // for every sphere
        // TODO: use iterator instead of index.
        for (unsigned int objectIndex = 0; objectIndex < Tracer::objects.size(); ++objectIndex) {
            // now, check if ray intersects the sphere

            pair<bool, double> intersectionTest = Tracer::objects[objectIndex]->intersectionCheck(pixelRay);

            if (intersectionTest.first) {
                // intersection found
                // now find out if this is the closest.
                if ((!object || intersectionTest.second < objectDistance) 
                        && intersectionTest.second > 0.0) {

                    // we've found at least one intersection
                    objectDistance  = intersectionTest.second;
                    object = Tracer::objects[objectIndex];
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
            Colour objectColour = objectMaterial->getColour();

            // ADD AMBIENT LIGHTING
            pixelColour += objectColour * (objectMaterial->getAmbientReflectionCoeff() * Tracer::ambientLightingIntensity);

            // TODO: multiple lights

            // calculate Phong attenuation
            // TODO: make Phong n value (0.5) a material property.
            double lightDistance = Vector3(intersection, lightLocation).magnitude();
            double lightAttenuation = lightIntensity / (pow(lightDistance, 0.5) + 0.01);

            // get direction from intersection to lightLocation
            Vector3 lightNormal(intersection, lightLocation);
            lightNormal.normalise();

            // if the dot product is negative, it is in shadow
            double shadowCheck = surfaceNormal.dot(lightNormal);

            // ADD DIFFUSE LIGHTING
            if (shadowCheck > 0.0f) {
                // not in shadow
                // we 'add' the light from the current light to the screen

                // pixelColour += sC*shadowCheck;
                pixelColour += objectColour * (lightAttenuation * objectMaterial->getDiffuseReflectionCoeff() * shadowCheck);

                // normal to camera
                Vector3 cameraNormal(intersection, cameraLocation);
                cameraNormal.normalise();

                // normal to light
                // NOTE: we can just use shadowCheck here because it's 
                //   surfaceNormal.dot(lightNormal)
                // also, this is already normalise, don't normalise again!
                Vector3 lightNormalReflection = (surfaceNormal * shadowCheck * 2) - lightNormal;

                // now find the angle between these normal vectors
                // note, these are unit so the magnitude is 1 ;)
                double cosAlpha = lightNormalReflection.dot(cameraNormal);

                // TODO: get n value from material ;)
                double specular = pow(cosAlpha, 5);

                // occasionally it's negative, why?
                // TODO: find out why it's occasionally negative
                if (specular < 0)
                    specular = 0;

                // add to pixel
                pixelColour += (255 * lightAttenuation * objectMaterial->getSpecularReflectionCoeff() * specular);
            }

            // TODO: ADD REFLECTION RAY

            // TODO: ADD REFRACTION RAY

            // set it
            Tracer::screenBuffer[screenIndex] = pixelColour;
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
    int extraBytes = (4 - (Tracer::renderWidth * 3) % 4) % 4; // each row must be multiple of four
    int imageBufferSize = (Tracer::renderWidth * 3 + extraBytes) * renderHeight;

    header.magic = 0x4d42; // 'BM'
    header.size	= 14 + 40 + imageBufferSize;
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.offbits = 14 + 40;

    info.size = 40;
    info.width = Tracer::renderWidth;
    info.height = Tracer::renderHeight;
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

    for (int i = 0; i < screenBufferSize; ++i ) {
        int x = i % Tracer::renderWidth;
        int y = (i - x) / Tracer::renderWidth;

        // use x and y to find offset n
        // this is because the bitmap format expects the last row first
        int n = (Tracer::renderHeight - 1 - y) * (Tracer::renderWidth * 3 + extraBytes) + (x * 3);

        // set blue, green, and red byte
        imageBuffer[n]		= (char)Tracer::screenBuffer[i].getBlueRGB();
        imageBuffer[n+1]	= (char)Tracer::screenBuffer[i].getGreenRGB();
        imageBuffer[n+2]	= (char)Tracer::screenBuffer[i].getRedRGB();
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
