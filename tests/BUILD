cc_test(
    name = "tests",
    size = "small",
    srcs = [
        "test_bookcamp.cc",
        "test_ccpg.cc",
        "test_cuda.cc",
        "test_leetcode.cc",
        "test_neural_nets.cc",
        "test_sanity.cc",
    ],
    deps = [
        "//bookcamp",
        "//ccpg",
        "//common",
        "//cuda:ping",
        "//leetcode",
        "//neural_nets",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_bookcamp",
    size = "small",
    srcs = [
        "test_bookcamp.cc",
    ],
    deps = [
        "//bookcamp:pascals_triangle",
        "//common",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)
