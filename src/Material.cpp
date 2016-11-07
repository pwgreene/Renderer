#include "Material.h"
#include "Light.h"

Vector3f Material::shade(const Ray &ray,
    const Hit &hit,
    const Vector3f &dirToLight,
    const Vector3f &lightIntensity)
{
    
    Vector3f I_diffuse, I_specular;
    //diffuse calculations
    Vector3f N = hit.getNormal();
    float dot = Vector3f::dot(dirToLight, N);
    float clamp = dot > 0.f ? dot : 0.f;
    I_diffuse = clamp * lightIntensity;
    
    //specular phong terms
    Vector3f dir = ray.getDirection();
    Vector3f R = dir - 2 * Vector3f::dot(dir, N) * N;
    R.normalize();
    dot = Vector3f::dot(dirToLight, R);
    clamp = dot > 0.f ? dot : 0.f;
    I_specular = std::pow(clamp, _shininess) * lightIntensity;
    
    return I_diffuse*getDiffuseColor() + I_specular*getSpecularColor();
    
}