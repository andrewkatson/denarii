package(default_visibility = ["//visibility:public"])

config_setting(
    name = "windows",
    constraint_values = [
        "@platforms//os:windows",
    ],
    visibility = ["//visibility:public"],
)

config_setting(
    name = "mac",
    constraint_values = [
        "@platforms//os:macos",
    ],
    visibility = ["//visibility:public"],
)

config_setting(
   name = "linux",
   constraint_values = [
      "@platforms//os:linux",
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
        "mac": [
            "posix_daemonizer.inl",
            "posix_fork.cpp",
        ],
        "linux": [
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
        "mac": [
            "daemonizer.h",
            "posix_fork.h",
        ],
        "linux": [
            "daemonizer.h",
            "posix_fork.h",
        ],
    }),
    deps = [
        "//src:common",
        "@boost.chrono",
        "@boost.filesystem",
        "@boost.program_options",
    ],
)
