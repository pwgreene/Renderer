#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Ray.h"
#include "Material.h"

#include <string>


class Object3D
{
public:
    Object3D()
    {
        material = NULL;
    }

    virtual ~Object3D() {}

    Object3D(Material *material)
    {
        this->material = material;
    }

    std::string getType() const {
        return type;
    }
    Material * getMaterial() const {
        return material;
    }

    virtual bool intersect(const Ray &r, float tmin, Hit &h) const = 0;

    std::string   type;
    Material*     material;
    PhotonMaterial* photonMaterial;
};


class Sphere : public Object3D
{
public:
    // default contstructor: unit ball at origin
    Sphere() {
        _center = Vector3f(0.0, 0.0, 0.0);
        _radius = 1.0f;
    }

    Sphere(const Vector3f &center,
        float radius,
        Material *material) :
        Object3D(material),
        _center(center),
        _radius(radius)
    {
    }

    virtual bool intersect(const Ray &r, float tmin, Hit &h) const override;

private:
    Vector3f _center;
    float    _radius;
};

class Group : public Object3D
{
public:
    // Return true if intersection found
    virtual bool intersect(const Ray &r, float tmin, Hit &h) const override;

    // Add object to group
    void addObject(Object3D *obj);

    // Return number of objects in group
    int getGroupSize() const;
private:
    std::vector<Object3D*> m_members;
};

// TODO: Implement Plane representing an infinite plane
// Choose your representation, add more fields and fill in the functions
class Plane : public Object3D
{
public:
    Plane(const Vector3f &normal, float d, Material *m);

    virtual bool intersect(const Ray &r, float tmin, Hit &h) const override;

private:
    Vector3f _normal;
    float _d; //offset from origin
};



// TODO: implement this class.
// Add more fields as necessary, but do not remove getVertex and getNormal
// as they are currently called by the Octree for optimization
class Triangle : public Object3D
{
public:
    Triangle(const Vector3f &a,
        const Vector3f &b,
        const Vector3f &c,
        const Vector3f &na,
        const Vector3f &nb,
        const Vector3f &nc,
        Material *m) :
        Object3D(m)
    {
        _v[0] = a;
        _v[1] = b;
        _v[2] = c;
        _normals[0] = na;
        _normals[1] = nb;
        _normals[2] = nc;
    }

    virtual bool intersect(const Ray &ray, float tmin, Hit &hit) const override;

    const Vector3f & getVertex(int index) const {
        assert(index < 3);
        return _v[index];
    }

    const Vector3f & getNormal(int index) const {
        assert(index < 3);
        return _normals[index];
    }

private:
    Vector3f _v[3];
    Vector3f _normals[3];
    
};

class Rectangle : public Object3D
{
public:
    Rectangle(const Vector3f &normal, const Vector3f &vecmin, const Vector3f &vecmax, Material *m) :
    Object3D(m),
    _normal(normal),
    _vecmin(vecmin),
    _vecmax(vecmax)
    {
        
    }
    
    Rectangle(const Vector3f &normal, const Vector3f p1, const Vector3f p2, const Vector3f p3, const Vector3f p4, Material *m) :
    Object3D(m),
    _normal(normal)
    {
        std::vector<float> x = {p1.x(), p2.x(), p3.x(), p4.x()};
        std::vector<float> y = {p1.y(), p2.y(), p3.y(), p4.y()};
        std::vector<float> z = {p1.z(), p2.z(), p3.z(), p4.z()};
        _vecmin[0] = minvec(x);
        _vecmin[1] = minvec(y);
        _vecmin[2] = minvec(z);
        _vecmax[0] = maxvec(x);
        _vecmax[1] = maxvec(y);
        _vecmax[2] = maxvec(z);
        
    }
    virtual bool intersect(const Ray &r, float tmin, Hit &h) const override;
    
private:
    Vector3f _normal;
    Vector3f _vecmin; //(X1, Y1, Z1) --- Axis aligned!
    Vector3f _vecmax; //(X2, Y2, Z2)
//    Triangle triangle1;
//    Triangle triangle2;
    float minvec(std::vector<float> v) {
        float smallest = v[0];
        for (int i = 1; i < v.size(); i++) {
            smallest = smallest < v[i] ? smallest : v[i];
        }
        return smallest;
    }
    float maxvec(std::vector<float> v) {
        float largest = v[0];
        for (int i = 1; i < v.size(); i++) {
            largest = largest > v[i] ? largest : v[i];
        }
        return largest;
    }
};


// TODO implement this class
// So that the intersect function first transforms the ray
// Add more fields as necessary
class Transform : public Object3D
{
public:
    Transform(const Matrix4f &m, Object3D *obj);

    virtual bool intersect(const Ray &r, float tmin, Hit &h) const override;

private:
    Object3D *_object; //un-transformed object
    Matrix4f _m; //transformation matrix
};


#endif
