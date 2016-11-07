#include "Vector3f.h"
#include "vector"
#include "bounded_priority_queue.hpp"

class cmp {
    Vector3f _point;
public:
    cmp(Vector3f point) : _point(point) {}
    bool operator()(Vector3f a, Vector3f b) {
        return (a-_point).abs() < (b-_point).abs();
    }
};

class kdTree3D {
public:
    
    kdTree3D(Vector3f root, int depth=0, bool isEmpty=false) {
        _rootpoint = root;
        _depth = depth;
        _isEmpty = isEmpty;
        _leftChild = NULL;
        _rightChild = NULL;
    }
    
    void add(Vector3f point);
    
    //modifies nearest as output. nearest should be initialized with size limit k
    void kNearest(Vector3f point, sway::bounded_priority_queue<Vector3f, std::vector<Vector3f>, cmp> &nearest,
                  float max_distance);
    
    bool getIsEmpty() {
        return _isEmpty;
    }
    
    void print(kdTree3D *p, int indent);
    
private:
    Vector3f _rootpoint;
    kdTree3D *_leftChild;
    kdTree3D *_rightChild;
    int _depth;
    bool _isEmpty;
};