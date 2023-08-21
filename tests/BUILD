cc_test(
    name = "tests",
    size = "small",
    srcs = [
        "test_cuda.cc",
        "test_leetcode.cc",
        "test_sanity.cc",
    ],
    deps = [
        "//common",
        "//cuda:ping",
        "//leetcode",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main",
    ],
)
