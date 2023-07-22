# Lawrencium Learning Ground
Repository used to track some experiments with build systems, Tensorflow and C++.
## Development Environment (Windows)
* Install WSL with the `Ubuntu 20.04` distribution.
  * Why this version ? At the time of writing this, LLVM does not support CUDA 12, we have to install CUDA 11.something, which cannot be installed in `Ubuntu 22.04`.
  * Note that this could be fixed with a trully hermetic build. But currently LLVM and CUDA have to be pre-installed (AFAIK).
  * Also make yourself
* Install LLVM using the [Automatic Installation Script](https://apt.llvm.org/).
* Follow [those instructions](https://developer.nvidia.com/cuda-11-5-2-download-archive?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=20.04&target_type=deb_local). See above as to why we can't use newer version.
* Run `install_bazel.sh` to install Bazel
* Install Python, pip and numpy
  * Note that this is making the build non-hermetic, but I haven't figured out a way of having Bazel find the Python interpreter set up directly in the build by Bazel.
```
sudo apt install python3-pip
pip install numpy
```
* You also need to install CUDNN by following this guide : https://docs.nvidia.com/deeplearning/cudnn/install-guide/index.html
  * Another hermeticity breach...
* Build and / or run the tests to verify that everything is set up correctly:
```
bazel build //tests:lawrencium_tests
bazel test --test_output=all //tests:lawrencium_tests
```