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
    bool isRegular;
    
    Material(const Vector3f &diffuseColor, 
             const Vector3f &specularColor = Vector3f::ZERO, 
             float shininess = 0,
             float refractionIndex = 0,
             float fadeDistance = 0) :
        _diffuseColor(diffuseColor),
        _specularColor(specularColor),
        _shininess(shininess),
        _refractionIndex(refractionIndex),
        _fadeDistance(fadeDistance)
    {
        isLight = false;
        isRegular = true;
    }

    virtual const Vector3f & getDiffuseColor() const {
        return _diffuseColor;
    }

    virtual const Vector3f & getSpecularColor(Vector3f location=Vector3f(0,0,0)) const {
        return _specularColor;
    }
    
    const float getRefractionIndex() const {
        return _refractionIndex;
    }
    
    const float getFadeDistance() const {
        return _fadeDistance;
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
    float    _fadeDistance;
};

class ToonMaterial : public Material
{
public:
    ToonMaterial(const Vector3f &diffuseColor,
             const Vector3f &specularColor = Vector3f::ZERO,
             float shininess = 0,
             float refractionIndex = 0) :
    Material(diffuseColor, specularColor, shininess, refractionIndex)
    {
        isLight = false;
        isRegular = true;
    }
    virtual Vector3f shade(const Ray &ray,
                           const Hit &hit,
                           const Vector3f &dirToLight,
                           const Vector3f &lightIntensity) override;
};

class PhotonMaterial : public Material
{
public:
    bool isRegular = false;
    PhotonMaterial(Vector3f color,
                   float pReflectionDiffuse,
                   float pReflectionSpecular,
                   float pRefraction,
                   float pAbsorption,
                   float refractionIndex,
                   bool diffracting,
                   float shininess,
                   float fadeDistance) :
    Material(color, color, shininess, refractionIndex, fadeDistance),
    _color(color),
    _pReflectionDiffuse(pReflectionDiffuse),
    _pReflectionSpecular(pReflectionSpecular),
    _pRefraction(pRefraction),
    _pAbsorption(pAbsorption),
    _refractionIndex(refractionIndex),
    _isDiffracting(diffracting)
    {
        isRegular = false;
    }
    
    virtual Vector3f getColor(Vector3f location) const {
        return _color;
    }
    
    float getPReflectionDiffuse() {
        return _pReflectionDiffuse;
    }
    float getPReflectionSpecular() {
        return _pReflectionSpecular;
    }
    float getPTransmission() {
        return _pRefraction;
    }
    float getPAbsorption() {
        return _pAbsorption;
    }
    float getRefractionIndex() {
        return _refractionIndex;
    }
    bool getIsDiffracting() {
        return _isDiffracting;
    }
    
private:
    Vector3f _color;
    float _pReflectionDiffuse;
    float _pReflectionSpecular;
    float _pRefraction;
    float _pAbsorption;
    float _refractionIndex;
    bool _isDiffracting;
};

class MultiColoredMaterial : public PhotonMaterial
{
public:
    MultiColoredMaterial(Vector3f color,
                         float pReflectionDiffuse,
                         float pReflectionSpecular,
                         float pRefraction,
                         float pAbsorption,
                         float refractionIndex,
                         std::vector<Vector3f> colors) :
    PhotonMaterial(color, pReflectionDiffuse, pReflectionSpecular, pRefraction, pAbsorption, refractionIndex, false, 0, 0),
    _colors(colors)
    {
        isRegular = false;
        _colors.push_back(Vector3f(1,0.6,0.6));
        _colors.push_back(Vector3f(0.6,0.6,1));
    }
    
    Vector3f getColor(Vector3f location) const override {
        return location.y() > 0.75 ? _colors[0] : _colors[1];
    }
        
    const Vector3f & getSpecularColor(Vector3f location) const override {
        return location.y() > 0.75 ? _colors[0] : _colors[1];
    }
    
private:
    std::vector<Vector3f> _colors;
};



#endif // MATERIAL_H
