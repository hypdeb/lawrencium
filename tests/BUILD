cc_test(
    name = "tests",
    size = "small",
    srcs = [
        "test_ccpg.cc",
        "test_cuda.cc",
        "test_leetcode.cc",
        "test_neural_nets.cc",
        "test_sanity.cc",
    ],
    deps = [
        "//ccpg",
        "//common",
        "//cuda:ping",
        "//leetcode",
        "//neural_nets",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)
