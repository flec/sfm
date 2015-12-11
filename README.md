# Structure from Motion

## Installation
## CUDA
One can offload feature detection to the graphic card. Thus enable the USE_CUDA CMake option and compile OpenCV with 
 CUDA.
### Linux
1. Build OpenCV with the contrib modules and install it:
⋅⋅⋅<https://github.com/itseez/opencv_contrib#how-to-build-opencv-with-extra-modules>

2. Install the following dependencies:
⋅⋅⋅* libsuitesparse-dev
⋅⋅⋅* Qt (working for us: 5.5.0)
⋅⋅⋅* libqglviewer-dev (working for us: 2.6.3+dfsg1-1)

3. ```bash
mkdir build
cd build
cmake ..
```