#include "kdTree.h"
#include "math.h"
#include <iostream>
#include <iomanip>
#include <cmath>

void kdTree3D::add(Photon point) {
    if (_isEmpty) {
        _rootpoint = point;
        _isEmpty = false;
        size++;
        return;
    }
    int i_partition = _depth % 3;
    if (point.position[i_partition] < _rootpoint.position[i_partition]) {
        if (_leftChild == NULL)
            _leftChild = new kdTree3D(point, _depth+1);
        else
            _leftChild->add(point);
    } else {
        if (_rightChild == NULL)
            _rightChild = new kdTree3D(point, _depth+1);
        else
            _rightChild->add(point);
    }
    size++;
}

void
kdTree3D::kNearest(Vector3f point, sway::bounded_priority_queue<Photon, std::vector<Photon>, cmp> &nearest, float &maxDistanceSq)
{
    if (_isEmpty) {
        return;
    }
    int i_partition = _depth % 3;
    float distToSplitPlane = point[i_partition] - _rootpoint.position[i_partition];
    if (distToSplitPlane < 0) {
        //on left of splitting plane
        if (_leftChild != NULL)
            _leftChild->kNearest(point, nearest, maxDistanceSq);
        if ((_rightChild != NULL) && (distToSplitPlane*distToSplitPlane < maxDistanceSq)) {
            _rightChild->kNearest(point, nearest, maxDistanceSq);
        }
    } else {
        if (_rightChild != NULL)
            _rightChild->kNearest(point, nearest, maxDistanceSq);
        if ((_leftChild != NULL) && (distToSplitPlane*distToSplitPlane < maxDistanceSq)) {
            _leftChild->kNearest(point, nearest, maxDistanceSq);
        }
    }
    
    float distToPhotonSq = (point - _rootpoint.position).absSquared();
    if (distToPhotonSq < maxDistanceSq) {
        nearest.push(_rootpoint);
        //maxDistanceSq = (nearest.top().position - point).absSquared();
    }
}

Vector3f kdTree3D::gatherAndFilter(Vector3f point, sway::bounded_priority_queue<Photon, std::vector<Photon>, cmp> &bpq, float dSq, float k, bool isCaustic) {
    Vector3f totalColor(0, 0, 0);
    float distance;
    int numPhotons = 0;
    while (!bpq.empty()) {
        distance = (point - bpq.top().position).abs();
        if (isCaustic)
            totalColor += (1 - distance/(k*sqrt(dSq)))*bpq.top().color; //filter, for caustics only
        else
            totalColor += bpq.top().color;
        bpq.pop_top();
        numPhotons++;
    }
    if (isCaustic)
        return totalColor/((1-2/(3*k))*M_PI*dSq);
    else
        return totalColor;
}

void kdTree3D::print(kdTree3D *p, int indent=0) {
    if(p != NULL) {
        if(p->_rightChild) {
            print(p->_rightChild, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->_rightChild) std::cout<<" /\n" << std::setw(indent) << ' ';
        //std::cout<< p->key_value << "\n ";
        p->_rootpoint.position.print();
        p->_rootpoint.color.print();
        if(p->_leftChild) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            print(p->_leftChild, indent+4);
        }
    }
}

