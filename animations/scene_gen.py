#!/usr/bin/env python
import sys

targetdir = sys.argv[1]

def rotate():

    for deg in range(360):
        text = \
"""
    
   

PerspectiveCamera {
center 15 5 -23
direction -1.2 -.5 1.5
up 0 1 0
angle 30
}

Lights {
numLights 1
SpotLight {
position 0 1 7
direction 0 -.1 -.7
color 1 1 1
power 75
falloffAngle 180
hotspotAngle 20
falloffDegree 1
}
}

Background {
color 0 0 0
ambientLight 0.04 .04 .05
}

Materials {
numMaterials 3
PhotonMaterial {
color 1 1 1
p_refract 1
refractionIndex 1.5
diffracting
}
PhotonMaterial {
color .8 .8 1
p_absorb 1.0
}
PhotonMaterial {
color .8 .1 .1
p_absorb 1.0
}
}

Group {
numObjects 2
MaterialIndex 0
Transform {
Translate  0 0.01 0
Scale  1 2 1
YRotate """+str(deg)+"""
TriangleMesh {
obj_file models/cube.obj
}
}
MaterialIndex 1
Plane {
normal 0 1 0
offset -2
}

}





"""

        with open('%s/scene%s.txt' % (targetdir, deg), 'w') as f:
            f.write(text)
 

if __name__ == "__main__":
    rotate()
