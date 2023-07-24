load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    sha256 = "5ac2cd780ff0bad9778c35cb2409b4af0b879a34e612ea67cefe4b2edd5dea6c",
    strip_prefix = "googletest-01e18376efe643a82cff468734f87f8c60e314b6",
    urls = ["https://github.com/google/googletest/archive/01e18376efe643a82cff468734f87f8c60e314b6.zip"],
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
