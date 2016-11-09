#include "Renderer.h"

#include "ArgParser.h"
#include "Camera.h"
#include "Image.h"
#include "Ray.h"
#include "VecUtils.h"

#include <limits>
#include <random>


Renderer::Renderer(const ArgParser &args) :
    _args(args),
    _scene(args.input_file)
{
    gen = std::mt19937(rd());
    dis = std::uniform_int_distribution<>(-100, 100);
    struct Photon root;
    photonMap = new kdTree3D(root, 0, true);

}

Vector3f Renderer::addNoiseToVector(Vector3f v) {
    return Vector3f(v[0] + dis(gen)/500.f, v[1] + dis(gen)/500.f, v[2] + dis(gen)/500.f);
}

void
Renderer::Render()
{
    int w = _args.width;
    int h = _args.height;

    Image image(w, h);
    Image nimage(w, h);
    Image dimage(w, h);

    // loop through all the pixels in the image
    // generate all the samples

    // This look generates camera rays and callse traceRay.
    // It also write to the color, normal, and depth images.
    // You should understand what this code does.
    
    if (_args.photonmapping) {
        mapPhotons(_args.photonmapping);
    }
    Vector3f color;
    Camera* cam = _scene.getCamera();
    Vector3f gatherSpot;
    int nGatherPhotons = 50;
    float maxDistance;
    sway::bounded_priority_queue<struct Photon, std::vector<struct Photon>, cmp> bpq(nGatherPhotons, cmp(gatherSpot));
    for (int y = 0; y < h; ++y) {
        float ndcy = 2 * (y / (h - 1.0f)) - 1.0f;
        for (int x = 0; x < w; ++x) {
            float ndcx = 2 * (x / (w - 1.0f)) - 1.0f;
            // Use PerspectiveCamera to generate a ray.
            // You should understand what generateRay() does.
            Ray r = cam->generateRay(Vector2f(ndcx, ndcy));
            Hit h;
            if (_args.photonmapping) {
                maxDistance = 0.1;
                _scene.getGroup()->intersect(r, 0.01, h);
                gatherSpot = r.pointAtParameter(h.getT());
                //TODO get color from photon map at hit area (monte carlo integration)
                photonMap->kNearest(gatherSpot, bpq, maxDistance);
                color = kdTree3D::colorAverage(bpq); //clears bpq
            } else {
                color = traceRay(r, cam->getTMin(), _args.bounces, h);
            }
            image.setPixel(x, y, color);
            nimage.setPixel(x, y, (h.getNormal() + 1.0f) / 2.0f);
            float range = (_args.depth_max - _args.depth_min);
            if (range) {
                dimage.setPixel(x, y, Vector3f((h.t - _args.depth_min) / range));
            }
        }
    }
    // END SOLN

    // save the files 
    if (_args.output_file.size()) {
        image.savePNG(_args.output_file);
    }
    if (_args.depth_file.size()) {
        dimage.savePNG(_args.depth_file);
    }
    if (_args.normals_file.size()) {
        nimage.savePNG(_args.normals_file);
    }
}

void
Renderer::mapPhotons(int nPhotons)
{
    
    //TODO fill this in
    //monte carlo photon tracing for a nPhotons (100,000?) originating from the light source(s)
    int photonsMapped = 0;
    Hit h;
    for (Light *light : _scene.lights) {
        //printf("%d\n", nPhotons);
        while (photonsMapped < nPhotons) {
            //if (photonsSent >= nPhotons) break;
            Vector3f origin = light->getRandomPosition();
            Vector3f direction = light->getRandomDirection();
            //origin.print();
            h = Hit();
            Ray photonRay(origin, direction);
            if (_scene.getGroup()->intersect(photonRay, 0.01, h)) {
                struct Photon photon;
                photon.color = h.getMaterial()->getDiffuseColor();
                photon.position = photonRay.pointAtParameter(h.getT());
                photon.direction = direction.normalized();
                photonMap->add(photon);
                photonsMapped++;
            }
        }
    }
    printf("Photons Mapped: %d\n", photonMap->size);
}


