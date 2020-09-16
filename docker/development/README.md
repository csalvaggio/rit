# INTRODUCTION #
This directory contains the files required to build and run a Docker container to support compilation and execution of code in this repository using Docker installed on any Linux distribution; Fedora, Red Hat, Ubuntu, Mac OS X, Windows Subsystem for Linux (WSL 2).

# BUILDING #
The ``Dockerfile`` describes the configuration of the Fedora system for this container. To build the container, at the Linux prompt type

    ./build.nix.sh

This process only needs to be carried out once per installation.

# RUNNING #
Once created, you may instantiate the container by executing the command

    ./run.nix.sh

Upon instantiation, you will be placed in the directory ``/home/developer``.  The directory ``src`` in this location contains this repository.  The first time you run this container, create your ``build`` directory

    cd src
    mkdir build

and build the repository

    cd build
    cmake ..
    ninja

At this point, you are free to modify any files in this repository within the Fedora container using traditional Linux tools **OR** in your host computer's native Linux environment; Mac OS X, Ubuntu Terminal under Windows Subsystem for Linux (WSL 2), Ubuntu, Fedora, or Red Hat. 

# REQUIREMENTS #
* Docker Desktop for Mac OS X and Windows machines 
* Docker Engine for Linux
* X11 server for host operating system
