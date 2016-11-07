#ifndef RAY_H
#define RAY_H

#include "Vector3f.h"

#include <cassert>
#include <limits>
#include <iostream>
#include <vecmath.h>

// This file defines the Ray and Hit classes

// Ray class mostly copied from Peter Shirley and Keith Morley
class Ray
{
  public:
    bool isInsideObject;
    
    Ray(const Vector3f &orig, const Vector3f &dir, bool insideObject = false) :
        _origin(orig),
        _direction(dir)
    {
        isInsideObject = insideObject;
    }
    
    const Vector3f getOrigin() const {
        return _origin;
    }

    const Vector3f getDirection() const {
        return _direction;
    }

    Vector3f pointAtParameter(float t) const {
        return _origin + _direction * t;
    }
    
    //returns the ray in the new refracted direction
    Ray refract(Vector3f normal, float fromIndex, float toIndex, Vector3f point) {
        normal = isInsideObject ? -normal : normal;
        float ratio = fromIndex / toIndex; //n_r = n_i / n_T
        Vector3f I = -_direction;
        float sqrtTerm = 1 - std::pow(ratio, 2.0f)*(1 - std::pow(Vector3f::dot(normal, I), 2.0f));
        Vector3f newDirection;
        if (sqrtTerm < 0) {//total internal reflection
            newDirection = I - 2 * Vector3f::dot(I, normal) * normal;
            return Ray(point, newDirection.normalized(), true);
        }
        else {
            //leave/enter material
            newDirection = (ratio*Vector3f::dot(normal, I) - sqrtTerm)*normal - ratio*I;
//            if (ratio != 1.0) {
//                printf("%f\n", ratio);
//                newDirection.print();
//                I.print();
//            }
            return Ray(point, newDirection.normalized(), !isInsideObject);
        }
    }

  private:
    Vector3f _origin;
    Vector3f _direction;

};

inline std::ostream &
operator<<(std::ostream &os, const Ray &r)
{
    os << "Ray <" << r.getOrigin() << ", " << r.getDirection() << ">";
    return os;
}

class Material;
class Hit
{
public:
    // Constructors
    Hit() :
        material(NULL),
        t(std::numeric_limits<float>::max())
    {
    }

    Hit(float argt, Material *argmaterial, const Vector3f &argnormal) :
        t(argt),
        material(argmaterial),
        normal(argnormal.normalized())
    {
    }

    float getT() const
    {
        return t;
    }

    Material * getMaterial() const
    {
        return material;
    }

    const Vector3f getNormal() const
    {
        return normal;
    }

    void set(float t, Material *material, const Vector3f &normal)
    {
        this->t = t;
        this->material = material;
        this->normal = normal.normalized();
    }

    float     t;
    Material* material;
    Vector3f  normal;
};

inline std::ostream &
operator<<(std::ostream &os, const Hit &h)
{
    os << "Hit <" << h.getT() << ", " << h.getNormal() << ">";
    return os;
}


#endif // RAY_H