Vector3f
Renderer::traceRay(Ray &r,
    float tmin,
    int bounces,
    Hit &h)
{
    // The starter code only implements basic drawing of sphere primitives.
    // You will implement phong shading, recursive ray tracing, and shadow rays.

    if (_scene.getGroup()->intersect(r, tmin, h)) {
        Light *light;
        Vector3f toLight;
        Vector3f color = _scene.getAmbientLight() * h.getMaterial()->getDiffuseColor();
        Vector3f intensity;
        Hit shadowHit;
        Hit lightHit;
        Hit refractionHit;
        int numScatteredVectors = 1000;
        float epsilon = 0.01;
        float distToLight;
        //location of the hit
        Vector3f p = r.pointAtParameter(h.getT());
        //go through each light an calculate its contribution to the color
        //check area lights first
        if (!h.getMaterial()->isLight) {
            for (LuminousMaterial *light : _scene.areaLights) {
                Vector3f totalLight = Vector3f(0, 0, 0);
                Vector3f hitSpot = r.pointAtParameter(h.getT());
                for (int v = 0; v < numScatteredVectors; v++) {
                    lightHit = Hit();
                    //printf("%d\n", v);
                    Ray scatteredRay = Ray(hitSpot, addNoiseToVector(h.getNormal()));
                    if (_scene.getGroup()->intersect(scatteredRay, epsilon, lightHit)) {
                        if (lightHit.getMaterial()->isLight) {
                            LuminousMaterial *lumMaterial = (LuminousMaterial *) lightHit.getMaterial();
                            lumMaterial->getIllumination(p, toLight, intensity, distToLight);
                            totalLight += lumMaterial->shade(scatteredRay, lightHit, toLight, intensity);
                        }
                    }
                }
                color += totalLight / numScatteredVectors;
            }
        }
        
        for (int i = 0; i < _scene.getNumLights(); i++) {
            light = _scene.getLight(i);
            light->getIllumination(p, toLight, intensity, distToLight);
            //check shadowing
            if (_args.shadows) {
                Ray rayToLight = Ray(r.pointAtParameter(h.getT()), toLight);
                shadowHit = Hit();
                bool hitObj = _scene.getGroup()->intersect(rayToLight, epsilon, shadowHit);
                if (!(hitObj) || shadowHit.getT() > distToLight) {
                    color += h.getMaterial()->shade(r, h, toLight, intensity);
                }
            } else {
                
                color += h.getMaterial()->shade(r, h, toLight, intensity);
            }
        }
        //recursive ray tracing
        if (bounces > 0) {
            //if (h.getMaterial()->getSpecularColor().abs() == 0) return color; //no point in tracing the recursive ray
            
            Vector3f newOrigin = p;
            if (h.getMaterial()->getRefractionIndex() > 0) {
                //handle refraction rays
                refractionHit = Hit();
                Ray refractedRay = r.refract(h.getNormal(),
                                             r.isInsideObject ? h.getMaterial()->getRefractionIndex() : 1.0,
                                             r.isInsideObject ? 1.0 : h.getMaterial()->getRefractionIndex(),
                                             newOrigin);
                color += h.getMaterial()->getSpecularColor() * traceRay(refractedRay, epsilon, bounces-1, h);
            } else if (h.getMaterial()->isLight) {
                color += h.getMaterial()->getSpecularColor();
            } else {
                Hit reflectionHit = Hit();
                Vector3f newDirection = r.getDirection() - 2 * Vector3f::dot(r.getDirection(), h.getNormal()) * h.getNormal();
                Ray recursiveRay = Ray(newOrigin, newDirection.normalized());
                color += h.getMaterial()->getSpecularColor() * traceRay(recursiveRay, epsilon, bounces-1, reflectionHit);

            }
        }
        return color;
    } else {
        return _scene.getBackgroundColor(r.getDirection());
    };
}

