#include "Vector3f.h"
#include "vector"
#include "bounded_priority_queue.hpp"

struct Photon {
    Vector3f position;
    Vector3f direction;
    Vector3f color;
};

class cmp {
    Vector3f _point;
public:
    cmp(Vector3f point) : _point(point) {}
    bool operator()(Photon a, Photon b) {
        return (a.position-_point).absSquared() < (b.position-_point).absSquared();
    }
};

class kdTree3D {
public:
    int size;
    kdTree3D(struct Photon root, int depth=0, bool isEmpty=false) {
        _rootpoint = root;
        _depth = depth;
        _isEmpty = isEmpty;
        _leftChild = NULL;
        _rightChild = NULL;
        size = 0;
    }
    
    void add(Photon point);
    
    //modifies nearest as output. nearest should be initialized with size limit k
    void kNearest(Vector3f point, sway::bounded_priority_queue<Photon, std::vector<Photon>, cmp> &nearest,
                  float &max_distance);
    
    static Vector3f colorAverage(sway::bounded_priority_queue<Photon, std::vector<Photon>, cmp> &nearest);
    
    bool getIsEmpty() {
        return _isEmpty;
    }
    
    void print(kdTree3D *p, int indent);
    
private:
    struct Photon _rootpoint;
    kdTree3D *_leftChild;
    kdTree3D *_rightChild;
    int _depth;
    bool _isEmpty;
};