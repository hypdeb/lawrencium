cc_test(
    name = "lawrencium_tests",
    size = "small",
    srcs = [
        "test_cuda.cc",
    ],
    copts = ["-D_LIBCPP_ENABLE_EXPERIMENTAL=1"],
    deps = [
        "//src/cpp:lawrencium_lib",
        "//src/cuda:ping",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "lawrencium_cpp_tests",
    size = "small",
    srcs = [
        "test_cpp.cc",
    ],
    copts = ["-D_LIBCPP_ENABLE_EXPERIMENTAL=1"],
    deps = [
        "//src/cpp:lawrencium_lib",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)
