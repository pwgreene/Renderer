#include "kdTree.h"
#include <iostream>
#include <iomanip>

void kdTree3D::add(Vector3f point) {
    if (_isEmpty) {
        _rootpoint = point;
        _isEmpty = false;
        return;
    }
    int i_partition = _depth % 3;
    if (point[i_partition] < _rootpoint[i_partition]) {
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
}

void kdTree3D::kNearest(Vector3f point, sway::bounded_priority_queue<Vector3f, std::vector<Vector3f>, cmp> &nearest,
                        float max_distance)
{
    
    if (_isEmpty) {
        return;
    }
    nearest.push(_rootpoint);
    int i_partition = _depth % 3;
    bool wentLeft = false;
    if ((point[i_partition] < _rootpoint[i_partition]) && (_leftChild != NULL)) {
        wentLeft = true;
        _leftChild->kNearest(point, nearest, max_distance);
    } else if (_rightChild != NULL)
        _rightChild->kNearest(point, nearest, max_distance);
    
    if ((nearest.size() < nearest.max_size()) ||
        ((point-_rootpoint).abs() < (nearest.bottom()-_rootpoint).abs())) {
        //recursively search the other subtree on the next axis
        if (wentLeft && _rightChild != NULL)
            _rightChild->kNearest(point, nearest, max_distance);
        else if (_leftChild != NULL)
            _leftChild->kNearest(point, nearest, max_distance);
    }
        
    
}

void kdTree3D::print(kdTree3D *p, int indent=0) {
    /**
    if(p != NULL) {
        p->_rootpoint.print();
        if(p->_leftChild) print(p->_leftChild, indent+4);
        if(p->_rightChild) print(p->_rightChild, indent+4);
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
    }
     **/
    {
        if(p != NULL) {
            if(p->_rightChild) {
                print(p->_rightChild, indent+4);
            }
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            if (p->_rightChild) std::cout<<" /\n" << std::setw(indent) << ' ';
            //std::cout<< p->key_value << "\n ";
            p->_rootpoint.print();
            if(p->_leftChild) {
                std::cout << std::setw(indent) << ' ' <<" \\\n";
                print(p->_leftChild, indent+4);
            }
        }
    }
}

