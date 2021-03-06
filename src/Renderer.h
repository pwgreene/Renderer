#ifndef RENDERER_H
#define RENDERER_H

#include <string>

#include "SceneParser.h"
#include "ArgParser.h"
#include "kdTree.h"
#include <random>

class Hit;
class Vector3f;
class Ray;

class Renderer
{
  public:
    // Instantiates a renderer for the given scene.
    Renderer(const ArgParser &args);
    Vector3f addNoiseToVector(Vector3f v);
    void Render();
  private:
    Vector3f traceRay(Ray &ray, float tmin, int bounces, 
                      Hit &hit);
    Vector3f traceEyeRay(Ray &ray, float tmin, int bounces,
                      Hit &hit);
    void mapPhotons(int nPhotons);
    int sendPhoton(Ray r, struct Photon &p);

    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
    kdTree3D *photonMap;
    kdTree3D *indirectPhotonMap;
    kdTree3D *causticMap;
    kdTree3D *shadowMap;
    int totalPhotons;
    ArgParser _args;
    SceneParser _scene;
    
};

#endif // RENDERER_H
