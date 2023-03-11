load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    sha256 = "6e85b4467b6fe974ba7b6f2556654ef18f794ed7c73c06c1bfaefe5aa8561f6b",
    strip_prefix = "googletest-391ce627def20c1e8a54d10b12949b15086473dd",
    urls = ["https://github.com/google/googletest/archive/391ce627def20c1e8a54d10b12949b15086473dd.zip"],
)

load("//tensorflow_wrapper:repo.bzl", "tensorflow_http_archive")

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
