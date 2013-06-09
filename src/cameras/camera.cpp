#include "cameras/camera.h"

Camera::Camera()
{
    // sane defaults?
    setPosition(Vector3(0, 0, -100));
    setTarget(Vector3());

    // up is inverse because z is negative
    setUpDirection(Vector3(0, -1, 0));

    // 90 degrees
    setHorizontalFOV(90);

    // sane default? although in reality this should always be called by Tracer
    setRenderDimensions(640, 480);
}

Camera::~Camera()
{

}

void Camera::setPosition(Vector3 position)
{
    m_position = position;

    recalculate();
}

void Camera::setDirection(Vector3 direction)
{
    m_direction = direction;
    m_direction.normalise();

    recalculate();
}

void Camera::setTarget(Vector3 target)
{
    m_direction = Vector3(m_position, target);
    m_direction.normalise();

    recalculate();
}

void Camera::setUpDirection(Vector3 up)
{
    m_up = up;

    recalculate();
}

void Camera::setHorizontalFOV(int degrees)
{
    setHorizontalFOV((double)degrees);
}

void Camera::setHorizontalFOV(double degrees)
{
    m_horizontalFOV = (degrees) * (3.14159 / 180.0);
}

Vector3 Camera::getPosition()
{
    return m_position;
}

void Camera::setRenderDimensions(int width, int height)
{
    m_renderWidth = (double)width;
    m_renderHeight = (double)height;

    recalculate();
}

Ray Camera::getPixelRay(int pixelX, int pixelY)
{
    return getPixelRay((double)pixelX, (double)pixelY);
}

Ray Camera::getPixelRay(double pixelX, double pixelY)
{
    // direction of ray
    Vector3 rayDirection = m_direction + m_imagePlaneX*(pixelX/m_renderWidth - 0.5)*m_imagePlaneWidth
        + m_imagePlaneY*(pixelY/m_renderHeight - 0.5)*m_imagePlaneHeight;

    // don't forget to normalise
    rayDirection.normalise();

    // return Ray object
    return Ray(m_position, rayDirection);
}

void Camera::recalculate()
{
    m_aspectRatio = (double)m_renderWidth / (double)m_renderHeight;

    m_imagePlaneWidth = 2.0 * tan(m_horizontalFOV / 2.0);
    m_imagePlaneHeight = m_imagePlaneWidth / m_aspectRatio;

    m_imagePlaneX = m_direction.cross(m_up);
    m_imagePlaneX.normalise();
    m_imagePlaneY = m_imagePlaneX.cross(m_direction);
    m_imagePlaneY.normalise();
}