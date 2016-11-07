* built with the standard CMake system

* No collaborators

* I didn't use any outside references

* There aren't any existing problems that I'm aware of

* Extra Credit

    - Transparent Surfaces: materials can be given refractionIndex as an argument (default 0). If it is greater than zero, then the material will appear transparent. Some samples of this can be viewed in the samples folder (transparent_sphere.png and transparent_bunny.png)

    - Spot Lights: I implemented a new SpotLight class (defined in Light.h) that takes in hotspotAngle, falloffAngle, and falloffDegree as inputs. A higher falloffDegree will cause the light ring to go from 1.0 to 0.0 faster. A falloffDegree of 1 is linear, 2 is quadratic, and so on (it can be arbitrarily large, as SpotLight::GetIllumination generalizes to any degree > 1). Samples of this can be seen in the sample folder

    - Area Lights and soft shadows: I implemented a new Material type, LuminousMaterial (defined in Light.h) that inherits from both the Material class and the Light class, as well as a new Object3D Rectangle. The area light has to be axis aligned, since it uses the 1D interval intersection technique that we talked about in regards to ray tracing acceleration. "Shadow Rays" are sampled randomly around the normal of each object and each of these rays checks for a collision with any of the area lights. The colors are then averaged to get the color of the pixel. The sample image samples/area_light1.png uses 1000 sample average at each point.

    - Animations: I wrote two scripts, scene_gen.py and image_gen.sh, that created the .txt scenes and .png images from those scenes, respectively. I then compiled the sets of images into a .mp4 file using ffmpeg. The animations each run at 24 fps for 15 secs.
