package(default_visibility = ["//visibility:public"])

config_setting(
    name = "windows",
    constraint_values = [
        "@bazel_tools//platforms:windows",
    ],
    visibility = ["//visibility:public"],
)

# likely needs to be improved to follow the actual distinction between compilers being used not platforms
cc_library(
    name = "daemonizer",
    srcs = select({
        ":windows": [
            "windows_daemonizer.inl",
            "windows_service.cpp",
        ],
        "//conditions:default": [
            "posix_daemonizer.inl",
            "posix_fork.cpp",
        ],
    }),
    hdrs = select({
        ":windows": [
            "daemonizer.h",
            "windows_service.h",
            "windows_service_runner.h",
        ],
        "//conditions:default": [
            "daemonizer.h",
            "posix_fork.h",
        ],
    }),
    deps = [
        "//src:common",
        "@boost//:chrono",
        "@boost//:filesystem",
        "@boost//:program_options",
    ],
)