# Structure from Motion
An easy understandle Structure from Motion (SfM) application wirrten in C++ using OpenCV, Qt and OpenGL. 

The goal of this application was mainly educational (Bachelor Thesis by nordewal/flec). It gives one a good insight and starting point into the Structure from Motion domain. Using the GUI one can easily follow the pipeline used for SfM:

1. Detect and describe features of each image
2. Create image pair and match features
3. Compute rotation and translation (extrinsic parameters) for the first image pair
4. Create a point cloud for the first image pair.
5. Add more points to the point cloud using PnP and triangulation.
6. Minimize the errors in the point cloud using bundle adjustment.

This application can only handle images that are already in the correct sequence (eg. video), as it only compares image A to B and image B to C. But not image A to C. The application can load images as well as videos.

The main logic is in `sfmapp.h` and `sfmapp.cpp`. One can easily interchange feature detectors and so on in the `sfmapp.h` file.

## Installation
### CUDA
**OPTIONAL**: One can offload feature detection to the graphic card. Thus enable the USE_CUDA CMake option and compile OpenCV with 
 CUDA.
### Linux
1. Build OpenCV with the contrib modules and install it. Make after cloning the git repos (opencv & opencv_contrib) that you checkout the same version of both repos:
```bash
git clone https://github.com/Itseez/opencv_contrib.git
cd opencv_contrib
git checkout 3.0.0
cd ..
git clone https://github.com/Itseez/opencv.git
cd opencv
git checkout 3.0.0
mkdir build
cd build
cmake -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules ..
```

2. Install the following dependencies:
   * libsuitesparse-dev
   * Qt (working for us: 5.5.0)
   * libqglviewer-dev (working for us: 2.6.3+dfsg1-1)

3. Compile the code: 
```bash
mkdir build
cd build
cmake ..
make
```

## Usage
### Datasets
For sake of comfort, two datasets are already provided in the datasets folder:
* house: Created for this project
* fountain: Created by the EPFL: http://cvlabwww.epfl.ch/data/multiview/denseMVS.html
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

### Camera distorsion parameters
For automatically rectifying the images before they are being processed, one can provide the distorsion parameters of the camera. Thus the file `camera_distortion.yaml` must be in the same folder as the images. Replace the number of columns (size of parameters; either 4, 5 or 8), and the data array accordingly:
```yaml
%YAML:1.0
mat1: !!opencv-matrix
   rows: 1
   cols: 8 # number parameters
   dt: d
   data: [k1, k2, p1, p2, k3, k4, k5, k6] # Values of the parameters
```
