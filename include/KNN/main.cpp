#include "kdTree.h"
#include <math.h>

int main(int argc, char **argv)
{
    Vector3f rootpos = Vector3f(-1, 0, 0);
    Photon rootpoint;
    kdTree3D tree(rootpoint, 0, true);
    
    Vector3f point;
    Photon Photon;
    int dim = 2;
    int neg;
    
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            for (int k= 0; k < dim; k++) {
                neg = pow(-1, i % 2);
                point = Vector3f(neg*i,j,k);
                Photon.position = point;
                tree.add(Photon);
            }
        }
    }
    
    //tree.print(&tree, 0);
    printf("done creating %d\n", dim*dim*dim);
    
    Vector3f target = Vector3f(50, 43, 10);
    sway::bounded_priority_queue<struct Photon, std::vector<struct Photon>, cmp> bpq(3, cmp(target));
    float maxDistance = 0.1;
    tree.kNearest(target, bpq, maxDistance);
    while (!bpq.empty()) {
        bpq.top().position.print();
        bpq.pop_top();
    }
}
