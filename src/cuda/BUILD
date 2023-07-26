load("@rules_cuda//cuda:defs.bzl", "cuda_library")

# thrust have code marked as __global__ or __kernel__
# so source for thrust should be built with cuda_library first
cuda_library(
    name = "thrust_cu",
    srcs = ["thrust.cu"],
    visibility = ["//visibility:public"],
    deps = ["@local_cuda//:thrust"],
)

# Run with 'bazel run //examples/thrust:main'
cc_binary(
    name = "thrust_main",
    deps = [":thrust_cu"],
)

cuda_library(
    name = "ping",
    srcs = [
        "basic_cuda.cu",
        "basic_kernels.cu",
        "ping.cu",
    ],
    hdrs = [
        "basic_cuda.cuh",
        "basic_kernels.cuh",
        "helpers.h",
        "ping.h",
    ],
    visibility = ["//visibility:public"],
)
