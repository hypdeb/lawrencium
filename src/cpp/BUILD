load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_binary(
    name = "hello-world",
    srcs = ["main.cc"],
)

cc_library(
    name = "lawrencium_lib",
    hdrs = ["common.h"],
    visibility = ["//visibility:public"],
)
