# INTRODUCTION #
This repository contains a collection of some useful imaging science routines.

# INSTALLATION #
Installation is carried out using the [Conan](https://conan.io) C/C++ package manager and the [CMake](https://cmake.org) build environment.

If the [Conan](https://conan.io) C/C++ package manager is not installed globally on your system, you can install it locally using the command

```
pip3 install conan
```

After this repository is cloned/installed, create a `build` directory in the same directory as the top-level `conanfile.py` and `CMakeLists.txt` files.

Change directory to this `build` directory and type

```
conan install --build missing ..
```

Configure your build environment by typing

```
cmake ..
```

Compile the repository by typing

```
ninja
```

If you are running under the *Linux* operating system and the above command fails, type

```
conan profile update settings.compiler.libcxx=libstdc++11 default
```

to be certain the industry-standard Application Binary Interface, or ABI, is utilized by ensuring the C++11 standard library is being used, and execute the ```conan install```, ```cmake```, and ```ninja``` commands again.

All binaries (executables) will be located within the `build/bin` directory.

# REQUIREMENTS #
* C++ compiler that supports C++17 dialect/ISO standard

# DEPENDENCIES #
* Boost
* Eigen3
* OpenCV 3

These three target link libraries may be referenced as `PUBLIC` or `PRIVATE` in any `CMakeLists.txt` file, respectively, as

    CONAN_PKG::boost
    CONAN_PKG::eigen
    CONAN_PKG::opencv

# TESTING #
The `imgs/apps` directory contains implementations and examples that will be compiled during the build process.
