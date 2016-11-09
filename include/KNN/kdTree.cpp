#include "kdTree.h"
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
kdTree3D::kNearest(Vector3f point, sway::bounded_priority_queue<Photon, std::vector<Photon>, cmp> &nearest, float &max_distance)
{
    if (_isEmpty) {
        return;
    }
    int i_partition = _depth % 3;
    float distToSplitPlane = point[i_partition] - _rootpoint.position[i_partition];
    if (distToSplitPlane < 0) {
        //on left of splitting plane
        if (_leftChild != NULL)
            _leftChild->kNearest(point, nearest, max_distance);
        if ((_rightChild != NULL) && (distToSplitPlane < max_distance)) {
            _rightChild->kNearest(point, nearest, max_distance);
        }
    } else {
        if (_rightChild != NULL)
            _rightChild->kNearest(point, nearest, max_distance);
        if ((_leftChild != NULL) && (distToSplitPlane < max_distance)) {
            _leftChild->kNearest(point, nearest, max_distance);
        }
    }
    
    float distToPhoton = (point - _rootpoint.position).abs();
    if (distToPhoton < max_distance) {
        nearest.push(_rootpoint);
        max_distance = distToPhoton;
    }
//    if ((point[i_partition] < _rootpoint.position[i_partition]) && (_leftChild != NULL)) {
//        wentLeft = true;
//        _leftChild->kNearest(point, nearest, max_distance);
//    } else if (_rightChild != NULL)
//        _rightChild->kNearest(point, nearest, max_distance);
//    else {
//        if ((point-_rootpoint.position).absSquared() < max_distance*max_distance)
//            nearest.push(_rootpoint);
//    }
    
//    if ((point-_rootpoint.position).absSquared() < (nearest.bottom().position-_rootpoint.position).absSquared()) {
//        //recursively search the other subtree on the next axis
//        if (wentLeft && _rightChild != NULL)
//            _rightChild->kNearest(point, nearest, max_distance);
//        else if (_leftChild != NULL)
//            _leftChild->kNearest(point, nearest, max_distance);
//    }
}

Vector3f kdTree3D::colorAverage(sway::bounded_priority_queue<Photon, std::vector<Photon>, cmp> &bpq) {
    Vector3f totalColor(0, 0, 0);
    int numPhotons = 0;
    while (!bpq.empty()) {
        totalColor += bpq.top().color;
        bpq.pop_top();
        numPhotons++;
    }
    return totalColor/numPhotons;
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

