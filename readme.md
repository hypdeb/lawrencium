# Learning Sandbox
## Setting Up Environment
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
* Set `CUDA_PATH` to your CUDA installation path, e.g. `/usr/local/cuda-12.2`

### Installing GCC from source, to be able to build LLVM
If this works, thanks to [this guy](https://iamsorush.com/posts/build-gcc11/): 
* Create some folder as a workspace, say /gcc-install
* Move to that folder
* Run `wget https://github.com/gcc-mirror/gcc/archive/refs/tags/releases/gcc-12.2.0.tar.gz`
* Extract the thing: `tar -xvf gcc-12.2.0.tar.gz`
* Navigate to the folder: `cd gcc-releases-gcc-12.2.0`
* Run the provided script which downloads and installs prerequisites: `contrib/download_prerequisites`
* Some guy says some other dependencies might be missing. Run this just to be sure:
  * `sudo apt update && sudo apt install bzip2 flex`
* Create a build directory outside this:
```
/gcc-install
mkdir build
```
* Run whatever this is: `../gcc-releases-gcc-12.2.0/configure -v --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu --prefix=/usr/local/gcc-13.2.0 --enable-checking=release --enable-languages=c,c++,fortran --disable-multilib --program-suffix=-12.2`
* Build it: `make -j 16`
* Install it: `sudo make install-strip`
* Do some more magic:
```
export PATH=/usr/local/gcc-12.2.0/bin:$PATH
export LD_LIBRARY_PATH=/usr/local/gcc-12.2.0/lib64:$LD_LIBRARY_PATH
```
* Let CMake know
```
export CC=/usr/local/gcc-12.2.0/bin/gcc-12.2
export CXX=/usr/local/gcc-12.2.0/bin/g++-12.2
export FC=/usr/local/gcc-12.2.0/bin/gfortran-12.2
```

### Installing LLVM
For clang-format and clang-tidy.
* `sudo apt update && sudo apt install zlib1g-dev`
* `git clone https://github.com/llvm/llvm-project.git`
* `cd llvm-project`
* Check out whichever version you want to use, e.g. `16.0.6`: `git checkout 7cbf1a2`
* `mkdir build`
* `cmake -S llvm -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS='clang;clang-tools-extra;cross-project-tests;libclc;lld;lldb;openmp;polly;pstl' -DCMAKE_INSTALL_PREFIX=/usr/local/llvm`
* `ninja -j 8 -C /llvm-install/llvm-project/build install`