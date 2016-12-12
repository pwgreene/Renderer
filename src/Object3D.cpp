#include "Object3D.h"

bool Sphere::intersect(const Ray &r, float tmin, Hit &h) const
{
    // BEGIN STARTER

    // We provide sphere intersection code for you.
    // You should model other intersection implementations after this one.

    // Locate intersection point ( 2 pts )
    const Vector3f &rayOrigin = r.getOrigin(); //Ray origin in the world coordinate
    const Vector3f &dir = r.getDirection();

    Vector3f origin = rayOrigin - _center;      //Ray origin in the sphere coordinate

    float a = dir.absSquared();
    float b = 2 * Vector3f::dot(dir, origin);
    float c = origin.absSquared() - _radius * _radius;

    // no intersection
    if (b * b - 4 * a * c < 0) {
        return false;
    }

    float d = sqrt(b * b - 4 * a * c);

    float tplus = (-b + d) / (2.0f*a);
    float tminus = (-b - d) / (2.0f*a);

    // the two intersections are at the camera back
    if ((tplus < tmin) && (tminus < tmin)) {
        return false;
    }

    float t = 10000;
    // the two intersections are at the camera front
    if (tminus > tmin) {
        t = tminus;
    }

    // one intersection at the front. one at the back 
    if ((tplus > tmin) && (tminus < tmin)) {
        t = tplus;
    }

    if (t < h.getT()) {
        Vector3f normal = r.pointAtParameter(t) - _center;
        normal = normal.normalized();
        h.set(t, this->material, normal);
        return true;
    }
    // END STARTER
    return false;
}

// Add object to group
void Group::addObject(Object3D *obj) {
    m_members.push_back(obj);
}

// Return number of objects in group
int Group::getGroupSize() const {
    return (int)m_members.size();
}

bool Group::intersect(const Ray &r, float tmin, Hit &h) const
{
    // BEGIN STARTER
    // we implemented this for you
    bool hit = false;
    for (Object3D* o : m_members) {
        if (o->intersect(r, tmin, h)) {
            hit = true;
        }
    }
    return hit;
    // END STARTER
}


Plane::Plane(const Vector3f &normal, float d, Material *m) : Object3D(m) {
    material = m;
    _d = d;
    _normal = normal;
}
bool Plane::intersect(const Ray &r, float tmin, Hit &h) const
{
    float t = (_d - Vector3f::dot(_normal, r.getOrigin())) / Vector3f::dot(_normal, r.getDirection());
    //verify intersection is closer than previous and not behind eye
    if (t < h.getT() && t > tmin) {
        h.set(t, this->material, _normal);
        return true;
    }
    return false;
}
bool Triangle::intersect(const Ray &r, float tmin, Hit &h) const 
{
    Vector3f a = getVertex(0), b = getVertex(1), c = getVertex(2);
    Matrix3f A = Matrix3f(a[0]-b[0], a[0]-c[0], r.getDirection()[0],
                          a[1]-b[1], a[1]-c[1], r.getDirection()[1],
                          a[2]-b[2], a[2]-c[2], r.getDirection()[2]);
    Vector3f B = Vector3f(a[0]-r.getOrigin()[0],
                          a[1]-r.getOrigin()[1],
                          a[2]-r.getOrigin()[2]);
    //x is [beta, gamma, t]
//    if (A.determinant() < 0) {
//        return false;
//    }
    Vector3f x = A.inverse() * B;
    float alpha, beta = x[0], gamma = x[1], t = x[2];
    alpha = 1 - beta - gamma;
    if (t < h.getT() && t > tmin &&
        beta <= 1 && beta >= 0 && gamma <= 1 && gamma >= 0 && alpha <= 1 && alpha >= 0) {
        Vector3f P = alpha*a + beta*b + gamma*c;
        Vector3f normal = alpha*getNormal(0) + beta*getNormal(1) + gamma*getNormal(2);
        h.set(t, this->material, normal);
        return true;
    }
    return false;
}

void swapIfBigger(float &a, float &b) {
    float temp;
    if (a > b) {
        temp = a;
        a = b;
        b = temp;
    }
}

bool Rectangle::intersect(const Ray &r, float tmin, Hit &h) const
{
    if (Vector3f::dot(-r.getDirection(), _normal) < 0.001)
        return false;
    //calculate intersection of ray with axis-aligned plane
    float t_start;
    float t_end;
    float temp;
    Vector2f x_interval = Vector2f((_vecmin[0] - r.getOrigin()[0])/r.getDirection()[0],
                                   (_vecmax[0] - r.getOrigin()[0])/r.getDirection()[0]);
    swapIfBigger(x_interval[0], x_interval[1]);
    t_start = x_interval[0], t_end = x_interval[1];
    
    Vector2f y_interval = Vector2f((_vecmin[1] - r.getOrigin()[1])/r.getDirection()[1],
                                   (_vecmax[1] - r.getOrigin()[1])/r.getDirection()[1]);
    swapIfBigger(y_interval[0], y_interval[1]);
    if (y_interval[0] > t_start)
        t_start = y_interval[0];
    if (y_interval[1] < t_end)
        t_end = y_interval[1];
    
    Vector2f z_interval = Vector2f((_vecmin[2] - r.getOrigin()[2])/r.getDirection()[2],
                                   (_vecmax[2] - r.getOrigin()[2])/r.getDirection()[2]);
    swapIfBigger(z_interval[0], z_interval[1]);
    if (z_interval[0] > t_start)
        t_start = z_interval[0];
    if (z_interval[1] < t_end)
        t_end = z_interval[1];
    
    float new_t = t_start > tmin ? t_start : t_end;
    if ((t_start <= t_end) && (t_end >= tmin) && new_t < h.getT()) {
        h.set(new_t, this->material, _normal);
        return true;
    }
    return false;
}


Transform::Transform(const Matrix4f &m,
    Object3D *obj) : _object(obj) {
    _object = obj;
    _m = m;
}
bool Transform::intersect(const Ray &r, float tmin, Hit &h) const
{
    //position transformed by whole M
    Vector4f origin_os = _m.inverse() * Vector4f(r.getOrigin(), 1);
    //direction transformed by just translation component
    Vector3f direction_os = _m.inverse().getSubmatrix3x3(0, 0) * r.getDirection();
    Ray r_os = Ray(origin_os.xyz(), direction_os);
    bool isIntersected = _object->intersect(r_os, tmin, h);
    //transform normals
    if (isIntersected) {
        Matrix4f invTransposeM = _m.inverse().transposed();
        Vector3f normal = invTransposeM.getSubmatrix3x3(0,0) * h.getNormal();
        h.set(h.getT(), h.getMaterial(), normal.normalized());
    }
    return isIntersected;
}