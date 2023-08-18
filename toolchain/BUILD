load(":cc_toolchain_config.bzl", "cc_toolchain_config")

package(default_visibility = ["//visibility:public"])

cc_toolchain_suite(
    name = "gcc_suite",
    toolchains = {
        "amd64": ":amd64_toolchain",
    },
)

filegroup(name = "empty")

cc_toolchain(
    name = "amd64_toolchain",
    all_files = ":empty",
    compiler_files = ":empty",
    dwp_files = ":empty",
    linker_files = ":empty",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = 0,
    toolchain_config = ":amd64_toolchain_config",
    toolchain_identifier = "amd64-toolchain",
)

cc_toolchain_config(name = "amd64_toolchain_config")
