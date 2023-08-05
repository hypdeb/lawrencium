# Lawrencium Learning Ground
Repository used to track some experiments with build systems, C++ and CUDA.
## Development Environment Set Up From Clean Ubuntu 22.04 Installation
Below are the numerous steps necessary to have a working development environment.
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
### Installing GCC from source, to be able to build LLVM
If this works, thanks to [this guy](https://iamsorush.com/posts/build-gcc11/): 
* Create some folder as a workspace, say /gcc-install
* Move to that folder
* Run `wget https://github.com/gcc-mirror/gcc/archive/refs/tags/releases/gcc-13.2.0.tar.gz`
* Extract the thing: `tar -xvf gcc-13.2.0.tar.gz`
* Navigate to the folder: `cd gcc-releases-gcc-13.2.0`
* Run the provided script which downloads and installs prerequisites: `contrib/download_prerequisites`
* Some guy says some other dependencies might be missing. Run this just to be sure:
  * `sudo apt update && sudo apt install bzip2 flex`
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
### Installing LLVM
* `sudo apt update && sudo apt install zlib1g-dev`
* `git clone https://github.com/llvm/llvm-project.git`
* `cd llvm-project`
* Check out a version that is compatible with CUDA, e.g. `15.0.7`: `git checkout 8dfdcc7`
* `cmake -S llvm -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_PROJECTS='clang;clang-tools-extra;cross-project-tests;libclc;lld;lldb;openmp;polly;pstl' -DCMAKE_INSTALL_PREFIX=/usr/local/llvm`
* `ninja -j 8 -C /llvm-install/llvm-project/build install`
* Then we still need to build libc++:
  * `rm -rf build`
  * `mkdir build`
  * `cmake -G Ninja -S runtimes -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local/llvm -DCMAKE_C_COMPILER=/usr/local/llvm/bin/clang -DCMAKE_CXX_COMPILER=/usr/local/llvm/bin/clang++ -DLLVM_ENABLE_RUNTIMES="libcxx;libcxxabi;libunwind"`
  * `ninja -C build cxx cxxabi unwind`
  * `ninja -C build check-cxx check-cxxabi check-unwind`
  * `ninja -C build install-cxx install-cxxabi install-unwind`
* Set `CUDA_PATH` to your CUDA installation path, e.g. `/usr/local/cuda-12.2`
* Set `CUDA_CLANG_PATH` to your clang installation path, e.g. `/usr/local/llvm/bin/clang` 