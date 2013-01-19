#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "vector3.h"

using namespace std;

class Camera
{
public:
    Camera();
    Camera(Vector3 loc, Vector3 target);
    ~Camera();

private:
    // position and orientation
    Vector3d        location, direction;

    // FOV settings
    double          hFOV, vFOV;
};

#endif