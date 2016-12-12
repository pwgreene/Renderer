#ifndef LIGHT_H
#define LIGHT_H

#include <Vector3f.h>

#include "Object3D.h"
#include "Material.h"

#include <limits>
#include <random>


class Light
{
  public:
    bool isArea;
    float power;
    virtual ~Light() { }

    // in:  p           is the point to be shaded
    // out: tolight     is direction from p to light source
    // out: intensity   is the illumination intensity (RGB) at point p
    // out: distToLight is absolute distance from P to light (infinity for directional light)
    virtual void getIllumination(const Vector3f &p, 
                                 Vector3f &tolight, 
                                 Vector3f &intensity, 
                                 float &distToLight) const = 0;
    
    virtual Vector3f getRandomPosition() const = 0;
    
    virtual Vector3f getRandomDirection() = 0;
    
    virtual Vector3f getCenter() const = 0;
    
    virtual Vector3f getColor() const = 0;
    
    static float degreesToRadians(float deg) {
        return deg * 3.141592654 / 180.;
    }
};

class DirectionalLight : public Light
{
  public:
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
    
    virtual Vector3f getColor() const override {
        return _color;
    }
    
    virtual Vector3f getRandomDirection() override {
        return _direction;
    }
    
    virtual Vector3f getRandomPosition() const override {
        return Vector3f(0,0,0);
    }
    
    virtual Vector3f getCenter() const override {
        return Vector3f(0,0,0);
    }

  private:
    Vector3f _direction;
    Vector3f _color;
};

class PointLight : public Light
{
public:
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
    
    virtual Vector3f getColor() const override {
        return _color;
    }
    
    virtual Vector3f getRandomPosition() const override {
        return _position;
    }
    
    virtual Vector3f getCenter() const override {
        return _position;
    }
    
    virtual Vector3f getRandomDirection() override {
        return Vector3f::CosWeightedRandomHemisphereDirection(Vector3f(1,0,0));
        //TODO return Vector3f::CosWeightedRandomHemisphereDirection(Vector3f(-1,0,0)) with 50% chance
    }

  private:
    Vector3f _position;
    Vector3f _color;
    float _falloff;
};

class SpotLight : public Light
{
public:
    
    SpotLight(const Vector3f &p, const Vector3f &d, const Vector3f &c, float hotspotAngle, float falloffAngle, float pow, int type) :
    _position(p),
    _direction(d),
    _color(c),
    _hotspotAngle(degreesToRadians(hotspotAngle)),
    _falloffAngle(degreesToRadians(falloffAngle)),
    _falloffDegree(type)
    {
        isArea = false;
        power = pow;
    }
    
    virtual void getIllumination(const Vector3f &p,
        Vector3f &tolight,
        Vector3f &intensity,
        float &distToLight) const override;
    
    virtual Vector3f getColor() const override {
        return _color;
    }
    
    virtual Vector3f getRandomDirection() override {
        //random distribution of points on circle (not uniform-more points concentrated at center)
//        float r = rand() / RANDMAX; // [0, 1]
//        float theta = rand() / RANDMAX * 2*PI
        Vector3f randDirection = Vector3f::CosWeightedRandomHemisphereDirection(_direction);
        while (acos(Vector3f::dot(randDirection.normalized(), _direction.normalized())) > _hotspotAngle) {
            randDirection = Vector3f::CosWeightedRandomHemisphereDirection(_direction);
        }
        return randDirection;
    }
    
    virtual Vector3f getRandomPosition() const override {
        return _position;
    }
    
    virtual Vector3f getCenter() const override {
        return _position;
    }
    
    
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
        power = 300;
    }
    
    
    virtual void getIllumination(const Vector3f &p,
                                 Vector3f &tolight,
                                 Vector3f &intensity,
                                 float &distToLight) const override;
    
    virtual Vector3f getColor() const override {
        return _color;
    }
    
    void setPosition(Vector3f p) {
        _position = p;
    }
    
    virtual Vector3f getRandomPosition() const override {
        return _position;
    }
    
    virtual Vector3f getCenter() const override {
        return _position;
    }
    
    virtual Vector3f getRandomDirection() override {
        //implement this if needed!
        return Vector3f(0,0,0);
    }
    
protected:
    Vector3f    _color;
    Vector3f    _position;
    Vector3f    _intensity;
    float       _falloff;
    
};

class QuadLight : public Light
{
public:
    std::vector<Vector3f> points;
    QuadLight(Vector3f A,
                Vector3f B,
                Vector3f C,
                Vector3f D,
                Vector3f normal,
                Vector3f color,
                float pow) :
    _normal(normal),
    _color(color)
    {
        isArea = true;
        points.push_back(A);
        points.push_back(B);
        points.push_back(C);
        points.push_back(D);
        tmin = 0.01;
        power = pow;
    }
    
    virtual void getIllumination(const Vector3f &p,
                                 Vector3f &tolight,
                                 Vector3f &intensity,
                                 float &distToLight) const override;
    
    virtual Vector3f getRandomPosition() const override;
    
    virtual Vector3f getCenter() const override;
    
    virtual Vector3f getRandomDirection() override {
        return Vector3f::CosWeightedRandomHemisphereDirection(_normal);
    }
    
    virtual Vector3f getColor() const override {
        return _color;
    }
    
    Vector3f getNormal() const {
        return _normal;
    }
    
private:
    Vector3f _normal;
    Vector3f _color;
    float tmin;
};

#endif // LIGHT_H
