#include "Camera.h"

//rotates the camera about (0,0,0), maintaiing distance from (0,0,0)
void PerspectiveCamera::rotateY(float degrees)
{
    Vector3f vectorToOrigin = Vector3f(0,0,0) - Vector3f(_center.x(), 0, _center.z());
    float r = vectorToOrigin.abs();
    float theta = degrees;
    float newX = r * cos(theta);
    float newZ = r * sin(theta);
    _center = Vector3f(newX, _center.y(), newZ);
    _direction = (Vector3f(0, 0, 0) - _center).normalized();
    _horizontal = Vector3f::cross(_direction, _up).normalized();
}