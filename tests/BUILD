cc_test(
    name = "lawrencium_tests",
    size = "small",
    srcs = [
        "test_ping.cc",
        "test_ping_tensorflow.cc",
    ],
    linkstatic = 1,
    linkopts=["-lrt", "-force_load"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "@org_tensorflow//tensorflow/cc:scope",
        "@org_tensorflow//tensorflow/cc:client_session",
        "@org_tensorflow//tensorflow/cc:cc_ops",
        "@org_tensorflow//tensorflow/cc:ops",
        "@org_tensorflow//tensorflow/core",
        "@org_tensorflow//tensorflow/core:framework",
        "@org_tensorflow//tensorflow/core:tensorflow",
        "@org_tensorflow//tensorflow/core:lib",
        "@org_tensorflow//tensorflow/core:ops",
        "@org_tensorflow//tensorflow/core/platform:jpeg",
    ],
)
