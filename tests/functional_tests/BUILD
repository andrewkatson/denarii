package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "functional_tests",
    srcs = [
        "main.cpp",
        "transactions_flow_test.cpp",
        "transactions_flow_test.h",
        "transactions_generation_from_blockchain.cpp",
        "transactions_generation_from_blockchain.h",
    ],
    linkopts = [
        "-ltinfo",
        "-lreadline",
    ],
    deps = [
        "//contrib/epee",
        "//src:cncrypto",
        "//src:common",
        "//src:cryptonote_core",
        "//src:wallet",
        "@boost//:program_options",
        "@boost//:regex",
        "@liblzma",
        "@libreadline",
    ],
)

cc_binary(
    name = "make_test_signature",
    srcs = ["make_test_signature.cc"],
    linkopts = [
        "-ltinfo",
        "-lreadline",
    ],
    deps = [
        "//contrib/epee",
        "//src:cncrypto",
        "//src:rpc_base",
        "@liblzma",
        "@libreadline",
    ],
)

py_binary(
    name = "functional_tests_rpc",
    srcs = ["functional_tests_rpc.py"],
    deps = [],
)

py_binary(
    name = "check_missing_rpc_methods",
    srcs = ["check_missing_rpc_methods.py"],
    deps = [],
)