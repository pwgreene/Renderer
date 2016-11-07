#include "kdTree.h"
#include <math.h>

int main(int argc, char **argv)
{
    Vector3f root = Vector3f(-1, 0, 0);
    kdTree3D tree(root, 0, true);
    
    Vector3f point;
    int dim = 100;
    int neg;
    
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            for (int k= 0; k < dim; k++) {
                neg = pow(-1, i % 2);
                point = Vector3f(neg*i,j,k);
                tree.add(point);
            }
        }
    }
    
    //tree.print(&tree, 0);
    printf("done creating %d\n", dim*dim*dim);
    
    Vector3f target = Vector3f(50, 43, 10);
    sway::bounded_priority_queue<Vector3f, std::vector<Vector3f>, cmp> bpq(3, cmp(target));
    tree.kNearest(target, bpq, 5);
    while (!bpq.empty()) {
        bpq.top().print();
        bpq.pop_top();
    }
}
