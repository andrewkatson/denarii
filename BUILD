package(default_visibility = ["//visibility:public"])

platform(
    name = "windows-mingw-gcc",
    constraint_values = [
        "@platforms//os:windows",
         "@platforms//cpu:x86_64",
        "@bazel_tools//tools/cpp:mingw",
    ],
)


py_binary(
    name = "configure",
    srcs = ["configure.py"],
    imports = [":workspace_path_finder", ":common"],
    deps = [":workspace_path_finder", ":common"],
)

py_binary(
    name = "configure_win",
    srcs = ["configure_win.py"],
    imports = [":workspace_path_finder", ":common"],
    deps = [":workspace_path_finder", ":common"],
)

py_library(
  name = "workspace_path_finder",
  srcs = ["workspace_path_finder.py"],
  deps = [],
)

py_library(
  name = "common",
  srcs = ["common.py"],
  deps = [":flags"],
  imports = [":flags"]
)

py_library(
  name = "flags", 
  srcs = ["flags.py"],
  deps = []
)