#include "camera.h"

Camera::Camera()
{
    m_location = Vector3(0, -100, 0);
    m_direction = Vector3(m_location, Vector3());
}

Camera::Camera(Vector3 location, Vector3 target)
{
    m_location = location;
    m_direction = Vector3(location, target);
}

Camera::~Camera()
{

}