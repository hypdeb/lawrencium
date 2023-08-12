load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "lawrencium_lib",
    srcs = ["matrixes.cpp"],
    hdrs = [
        "common.h",
        "matrixes.h",
    ],
    copts = ["-D_LIBCPP_ENABLE_EXPERIMENTAL=1"],
    visibility = ["//visibility:public"],
)
