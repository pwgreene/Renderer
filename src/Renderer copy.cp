#include "Renderer.h"

#include "ArgParser.h"
#include "Camera.h"
#include "Image.h"
#include "Ray.h"
#include "VecUtils.h"

#include <limits>
#include <random>

enum PhotonType {
    DIRECT,
    INDIRECT,
    CAUSTIC,
    SHADOW,
};


Renderer::Renderer(const ArgParser &args) :
    _args(args),
    _scene(args.input_file)
{
    gen = std::mt19937(rd());
    dis = std::uniform_int_distribution<>(-100, 100);
    struct Photon root;
    photonMap = new kdTree3D(root, 0, true);
    indirectPhotonMap = new kdTree3D(root, 0, true);
    causticMap = new kdTree3D(root, 0, true);
    shadowMap = new kdTree3D(root, 0, true);
    totalPhotons = 0;

}

Vector3f Renderer::addNoiseToVector(Vector3f v) {
    return Vector3f(v[0] + dis(gen)/500.f, v[1] + dis(gen)/500.f, v[2] + dis(gen)/500.f);
}

void
Renderer::Render()
{
    if (_args.photonmapping) {
        mapPhotons(_args.photonmapping);
    } else if (_args.stippling) {
        mapPhotons(_args.stippling);
    }
    
    int w = _args.width;
    int h = _args.height;
    
    for (int i = 0; i < _args.num_views; i++) {

        Image image(w, h);
        Image nimage(w, h);
        Image dimage(w, h);

        // loop through all the pixels in the image
        // generate all the samples

        // This look generates camera rays and callse traceRay.
        // It also write to the color, normal, and depth images.
        // You should understand what this code does.

        Vector3f color;
        Camera* cam = _scene.getCamera();
        //cam->rotateY(i);
        Vector3f gatherSpot;
        int nGatherPhotons = 1000;
        float maxDistanceCaustic = .15;
        float maxDistanceIndirect = .3;
        float dSq;
        float k = 1.2; //filter constant
        sway::bounded_priority_queue<struct Photon, std::vector<struct Photon>, cmp> bpq(nGatherPhotons, cmp(gatherSpot));
        for (int y = 0; y < h; ++y) {
            float ndcy = 2 * (y / (h - 1.0f)) - 1.0f;
            for (int x = 0; x < w; ++x) {
                float ndcx = 2 * (x / (w - 1.0f)) - 1.0f;
                // Use PerspectiveCamera to generate a ray.
                // You should understand what generateRay() does.
                Ray r = cam->generateRay(Vector2f(ndcx, ndcy));
                Hit h;
                color = Vector3f(0,0,0);
                if (_args.photonmapping) {
                    //_scene.getGroup()->intersect(r, 0.01, h);
                    gatherSpot = traceEyeRay(r, cam->getTMin(), _args.bounces, h);
                    dSq = maxDistanceCaustic*maxDistanceCaustic;
                    causticMap->kNearest(gatherSpot, bpq, dSq);
                    color += causticMap->gatherAndFilter(gatherSpot, bpq, dSq, k, true)/totalPhotons*.5; //clears bpq
    //                dSq = maxDistanceIndirect*maxDistanceIndirect;
    //                indirectPhotonMap->kNearest(gatherSpot, bpq, dSq);
    //                color += indirectPhotonMap->gatherAndFilter(gatherSpot, bpq, dSq, k, false)/totalPhotons;
                    h = Hit();
                    color += traceRay(r, cam->getTMin(), _args.bounces, h);
    //                photonMap->kNearest(gatherSpot, bpq, dSq);
    //                color += photonMap->gatherAndFilter(gatherSpot, bpq, dSq, k, false)/totalPhotons;
                } else if (_args.stippling) {
                    color = Vector3f(1,1,1);
                    float gatherDist = 0.015;
                    gatherSpot = traceEyeRay(r, cam->getTMin(), _args.bounces, h);
                    dSq = gatherDist*gatherDist;
                    shadowMap->kNearest(gatherSpot, bpq, dSq);
                    color += shadowMap->gatherAndFilter(gatherSpot, bpq, dSq, k, false);
                } else {
                    h = Hit();
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
            image.savePNG(_args.output_file.append(std::to_string(i)));
            printf(std::string("outputted image ").append(std::to_string(i)).append("\n").c_str());
        }
        if (_args.depth_file.size()) {
            dimage.savePNG(_args.depth_file);
        }
        if (_args.normals_file.size()) {
            nimage.savePNG(_args.normals_file);
        }
    }
}

void
Renderer::mapPhotons(int nPhotons)
{
    
    //TODO fill this in
    //monte carlo photon tracing for a nPhotons (100,000?) originating from the light source(s)
    int nDirectPhotonsMapped = 0, nCausticPhotonsMapped = 0, nIndirectPhotonsMapped = 0;
    while (nCausticPhotonsMapped < _args.nCausticWanted ){//|| nIndirectPhotonsMapped < _args.nIndirectWanted) {
        //printf("%d\n", nCausticPhotonsMapped);
        for (Light *light : _scene.lights) {
        //printf("%d\n", nPhotons);
            Vector3f origin = light->getRandomPosition();
            Vector3f direction = light->getRandomDirection();
            struct Photon photon;
            photon.start = origin;
            photon.color = light->getColor()*(light->power); //divide power evenly between all photons
            Ray photonRay(origin, direction);
            switch (sendPhoton(photonRay, photon)) {
                case DIRECT:
                    totalPhotons++;
                    nDirectPhotonsMapped++;
                    break;
                case INDIRECT:
                    totalPhotons++;
                    nIndirectPhotonsMapped++;
                    break;
                case CAUSTIC:
                    totalPhotons++;
                    nCausticPhotonsMapped++;
                    //printf("%d\n", nCausticPhotonsMapped);
                    break;
                default:
                    break;
            }
        }
    }
    printf("Photons Mapped: %d, %d, %d\n", nDirectPhotonsMapped, nIndirectPhotonsMapped, nCausticPhotonsMapped);
}

int
Renderer::sendPhoton(Ray r, struct Photon &p) {
    Hit h = Hit();
    Hit shadowHit;
    float epsilon = 0.01;
    float limit = 20;
    int numShadows;
    float t;
    if (_scene.getGroup()->intersect(r, epsilon, h)) {
        //add to shadow map
//        shadowHit = Hit();
//        t = h.getT()+epsilon;
//        while (_scene.getGroup()->intersect(r, t, shadowHit)) {
//            Photon shadowPhoton;
//            shadowPhoton.color = Vector3f(-.2, -.2, -.2);
//            shadowPhoton.position = r.pointAtParameter(shadowHit.getT());
//            shadowMap->add(shadowPhoton);
//            t = shadowHit.getT()+epsilon;
//            shadowHit = Hit();
//        }
        PhotonMaterial *m = h.getPhotonMaterial();
        float randVal = (float)rand()/(float)RAND_MAX;
        if (randVal < m->getPAbsorption()) {
            p.direction = r.getDirection();
            p.position = r.pointAtParameter(h.getT());
            p.color = p.color*m->getColor(p.position);
            if ((p.position - p.start).absSquared() > limit*limit) {
                return false;
            }
            if (p.hitDiffuse) {
                indirectPhotonMap->add(p);
                return INDIRECT;
            } else if (p.hitSpecular) {
                causticMap->add(p);
                return CAUSTIC;
            } else {
                //photonMap->add(p);
                return DIRECT;
            }
        } else if (randVal < m->getPAbsorption() + m->getPReflectionDiffuse()) {
            //Diffuse Reflection
            p.color = p.color*m->getColor(r.pointAtParameter(h.getT()));
            p.hitDiffuse = true;
            return sendPhoton(r.reflect(h.getNormal(), r.pointAtParameter(h.getT())), p);
        } else if (randVal < m->getPAbsorption() + m->getPReflectionDiffuse() + m->getPReflectionSpecular()) {
            //Specular reflection
            p.hitSpecular = true;
            p.color = p.color*m->getColor(r.pointAtParameter(h.getT()));
            return sendPhoton(r.reflect(h.getNormal(), r.pointAtParameter(h.getT())), p);
        } else {
            //transmit
            p.hitSpecular = true;
            float weight = m->getColor(r.pointAtParameter(h.getT())).abs() < 0.5 ? 2.0 : 1.0;
            p.color = weight*p.color*m->getColor(r.pointAtParameter(h.getT()));
            return sendPhoton(r.refract(h.getNormal(),
                                        r.isInsideObject ? m->getRefractionIndex() : 1.0,
                                        r.isInsideObject ? 1.0 : m->getRefractionIndex(),
                                        r.pointAtParameter(h.getT())), p);
        }
    }
    return -1;
}

Vector3f
Renderer::traceEyeRay(Ray &r,
                      float tmin,
                      int bounces,
                      Hit &h)
{
    if (_scene.getGroup()->intersect(r, tmin, h)) {
        Light *light;
        Vector3f toLight;
        Vector3f color = _scene.getAmbientLight() * h.getMaterial()->getDiffuseColor();
        Vector3f intensity;
        Hit shadowHit;
        Hit lightHit;
        Hit refractionHit;
        float epsilon = 0.01;
        float distToLight;
        //location of the hit
        Vector3f p = r.pointAtParameter(h.getT());
        PhotonMaterial *pMat = (PhotonMaterial*) h.getMaterial();
        if (bounces <= 0 || (pMat->getPReflectionSpecular() == 0 && pMat->getPTransmission() == 0))
            return p;
        
        Vector3f newOrigin = p;
        if (h.getMaterial()->getRefractionIndex() > 0) {
            //handle refraction rays
            refractionHit = Hit();
            Ray refractedRay = r.refract(h.getNormal(),
                                         r.isInsideObject ? h.getMaterial()->getRefractionIndex() : 1.0,
                                         r.isInsideObject ? 1.0 : h.getMaterial()->getRefractionIndex(),
                                         newOrigin);
            return traceEyeRay(refractedRay, epsilon, bounces-1, refractionHit);
        } else {
            Hit reflectionHit = Hit();
            Vector3f newDirection = r.getDirection() - 2 * Vector3f::dot(r.getDirection(), h.getNormal()) * h.getNormal();
            Ray recursiveRay = r.reflect(h.getNormal(), p);//Ray(newOrigin, newDirection.normalized());
            return traceEyeRay(recursiveRay, epsilon, bounces-1, reflectionHit);
        }
    } else {
        return Vector3f(0,0,0);
    }
}


Vector3f
Renderer::traceRay(Ray &r,
    float tmin,
    int bounces,
    Hit &h)
{
    if (_scene.getGroup()->intersect(r, tmin, h)) {
        //TODO check intersection with QuadLight
        Light *light;
        //location of the hit
        Vector3f p = r.pointAtParameter(h.getT());
        Vector3f toLight;
        Vector3f color = _scene.getAmbientLight() * h.getMaterial()->getDiffuseColor();
        //color.print();
        Vector3f intensity;
        Hit shadowHit;
        Hit lightHit;
        Hit refractionHit;
        int numScatteredVectors = 1;
        float epsilon = 0.01;
        float distToLight;
        if (_args.outline) {
            for (int i = 0; i < 5; i++) {
                Hit noiseHit = Hit();
                Ray noisyRay = Ray(r.getOrigin(), addNoiseToVector(r.getDirection()));
                _scene.getGroup()->intersect(noisyRay, 0.001, noiseHit);
                if ((noisyRay.pointAtParameter(noiseHit.getT()) - r.pointAtParameter(h.getT())).abs() > 1.0) {
                    //printf("outline\n");
                    return Vector3f(0,0,0);
                }
            }
        }
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
        //recursive ray tracing
        if (bounces > 0) {
            bool transmittingSurface = false;
            if (_args.photonmapping) {
                PhotonMaterial *pMat = (PhotonMaterial*) h.getMaterial();
                //no point in tracing the recursive ray
                if (pMat->getPReflectionSpecular() == 0 && pMat->getPTransmission() == 0) {
                    goto directlighting;
                }
            }
            Vector3f newOrigin = p;
            if (h.getMaterial()->getRefractionIndex() > 0) {
                //handle refraction rays
                refractionHit = Hit();
                Ray refractedRay = r.refract(h.getNormal(),
                                             r.isInsideObject ? h.getMaterial()->getRefractionIndex() : 1.0,
                                             r.isInsideObject ? 1.0 : h.getMaterial()->getRefractionIndex(),
                                             newOrigin);
                color += h.getMaterial()->getSpecularColor(p) * traceRay(refractedRay, epsilon, bounces-1, refractionHit);
                transmittingSurface = true;
            } else if (h.getMaterial()->isLight) {
                color += h.getMaterial()->getSpecularColor();
            } else {
            Hit reflectionHit = Hit();
            Vector3f newDirection = r.getDirection() - 2 * Vector3f::dot(r.getDirection(), h.getNormal()) * h.getNormal();
            Ray recursiveRay = r.reflect(h.getNormal(), p);//Ray(newOrigin, newDirection.normalized());
            if (_args.photonmapping) {
                float weight = transmittingSurface ? 0.1 : 1.0;
                color += weight*traceRay(recursiveRay, epsilon, bounces-1, reflectionHit);
            } else
                color += h.getMaterial()->getSpecularColor() * traceRay(recursiveRay, epsilon, bounces-1, reflectionHit);
            
        } else {
        directlighting:
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
        }
        return color;
    } else {
        return _scene.getBackgroundColor(r.getDirection());
    };
}

