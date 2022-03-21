package(default_visibility = ["//visibility:public"])

cc_test(
    name = "net_load_tests_clt",
    srcs = [
        "clt.cpp",
        "net_load_tests.h",
    ],
    linkopts = [
        "-ltinfo",
        "-lreadline",
        "-lunwind",
        "-llzma",
    ],
    deps = [
        "//contrib/epee",
        "//src:cryptonote_core",
        "//src:p2p",
        "//tests/unit_tests:unit_test_utils",
        "@boost//:chrono",
        "@boost//:date_time",
        "@boost//:system",
        "@boost//:thread",
        "@gtest",
        "@liblzma",
        "@libreadline",
        "@libsodium",
        "@libunwind",
    ],
)

cc_test(
    name = "net_load_tests_srv",
    srcs = [
        "net_load_tests.h",
        "srv.cpp",
    ],
    linkopts = [
        "-ltinfo",
        "-lreadline",
        "-lunwind",
        "-llzma",
    ],
    deps = [
        "//contrib/epee",
        "//src:cryptonote_core",
        "//src:p2p",
        "//tests/unit_tests:unit_test_utils",
        "@boost//:chrono",
        "@boost//:date_time",
        "@boost//:system",
        "@gtest",
        "@liblzma",
        "@libreadline",
        "@libsodium",
        "@libunwind",
    ],
)