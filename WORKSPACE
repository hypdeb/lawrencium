load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    sha256 = "ab4709e34b538e65c4575319965d3f1d2189ddd56ebb89e9a184ef3f4621ea64",
    strip_prefix = "googletest-b72202078d0a7a2f2509eb5237685bcf1baea3b4",
    urls = ["https://github.com/google/googletest/archive/b72202078d0a7a2f2509eb5237685bcf1baea3b4.zip"],
)

load("//tensorflow:repo.bzl", "tensorflow_http_archive")

tensorflow_http_archive(
    name = "org_tensorflow",
    git_commit = "3c3ed183552eba6b8a7d5dd71c572ec6ff226f1e",
    sha256 = "2a6b1ab52458308657d2d7235c7f51b2484a9cfaa203d7d750ccc14a94c8a731",
)

# Initialize TensorFlow's external dependencies.
load("@org_tensorflow//tensorflow:workspace3.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace2.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace1.bzl", "workspace")

workspace()

load("@org_tensorflow//tensorflow:workspace0.bzl", "workspace")

workspace()
