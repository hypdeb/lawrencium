# Lawrencium Learning Ground
Repository used to track some experiments with build systems, Tensorflow and C++.
## Development Environment (Windows)
* Install WSL with the `Ubuntu 22.04` distribution.
* Install LLVM using the [Automatic Installation Script](https://apt.llvm.org/).
* Follow [those instructions](https://docs.nvidia.com/cuda/wsl-user-guide/index.html#getting-started-with-cuda-on-wsl-2).
* Run `install_bazel.sh` to install Bazel
* Run the tests to verify that everything is set up correctly:
```
bazel test --config=clang15 --test_output=all //tests:lawrencium_tests
```