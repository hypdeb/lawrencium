load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    sha256 = "6baf9ca041462b9506aafd8bbe7c3a7628efd07ffd9aa4e7cc631c896845d250",
    strip_prefix = "googletest-455fcb7773dedc70ab489109fb12d8abc7fd59b6",
    urls = ["https://github.com/google/googletest/archive/455fcb7773dedc70ab489109fb12d8abc7fd59b6.zip"],
)

http_archive(
    name = "com_google_benchmark",
    sha256 = "0094b77c01e9973876f1831f76cbae43fdaf09b424e467dc4171abaa6884e455",
    strip_prefix = "benchmark-1.8.2",
    urls = ["https://github.com/google/benchmark/archive/refs/tags/v1.8.2.zip"],
)

http_archive(
    name = "com_google_absl",
    strip_prefix = "abseil-cpp-8f241e778c08cfb4213877b5022442a8d1921b58",
    urls = ["https://github.com/abseil/abseil-cpp/archive/8f241e778c08cfb4213877b5022442a8d1921b58.zip"],
)

http_archive(
    name = "rules_cuda",
    sha256 = "fa1462c4c3104de44489800a1da055f55afa57795789539c835e069818786f71",
    strip_prefix = "rules_cuda-cab1fa2dd0e1f8489f566c91a5025856cf5ae572",
    urls = ["https://github.com/bazel-contrib/rules_cuda/archive/cab1fa2dd0e1f8489f566c91a5025856cf5ae572.tar.gz"],
)

load("@rules_cuda//cuda:repositories.bzl", "register_detected_cuda_toolchains", "rules_cuda_dependencies")

rules_cuda_dependencies()

register_detected_cuda_toolchains()
