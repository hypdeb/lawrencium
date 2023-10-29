load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "bookcamp",
    srcs = [
        "bookcamp.cpp",
    ],
    hdrs = [
        "bookcamp.h",
        "hello_world.h",
    ],
    visibility = ["//visibility:public"],
    deps = ["//common"],
)

cc_binary(
    name = "bookcamp_hello_world",
    srcs = [
        "hello_world.cpp",
    ],
    visibility = ["//visibility:public"],
    deps = [
        "bookcamp",
    ],
)

cc_library(
    name = "pascals_triangle",
    srcs = [
        "pascals_triangle.cpp",
    ],
    hdrs = [
        "pascals_triangle.h",
    ],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "benchmark_pascals_triangle",
    srcs = [
        "benchmark_pascals_triangle.cpp",
    ],
    copts = [
        "-O3",
    ],
    deps = [
        "pascals_triangle",
        "@com_google_benchmark//:benchmark_main",
    ],
)
