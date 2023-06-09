# Face-Tracking-for-Creating-3D-Illusion
An interactive illusion of depth on a 2D screen by tracking the user's face position and adjusting the virtual viewing angle of the displayed object.

## Demos
![Demo](images/demo.gif)
![Demo (Left-Right)](images/demo-left-right.gif)
![Demo (Up-Down)](images/demo-up-down.gif)
![Demo (Forward-Backward)](images/demo-forward-backward.gif)

## Credits
This project is inspired by Servet Gulnaroglu's YouTube video:

[ASMR Programming - Spinning Cube - No Talking](https://youtu.be/p09i_hoFdd0)

## Dependencies

This project requires OpenCV version 4.7.0. Please ensure that you have this version installed on your system.

### Installation

#### macOS

To install OpenCV 4.7.0 on macOS, follow these steps:

1. Install Homebrew if you haven't already:

```
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

2. Update Homebrew:

```
brew update
```

3. Install OpenCV 4.7.0:

```
brew install opencv@4.7.0
```

4. Note that you might need to update the include path of your IDE to include
this new directory. For example, OpenCV was installed at `/opt/homebrew/Cellar/opencv/4.7.0_2/include/opencv4` on my MacBook (you can find this path by using the terminal command `locate opencv`).

---

#### Windows

For Windows users, you can download the pre-built binaries for OpenCV version 4.7.0 from the official OpenCV website or use package managers like vcpkg or conda to install the required version.

---

### Compile and Run the Application

To compile and run the application, follow these steps:

1. Clone the repository and navigate to the project directory:

```
git clone https://github.com/tonyfu97/Face-Tracking-for-Creating-3D-Illusion.git
cd Face-Tracking-for-Creating-3D-Illusion
```

2. Go to `src/main/FaceDetector.cpp`. Modify the two constants based on your system:

```
const int CAMERA_NUMBER = 1;  // replace with the number of the main camara if needed.
const std::string REPO_DIR = "/path/to/repository/Face-Tracking-for-Creating-3D-Illusion/";
```

3. Compile the project using the provided Makefile:

```
make
```

4. Run the application:

```
./bin/main
```

5. (Optional) Fine tune the rotation and size sensitivities (in `src/main/Viewer.cpp`) to maximize the illusion of depth.

```
// Rotation sensitivity: Larger sensitivity = cube more sensitive to head movement.
const float UP_DOWN_SENSITIVITY = 1 / 1200.0;
const float LEFT_RIGHT_SENSITIVITY = 1 / 6400.0;
// Size sensitivity: larger value = cube change size more dramatically
const float FORWARD_BACKWARD_SENSITIVITY = 1 / 5.0;
```
