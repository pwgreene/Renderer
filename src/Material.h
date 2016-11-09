#ifndef MATERIAL_H
#define MATERIAL_H

#include <cassert>
#include <vecmath.h>

#include "Ray.h"
#include "Image.h"
#include "Vector3f.h"

#include <string>

class Material
{
  public:
      bool isLight;
    
    Material(const Vector3f &diffuseColor, 
             const Vector3f &specularColor = Vector3f::ZERO, 
             float shininess = 0,
             float refractionIndex = 0) :
        _diffuseColor(diffuseColor),
        _specularColor(specularColor),
        _shininess(shininess),
        _refractionIndex(refractionIndex)
    {
        isLight = false;
    }

    const Vector3f & getDiffuseColor() const {
        return _diffuseColor;
    }

    const Vector3f & getSpecularColor() const {
        return _specularColor;
    }
    
    const float getRefractionIndex() const {
        return _refractionIndex;
    }

    virtual Vector3f shade(const Ray &ray,
        const Hit &hit,
        const Vector3f &dirToLight,
        const Vector3f &lightIntensity);

protected:

    Vector3f _diffuseColor;
    Vector3f _specularColor;
    float    _shininess;
    float    _refractionIndex; //a refractionIndex of 0 indicates no transparency (for this implementation)
};

class PhotonMaterial
{
public:
    PhotonMaterial(Vector3f color,
                   float pReflectionDiffuse,
                   float pReflectionSpecular,
                   float pRefraction,
                   float pAbsorption,
                   float refractionIndex) :
    _color(color),
    _pReflectionDiffuse(pReflectionDiffuse),
    _pReflectionSpecular(pReflectionSpecular),
    _pRefraction(pRefraction),
    _pAbsorption(pAbsorption),
    _refractionIndex(refractionIndex)
    {
    }
    
    Vector3f getColor() {
        return _color;
    }
    
    float getPReflectionDiffuse() {
        return _pReflectionDiffuse;
    }
    float getPReflectionSpecular() {
        return _pReflectionSpecular;
    }
    float getPRefraction() {
        return _pRefraction;
    }
    float getPAbsorption() {
        return _pAbsorption;
    }
    float getRefractionIndex() {
        return _refractionIndex;
    }
    
private:
    Vector3f _color;
    float _pReflectionDiffuse;
    float _pReflectionSpecular;
    float _pRefraction;
    float _pAbsorption;
    float _refractionIndex;
};



#endif // MATERIAL_H
