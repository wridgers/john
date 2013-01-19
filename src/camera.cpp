#include "camera.h"

Camera::Camera()
{
    // use sane defaults
    Vector3 location(0, 0, -100);
    Vector3 target;

    Camera::Camera(location, target);
}

Camera::Camera(Vector3 location, Vector3 target)
{
    Camera::location = location;
    Camera::direction = Vector3(location, target);
}

Camera::~Camera()
{

}