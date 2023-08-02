# Lawrencium Learning Ground
Repository used to track some experiments with build systems, C++ and CUDA.
## Development Environment (Windows)
* Install WSL with the `Ubuntu 20.04` distribution.
  * Why this version ? At the time of writing this, LLVM does not support CUDA 12, we have to install CUDA 11.something, which cannot be installed in `Ubuntu 22.04`.
  * Note that this could be fixed with a trully hermetic build. But currently LLVM and CUDA have to be pre-installed (AFAIK).
* Install LLVM 15 using the [Automatic Installation Script](https://apt.llvm.org/).
* Follow [those instructions](https://developer.nvidia.com/cuda-11-5-2-download-archive?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=20.04&target_type=deb_local). See above as to why we can't use newer version.
* Run `install_bazel.sh` to install Bazel
* Set CUDA_PATH to the location of your CUDA installation. This variable is used by `rules_cuda`.
* You also need to install CUDNN by following this guide : https://docs.nvidia.com/deeplearning/cudnn/install-guide/index.html
  * Another hermeticity breach...
* Update gcc:
```
sudo apt update && sudo apt upgrade
sudo apt install gcc
```
* Build and / or run the tests to verify that everything is set up correctly:
```
bazel build --config=clang //tests:lawrencium_tests
bazel test --config=clang --test_output=all //tests:lawrencium_tests
```
## Installing LLVM and clang from source
### First you need to install cmake
* `sudo apt remove --purge --auto-remove cmake`
* `sudo apt update && sudo apt install -y software-properties-common lsb-release && sudo apt clean all`
* `wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null`
* `sudo apt-add-repository "deb https://apt.kitware.com/ubuntu/ $(lsb_release -cs) main"`
### And Ninja
* `sudo wget -qO /usr/local/bin/ninja.gz https://github.com/ninja-build/ninja/releases/latest/download/ninja-linux.zip`
* `sudo gunzip /usr/local/bin/ninja.gz`
* `sudo chmod a+x /usr/local/bin/ninja`
### LLVM and Clang themselves
* `git clone https://github.com/llvm/llvm-project.git`
* `cd llvm-project`
* `cmake -S llvm -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS='clang;libc;clang-tools-extra'  -DCMAKE_INSTALL_PREFIX=/usr/local/llvm`
* `ninja -C /llvm-from-source/llvm-project/build install`

## Installing GCC from source (Not require, but saving the steps here in case)
If this works, thanks to [this guy](https://iamsorush.com/posts/build-gcc11/): 
* Create some folder as a workspace, say /gcc-install
* Move to that folder
* Run wget `https://github.com/gcc-mirror/gcc/archive/refs/tags/releases/gcc-13.2.0.tar.gz`
* Extract the thing: `tar -xvf gcc-13.2.0.tar.gz`
* Navigate to the folder: `gcc-releases-gcc-13.2.0`
* Run the provided script which downloads and installs prerequisites: `contrib/download_prerequisites`
* Some guy says some other dependencies might be missing. Run this just to be sure:
  * `sudo apt install bzip2 flex`
* Create a build directory outside this:
```
/gcc-install
mkdir build
```
* Run whatever this is: `../gcc-releases-gcc-13.2.0/configure -v --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=/usr/local/gcc-13.2.0 --enable-checking=release --enable-languages=c,c++,fortran --disable-multilib --program-suffix=-13.2`
* Build it: `make -j 16`
* Install it: `sudo make install-strip`
* Do some more magic:
```
export PATH=/usr/local/gcc-13.2.0/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/gcc-13.2.0/lib64:$LD_LIBRARY_PATH

# To let CMake know
export CC=/usr/local/gcc-13.2.0/bin/gcc-13.2
export CXX=/usr/local/gcc-13.2.0/bin/g++-13.2
export FC=/usr/local/gcc-13.2.0/bin/gfortran-13.2
```

## Set Up From Clean Ubuntu 22.04 Installation
### Installing the stuff we need to install CMake from source
* `sudo apt update && sudo apt upgrade`
* `sudo apt install build-essential`
* `sudo apt-get update`
* `sudo apt-get install libssl-dev`
### Installing CMake from source
* `mkdir cmake-install`
* `cd cmake-install/`
* `wget https://github.com/Kitware/CMake/releases/download/v3.27.1/cmake-3.27.1.tar.gz`
* `tar -xvf cmake-3.27.1.tar.gz`
* `cd cmake-3.27.1`
* `./bootstrap -- -DCMAKE_BUILD_TYPE:STRING=Release`
* `make`
* `make install`
* `cd / && rm -rf cmake-install`
### Installing the stuff we need to install LLVM
* `mkdir llvm-install`
* `cd llvm-install`
* `sudo wget -qO /usr/local/bin/ninja.gz https://github.com/ninja-build/ninja/releases/latest/download/ninja-linux.zip`
* `sudo gunzip /usr/local/bin/ninja.gz`
* `sudo chmod a+x /usr/local/bin/ninja`
* `sudo apt-get install software-properties-common`
* `sudo add-apt-repository ppa:deadsnakes/ppa`
* `sudo apt-get update`
* `sudo apt-get install swig libedit-dev libncurses5-dev libncursesw5-dev liblzma-dev python3.8 libxml2-dev`
* Follow [those instructions](https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&Distribution=WSL-Ubuntu&target_version=2.0&target_type=deb_local) to install CUDA.
### Installing LLVM
* `git clone https://github.com/llvm/llvm-project.git`
* `cd llvm-project`
* Check out a version that is compatible with CUDA, e.g. `15.0.7`: `git checkout 8dfdcc7`
* `cmake -S llvm -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS='clang;clang-tools-extra;cross-project-tests;libclc;lld;lldb;openmp;polly;pstl' -DCMAKE_INSTALL_PREFIX=/usr/local/llvm`
* `ninja -j 4 -C /llvm-install/llvm-project/build install`