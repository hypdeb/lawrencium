load("@rules_cuda//cuda:defs.bzl", "cuda_library")

cuda_library(
    name = "ping",
    srcs = [
        "ping.cu",
    ],
    hdrs = [
        "helpers.h",
        "ping.h",
    ],
    visibility = ["//visibility:public"],
)

cuda_library(
    name = "cuda_neural_nets",
    srcs = [
        "layers.cu.cc",
    ],
    hdrs = [
        "layers.h",
    ],
    visibility = ["//visibility:public"],
)
