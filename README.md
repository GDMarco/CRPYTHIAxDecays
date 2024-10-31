# CRPYTHIAxDecays
CRPropa code plugin that performs particle decays through Pythia code. At the current stage only the decays of muons and charged pions are implemented. The plan is to extend this plugin to the decay of other particles.  

## Structure
The header of the `Decays` class is defined in `Decays.h`. The C++ file `Decays.cc` contains the decay class functions and a class to produce the decay's secondaries in Pythia code. The file `Decays.i` is the SWIG interface for python usage. 

The CMake installation file `CMakeList.txt` includes the coordinates to the Pythia library and include files. The installation can be tested through the script `testPlugin.py`. 

# Installation
For the installation of the CRPYTHIAzDecays plugin you need a running version of CRPropa (see [CRPropa installation documentation](https://crpropa.github.io/CRPropa3/pages/Installation.html)) and Pythia ([Pythia installation documentation](https://pythia.org/)).

First create a build folder within the plugin's directory and move there.

    mkdir build && cd build/

Now you can run cmake to configure your project:

    ccmake ..

At this step you have to set the installation path and the path to your swig interface of the current CRPropa installation and/or of the Pythia library and include directories (if it is not found by cmake).

After configuration (press c) and generation (press g) you can now build and install your plugin

    make install
    
Now you can run the python test script. 

    python ../testPlugin.py
