#ifndef LIGHT_H
#define LIGHT_H

#include <Vector3f.h>

#include "Object3D.h"
#include "Material.h"

#include <limits>


class Light
{
  public:
    virtual ~Light() { }

    // in:  p           is the point to be shaded
    // out: tolight     is direction from p to light source
    // out: intensity   is the illumination intensity (RGB) at point p
    // out: distToLight is absolute distance from P to light (infinity for directional light)
    virtual void getIllumination(const Vector3f &p, 
                                 Vector3f &tolight, 
                                 Vector3f &intensity, 
                                 float &distToLight) const = 0;
    
    static float degreesToRadians(float deg) {
        return deg * 3.141592654 / 180.;
    }
};

class DirectionalLight : public Light
{
  public:
    bool isArea;
    
    DirectionalLight(const Vector3f &d, const Vector3f &c) :
    _direction(d.normalized()),
    _color(c)
    {
        isArea = false;
    }

    virtual void getIllumination(const Vector3f &p,
        Vector3f &tolight,
        Vector3f &intensity,
        float &distToLight) const override;
    

  private:
    Vector3f _direction;
    Vector3f _color;
};

class PointLight : public Light
{
  public:
    bool isArea;
    
    PointLight(const Vector3f &p, const Vector3f &c, float falloff) :
    _position(p),
    _color(c),
    _falloff(falloff)
    
    {
        isArea = false;
    }

    virtual void getIllumination(const Vector3f &p,
        Vector3f &tolight,
        Vector3f &intensity,
        float &distToLight) const override;
    

  private:
    Vector3f _position;
    Vector3f _color;
    float _falloff;
};

class SpotLight : public Light
{
public:
    bool isArea;
    
    SpotLight(const Vector3f &p, const Vector3f &d, const Vector3f &c, float hotspotAngle, float falloffAngle, int type) :
    _position(p),
    _direction(d),
    _color(c),
    _hotspotAngle(degreesToRadians(hotspotAngle)),
    _falloffAngle(degreesToRadians(falloffAngle)),
    _falloffDegree(type)
    {
        isArea = false;
    }
    
    virtual void getIllumination(const Vector3f &p,
        Vector3f &tolight,
        Vector3f &intensity,
        float &distToLight) const override;
    
    
private:
    Vector3f _position;
    Vector3f _direction;
    Vector3f _color;
    float _hotspotAngle;
    float _falloffAngle;
    int _falloffDegree;
};


class LuminousMaterial : public Light, public Material
{
public:
    LuminousMaterial(const Vector3f &diffuseColor,
                     const Vector3f &specularColor = Vector3f::ZERO,
                     float shininess = 0,
                     float refractionIndex = 0,
                     const Vector3f &lightColor = Vector3f(1,1,1),
                     float falloff = 1.0) :
    _color(lightColor),
    _position(Vector3f(0,0,0)),
    _falloff(falloff),
    Material(lightColor, lightColor, shininess, refractionIndex)
    {
        isLight = true;
    }
    
    
    virtual void getIllumination(const Vector3f &p,
                                 Vector3f &tolight,
                                 Vector3f &intensity,
                                 float &distToLight) const override;
    
    void setPosition(Vector3f p) {
        _position = p;
    }
    
protected:
    Vector3f    _color;
    Vector3f    _position;
    Vector3f    _intensity;
    float       _falloff;
    
};

#endif // LIGHT_H
