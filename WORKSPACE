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
    sha256 = "9039c00f5cfe0ac5ff1110d20706bc41d6dbd52c737f303e9a4cea0994ec19a9",
    strip_prefix = "rules_cuda-0503ead4724517db445796cbcdfc8400ce88c853",
    urls = ["https://github.com/bazel-contrib/rules_cuda/archive/0503ead4724517db445796cbcdfc8400ce88c853.tar.gz"],
)

load("@rules_cuda//cuda:repositories.bzl", "register_detected_cuda_toolchains", "rules_cuda_dependencies")

rules_cuda_dependencies()

register_detected_cuda_toolchains()
