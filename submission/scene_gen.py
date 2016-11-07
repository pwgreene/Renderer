#!/usr/bin/env python
import sys

targetdir = sys.argv[1]

def rotate():

    for deg in range(360):
        text = \
"""
    
    PerspectiveCamera {
    center 0 0 10
    direction 0 0 -1
    up 0 1 0
    angle 30
    }
    
    
    Lights {
    numLights 1
    DirectionalLight {
    direction -0.5 -0.3 -1
    color 0.9 0.9 0.9
    }
    }
    
    Background {
    color 0.2 0 0.6
    ambientLight 0.1 0.1 0.1
    cubeMap ../tex/church
    }
    
    Materials {
    numMaterials 1
    Material {
    specularColor 0.7 0.7 0.7
    shininess 30
    diffuseColor 0 0 0
    refractionIndex 1.2
    }
    }
    
    Group {
    numObjects 1
    MaterialIndex 0
    Transform {
    Translate  0.5 -2.6 0
    Scale  12 12 12
    YRotate """ + str(deg) + """
    TriangleMesh {
    obj_file ../bunny_1k.obj
    }
    }
    }

"""

        with open('%s/scene%s.txt' % (targetdir, deg), 'w') as f:
            f.write(text)
 

if __name__ == "__main__":
    rotate()
