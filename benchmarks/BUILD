cc_binary(
    name = "lawrencium_cpp_benchmarks",
    srcs = [
        "benchmark_cpp.cc",
    ],
    copts = ["-D_LIBCPP_ENABLE_EXPERIMENTAL=1"],
    deps = [
        "//src/cpp:lawrencium_lib",
        "@com_google_benchmark//:benchmark_main",
    ],
)
