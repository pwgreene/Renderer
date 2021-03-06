#ifndef SCENE_PARSER_H
#define SCENE_PARSER_H

#include <cassert>
#include <vector>
#include <vecmath.h>

#include "SceneParser.h"
#include "Camera.h"
#include "CubeMap.h"
#include "Light.h"
#include "Material.h"
#include "Object3D.h"
#include "Mesh.h"

#define MAX_PARSER_TOKEN_LENGTH 100

class SceneParser
{
  public:
    SceneParser(const std::string &filename);
    ~SceneParser();

    Camera * getCamera() const {
        return _camera;
    }

    Vector3f getBackgroundColor(const Vector3f &dir) const {
        if (_cubemap) {
            return _cubemap->getTexel(dir);
        } else {
            return _background_color;
        }
    }

    const Vector3f & getAmbientLight() const {
        return _ambient_light;
    }

    int getNumLights() const {
        return _num_lights;
    }

    Light * getLight(int i) const {
        assert(i >= 0 && i < _num_lights);
        return lights[i];
    }

    int getNumMaterials() const {
        return _num_materials;
    }

    Material * getMaterial(int i) const {
        assert(i >= 0 && i < _num_materials);
        return _materials[i];
    }

    Group * getGroup() const {
        return _group;
    }

   std::vector<Light*> lights;
   std::vector<LuminousMaterial*> areaLights;
  private:
    void parseFile();
    void parsePerspectiveCamera();
    void parseBackground();
    void parseLights();
    Light * parseDirectionalLight();
    Light * parsePointLight();
    Light * parseSpotLight();
    Light * parseQuadLight();
    void parseMaterials();
    Material * parseMaterial();
    LuminousMaterial * parseLuminousMaterial();
    PhotonMaterial * parsePhotonMaterial();
    MultiColoredMaterial * parseMultiColoredMaterial();
    ToonMaterial * parseToonMaterial();

    Object3D * parseObject(char token[MAX_PARSER_TOKEN_LENGTH]);
    Group * parseGroup();
    Sphere * parseSphere();
    Plane * parsePlane();
    Rectangle * parseRectangle();
    Triangle * parseTriangle();
    Mesh * parseTriangleMesh();
    Transform * parseTransform();
    CubeMap * parseCubeMap();

    int getToken(char token[MAX_PARSER_TOKEN_LENGTH]);
    Vector3f readVector3f();
    Vector2f readVec2f();
    float readFloat();
    int readInt();

    std::string _basepath;
    FILE * _file;
    Camera * _camera;
    Vector3f _background_color;
    Vector3f _ambient_light;
    int _num_lights;
    int _num_materials;
    std::vector<Material*> _materials;
    std::vector<Object3D*> _objects;
    Material * _current_material;
    Group * _group;
    CubeMap * _cubemap;
};

#endif // SCENE_PARSER_H
