#include "Light.h"

#include <math.h>
#include <random>


void DirectionalLight::getIllumination(const Vector3f &p,
                             Vector3f &tolight, 
                             Vector3f &intensity, 
                             float &distToLight) const
{
    // the direction to the light is the opposite of the
    // direction of the directional light source

    // BEGIN STARTER
    tolight = -_direction;
    intensity  = _color;
    distToLight = std::numeric_limits<float>::max();
    // END STARTER
}
void PointLight::getIllumination(const Vector3f &p, 
                             Vector3f &tolight, 
                             Vector3f &intensity, 
                             float &distToLight) const
{
    // tolight, intensity, distToLight are outputs
    Vector3f lightToPoint = _position - p;
    tolight = lightToPoint.normalized();
    distToLight = lightToPoint.abs();
    intensity = _color / (_falloff*distToLight*distToLight);
}

void SpotLight::getIllumination(const Vector3f &p,
                             Vector3f &tolight,
                             Vector3f &intensity,
                             float &distToLight) const
{
    Vector3f lightToPoint = _position - p;
    tolight = lightToPoint.normalized();
    float cosangle = Vector3f::dot(-tolight, _direction.normalized());
    //falloff due to angle
    distToLight = lightToPoint.abs();
    float angle = std::acos(cosangle);
    //printf("%f, %f, %f\n", _hotspotAngle, _falloffAngle, angle);
    float angleDiff;
    if (angle < _hotspotAngle) {
        angleDiff = 1.0;
    } else if ((angle >= _hotspotAngle) && (angle < _falloffAngle)) {
        if (_falloffDegree <= 1) { //linear falloff function
            angleDiff = -1.0/(_falloffAngle - _hotspotAngle) * (angle - _falloffAngle);
        } else { //general degree falloff function
            angleDiff = -pow(1./(_falloffAngle-_hotspotAngle), _falloffDegree) *
                         pow(angle-_hotspotAngle, _falloffDegree) + 1.0;
        }
    } else {
        angleDiff = 0;
    }
    intensity = _color * angleDiff;
}

void LuminousMaterial::getIllumination(const Vector3f &p,
                                Vector3f &tolight,
                                Vector3f &intensity,
                                float &distToLight) const
{
    // tolight, intensity, distToLight are outputs
    Vector3f lightToPoint = _position - p;
    tolight = lightToPoint.normalized();
    distToLight = lightToPoint.abs();
    intensity = _color / (_falloff*distToLight);
}

void QuadLight::getIllumination(const Vector3f &p,
                                       Vector3f &tolight,
                                       Vector3f &intensity,
                                       float &distToLight) const
{
    // tolight, intensity, distToLight are outputs
    Vector3f lightToPoint = points[0] - p;
    tolight = lightToPoint.normalized();
    distToLight = lightToPoint.abs();
    intensity = _color / (distToLight*distToLight);
}

Vector3f QuadLight::getRandomPosition() {
    Vector4f randomWeights((float)rand(), (float)rand(), (float)rand(), (float)rand());
    randomWeights = randomWeights / (randomWeights[0] + randomWeights[1] + randomWeights[2] + randomWeights[3]);
    return Vector3f(points[0].x()*randomWeights[0] + points[1].x()*randomWeights[1] + points[2].x()*randomWeights[2] + points[3].x()*randomWeights[3],
                    points[0].y()*randomWeights[0] + points[1].y()*randomWeights[1] + points[2].y()*randomWeights[2] + points[3].y()*randomWeights[3],
                    points[0].z()*randomWeights[0] + points[1].z()*randomWeights[1] + points[2].z()*randomWeights[2] + points[3].z()*randomWeights[3]);
}
