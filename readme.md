# Lawrencium Learning Ground
Repository used to track some experiments with build systems, Tensorflow and C++.
## Development Environment (Windows)
* Install WSL with the `Ubuntu 22.04` distribution.
* Install LLVM using the [Automatic Installation Script](https://apt.llvm.org/).
* Follow [those instructions](https://docs.nvidia.com/cuda/wsl-user-guide/index.html#getting-started-with-cuda-on-wsl-2).
* Run `install_bazel.sh` to install Bazel
* Install Python, pip and numpy
  * Note that this is making the build non-hermetic, but I haven't figured out a way of having Bazel find the Python interpreter set up directly in the build by Bazel.
* Build and / or run the tests to verify that everything is set up correctly:
```
bazel build --config=clang15 --action_env TF_REVISION="3c3ed183552eba6b8a7d5dd71c572ec6ff226f1e" --experimental_repo_remote_exec //tests:lawrencium_tests
bazel test --config=clang15 --action_env TF_REVISION="3c3ed183552eba6b8a7d5dd71c572ec6ff226f1e" --experimental_repo_remote_exec --test_output=all //tests:lawrencium_tests
```