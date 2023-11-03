load("@rules_cuda//cuda:defs.bzl", "cuda_library")

cuda_library(
    name = "ccpg",
    srcs = [
        "julia.cu.cc",
        "matrixes.cu.cc",
        "vectors.cu.cc",
    ],
    hdrs = [
        "helpers.h",
        "julia.h",
        "matrixes.h",
        "shared.h",
        "vectors.h",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "benchmark_matrix_multiply",
    srcs = [
        "benchmark_matrix_multiplications.cc",
    ],
    copts = [
        "-O3",
    ],
    deps = [
        "ccpg",
        "//common",
        "@com_google_benchmark//:benchmark_main",
    ],
)

cc_binary(
    name = "demo_julia",
    srcs = [
        "demo_julia.cpp",
    ],
    copts = [
        "-O3",
    ],
    deps = [
        "ccpg",
        "//common",
        "@com_google_benchmark//:benchmark_main",
    ],
)
