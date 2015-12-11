# Structure from Motion

The main logic is in `sfmapp.h` and `sfmapp.cpp`. One can easily interchange feature detectors and so on in the `sfmapp.h` file.

## Installation
### CUDA
One can offload feature detection to the graphic card. Thus enable the USE_CUDA CMake option and compile OpenCV with 
 CUDA.
### Linux
1. Build OpenCV with the contrib modules and install it:
   <https://github.com/itseez/opencv_contrib#how-to-build-opencv-with-extra-modules>

2. Install the following dependencies:
   * libsuitesparse-dev
   * Qt (working for us: 5.5.0)
   * libqglviewer-dev (working for us: 2.6.3+dfsg1-1)

3. Compile it: 
```bash
mkdir build
cd build
cmake ..
```

## Usage
### Datasets
For sake of comfort, two sample datasets are already provided in the datasets folder.
### Camera intrinsic parameters
To avoid specifying the camera intrinsic parameters on every run in the GUI, one can define those in a file called 
`camera_intrinsic.yaml`, which must be in the same folder as the images. Replace `fx`, `fy`, `cx` and `cy` accordingly.
```yaml
%YAML:1.0
mat1: !!opencv-matrix
   rows: 3
   cols: 3
   dt: d
   data: [fx, 0,  cx, 
          0,  fy, cy,
          0,  0,  1 ] 
```