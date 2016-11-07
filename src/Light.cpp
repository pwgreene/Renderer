#include "Light.h"

#include <math.h>


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
//    float cosDiff = cosangle - cos(_hotspotAngle);
//    float angleDiff = cosDiff < 0 ? std::pow((1-cosDiff),5) : 1.0;
//    distToLight = lightToPoint.abs();
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
