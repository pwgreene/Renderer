#include "Camera.h"

//rotates the camera about (0,0,0), maintaiing distance from (0,0,0)
void PerspectiveCamera::rotateY(float degrees)
{
    Vector3f vectorToOrigin = Vector3f(0,0,0) - _center;
    float r = vectorToOrigin.abs();
    float theta = Vector3f::degreesToRadians(degrees);
    float newX = r * cos(theta);
    float newZ = r * sin(theta);
    _direction = (Matrix4f::lookAt(_direction, Vector3f(0,0,0), Vector3f(0,1,0)) * Vector4f(_direction)).xyz();
    _center = Vector3f(newX, _center.y(), newZ);
}