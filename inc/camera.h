#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "vector3.h"

using namespace std;

class Camera
{
public:
    Camera();
    Camera(Vector3 location, Vector3 target);
    ~Camera();

private:
    // position and orientation
    Vector3d        m_location, m_direction;

    // FOV settings
    double          m_hFOV, m_vFOV;
};

#endif