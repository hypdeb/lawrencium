load(
    "@local_config_cuda//cuda:build_defs.bzl",
    "cuda_library",
)

cuda_library(
    srcs = ['cuda_test.cu'],
    hdrs = ['cuda_test.cu.h'],
    alwayslink = 1,
    name = "cuda_lib",
    deps = [

    ],
)

cc_binary(
  name = 'cuda_demo',
  srcs = ['main.cc'],
  deps = [
    "//demos/cuda:cuda_lib"
  ],
)