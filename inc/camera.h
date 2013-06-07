#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "ray.h"
#include "vector3.h"

using namespace std;

class Camera
{
public:
    Camera();
    ~Camera();

    // control location, direction, and up vector
    void    setLocation(Vector3 location);
    void    setDirection(Vector3 direction);
    void    setTarget(Vector3 target);
    void    setUpDirection(Vector3 up);

    // we sometimes need this
    Vector3 getLocation();

    // control fov
    void    setHorizontalFOV(int degrees);
    void    setHorizontalFOV(double degrees);

    // set render dimensions
    void    setRenderDimensions(int width, int height);

    // get rays
    Ray     getPixelRay(int pixelX, int pixelY);
    Ray     getPixelRay(double pixelX, double pixelY);

private:
    // recalculate direction, aspect, etc, on change
    void    recalculate();

    // position and orientation
    Vector3         m_location, m_direction;
    Vector3         m_up;

    // image plane 
    double          m_renderWidth, m_renderHeight;
    double          m_imagePlaneWidth, m_imagePlaneHeight;
    Vector3         m_imagePlaneX, m_imagePlaneY;

    // fov settings
    double          m_horizontalFOV;
    double          m_aspectRatio;
};

#endif