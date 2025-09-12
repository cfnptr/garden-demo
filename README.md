# Garden Demo

This is a demonstration project for the [Garden](https://github.com/cfnptr/garden) game engine. You can 
use the provided [CMakeLists.txt](/CMakeLists.txt) to create your own project based on this demo.

## Supported operating systems

* Windows (10/11)
* Ubuntu (22.04/24.04)
* macOS (14/15)

This list includes only those systems on which functionality testing is conducted.
However, you can also compile it under any other Linux distribution or operating system.

## Supported hardware

### Graphics processing unit (GPU)

* Nvidia [Kepler](https://en.wikipedia.org/wiki/Kepler_(microarchitecture)) microarchitecture and newer
* AMD [GCN](https://en.wikipedia.org/wiki/Graphics_Core_Next) microarchitecture and newer
* Intel [Gen9](https://en.wikichip.org/wiki/intel/microarchitectures/gen9) microarchitecture and newer
* Apple [M1](https://en.wikipedia.org/wiki/Apple_M1) integrated GPU and newer (partial support)

At least GPU with Vulkan API 1.1 support.

### Central processing unit (CPU)

* Intel [Haswell](https://en.wikipedia.org/wiki/Haswell_(microarchitecture)) microarchitecture and newer
* AMD [Excavator](https://en.wikipedia.org/wiki/Excavator_(microarchitecture)) microarchitecture and newer
* Apple [M1](https://en.wikipedia.org/wiki/Apple_M1) processor and newer

These requirements are based on the support of the [AVX2](https://en.wikipedia.org/wiki/Advanced_Vector_Extensions) instruction set in the x86 architecture.
If you want, you can freely disable it and compile for any other architecture, including **ARM**.

## Build demo app ![CI](https://github.com/cfnptr/garden-demo/actions/workflows/cmake.yml/badge.svg)

1. Follow Garden building [instructions](https://github.com/cfnptr/garden/blob/main/BUILDING.md)
4. Run ```git clone --progress --recursive https://github.com/cfnptr/garden-demo``` using **Terminal**
5. Open garden-demo directory using **IDE** or use build [scripts](scripts/) script

Make sure to install "C++ Clang tools for Windows" for Visual Studio! (Windows only)

## Garden Shading Language (GSL)

Documentation with all GLSL changes is [here](https://github.com/cfnptr/garden/blob/main/docs/GSL.md).
You can install **Visual Studio Code** [extension](https://marketplace.visualstudio.com/items?itemName=cfnptr.gsl-linter) to highlight GSL syntax.

## Third-party

* [Garden](https://github.com/cfnptr/garden) (Apache-2.0 license)
* [Prototype Bits](https://github.com/KayKit-Game-Assets/KayKit-Prototype-Bits-1.0) (CC0 license)
