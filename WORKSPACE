load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    sha256 = "ab4709e34b538e65c4575319965d3f1d2189ddd56ebb89e9a184ef3f4621ea64",
    strip_prefix = "googletest-b72202078d0a7a2f2509eb5237685bcf1baea3b4",
    urls = ["https://github.com/google/googletest/archive/b72202078d0a7a2f2509eb5237685bcf1baea3b4.zip"],
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
