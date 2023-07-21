load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_google_googletest",
    sha256 = "5ac2cd780ff0bad9778c35cb2409b4af0b879a34e612ea67cefe4b2edd5dea6c",
    strip_prefix = "googletest-01e18376efe643a82cff468734f87f8c60e314b6",
    urls = ["https://github.com/google/googletest/archive/01e18376efe643a82cff468734f87f8c60e314b6.zip"],
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
