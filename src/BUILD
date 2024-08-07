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

cc_binary(
    name = "denariid",
    srcs = glob(
        [
            "**/cryptonote_protocol/cryptonote_protocol*",
            "**/daemon/*",
            "**/p2p/*",
        ],
        exclude = ["**/*.txt"],
    ) + [
        "rpc/core_rpc_server_commands_defs.h",
        "rpc/rpc_payment_costs.h",
        "serialization/pair.h",
        "wallet/message_store.cpp",
        "wallet/message_store.h",
        "wallet/message_transporter.cpp",
        "wallet/message_transporter.h",
        "wallet/node_rpc_proxy.cpp",
        "wallet/node_rpc_proxy.h",
        "wallet/ringdb.cpp",
        "wallet/ringdb.h",
        "wallet/wallet2.cpp",
        "wallet/wallet2.h",
        "wallet/wallet_args.cpp",
        "wallet/wallet_args.h",
        "wallet/wallet_errors.h",
        "wallet/wallet_rpc_helpers.h",
        "wallet/wallet_rpc_payments.cpp",
        "wallet/wallet_rpc_server_commands_defs.h",
        "wallet/wallet_rpc_server_error_codes.h",
    ],
    linkopts = [
        "-lpthread",
        "-llzma",
        "-Lother/openssl",
        "-lssl",
        "-lcrypto",
    ] + select({
        "windows": [
            "-L db_drivers/liblmdb",
            "-llmdb",
            "-lzmq",
            "-lunbound",
            "-L miniupnp/miniupnpc",
            "-lminiupnpc",
            "-Lother/randomx/build",
            "-lrandomx",
            "-lws2_32",
            "-lwsock32",
            "-lbcrypt",
            "-lbsd",
            "-fPIC",
        ],
        "mac": ["-Lother/openssl"],
        "linux": [
            "-L db_drivers/liblmdb",
            "-llmdb",
            "-lzmq",
            "-lunbound",
            "-L miniupnp/miniupnpc",
            "-lminiupnpc",
            "-lunwind",
            "-lbsd",
            "-fPIC",
        ],
    }),
    deps = [
        "//contrib/epee",
        "//other:db_drivers",
        "//other:liblzma",
        "//other:libreadline",
        "//other:libsodium",
        "//other:libunbound",
        "//other:miniupnpc",
        "//src:blockchain_db",
        "//src:cncrypto",
        "//src:common",
        "//src:cryptonote_core",
        "//src:cryptonote_protocol",
        "//src:daemon_rpc_server",
        "//src:multisig",
        "//src:net",
        "//src:p2p",
        "//src:rpc",
        "//src:rpc_base",
        "//src:serialization",
        "//src:version",
        "//src/blocks",
        "//src/centralnode:dynamic_critical_values",
        "//src/daemonizer",
        "//src/device_trezor",
        "//src/mnemonics",
        "@boost.asio",
        "@boost.chrono",
        "@boost.filesystem",
        "@boost.program_options",
        "@boost.regex",
        "@boost.serialization",
        "@boost.system",
        "@boost.thread",
    ] + select({
        "windows": [
        ],
        "mac": [],
        "linux": ["//other:libunwind"],
    }),
)

cc_library(
    name = "version",
    srcs = ["version.cpp"],
    hdrs = ["version.h"],
    deps = [],
)

cc_library(
    name = "config",
    srcs = [],
    hdrs = ["cryptonote_config.h"],
    deps = [
        "@boost.uuid",
    ],
)

cc_library(
    name = "cncrypto",
    srcs = glob([
        "**/crypto/*.c",
        "**/crypto/*.cpp",
    ]) + select({
        "windows": glob([
            "**/crypto/wallet/*.c",
            "**/crypto/wallet/*.cpp",
        ]),
        "mac": [],
        "linux": glob([
            "**/crypto/CryptonightR_template.S",
        ]),
    }),
    hdrs = glob([
        "**/crypto/*.h",
        "**/varint.h",
        "**/pod-class.h",
    ]) + select({
        "windows": glob(["**/crypto/wallet/*.h"]),
        "mac": [],
        "linux": [],
    }),
    copts = [
    ] + select({
        "windows": [
            "-msse4.1",
            "-maes",
            "-march=native",
        ],
        "mac": [],
        "linux": [
            "-msse4.1",
            "-maes",
            "-march=native",
        ],
    }),
    linkopts = select({
        "windows": [
            "-Lother/randomx/build",
            "-lrandomx",
        ],
        "mac": [
        ],
        "linux": [],
    }),
    deps = [
        ":config",
        "//contrib/epee",
        "//other:libsodium",
        "//other:randomx",
        "@boost.scope_exit",
        "@boost.system",
    ],
)

# ONLY USE IN TESTS THIS IS A WORKAROUND BECAUSE CMAKE IS WEIRD
cc_library(
    name = "cnccrypto_for_tests",
    srcs = [],
    hdrs = [
        "crypto/crypto.cpp",
        "crypto/crypto-ops.c",
        "crypto/hash.c",
        "crypto/keccak.c",
        "crypto/random.c",
    ],
    copts = [
    ] + select({
        "windows": [
            "-msse4.1",
            "-maes",
            "-march=native",
        ],
        "mac": [],
        "linux": [
            "-msse4.1",
            "-maes",
            "-march=native",
        ],
    }),
    linkopts = select({
        "windows": [
            "-Lother/randomx/build",
            "-lrandomx",
        ],
        "mac": [],
        "linux": [],
    }),
    deps = [
        ":config",
        "//contrib/epee",
        "//other:libsodium",
        "//other:randomx",
        "@boost.system",
    ],
)

cc_library(
    name = "common",
    srcs = glob([
        "**/common/*.c",
        "**/common/*.cc",
        "**/common/*.cpp",
    ]),
    hdrs = glob(["**/common/*.h"]),
    linkopts =
        select({
            ":windows": [
                "-Lother/openssl",
                "-lssl",
                "-lcrypto",
                "-Lexternal/libunbound",
                "-lunbound",
                "-lws2_32",
                "-lwsock32",
                "-ldbghelp",
            ],
            "mac": [],
            "linux": [
                "-Lother/openssl",
                "-lssl",
                "-lcrypto",
                "-Lexternal/libunbound",
                "-lunbound",
                "-ldl",
                "-lunwind",
            ],
        }),
    deps = [
        "//contrib/epee",
        "//other:crypto",
        "//other:libsodium",
        "//other:libunbound",
        "//other:ssl",
        "//src:cncrypto",
        "//src:config",
        "//src/boost/archive:boost_extra",
        "//translations",
        "@boost.chrono",
        "@boost.date_time",
        "@boost.filesystem",
        "@boost.format",
        "@boost.program_options",
        "@boost.regex",
        "@boost.system",
        "@boost.thread",
    ] + select({
        ":windows": [
        ],
        "mac": [],
        "linux": ["@libunwind"],
    }),
)

cc_library(
    name = "file",
    srcs = glob(["**/common/file/*.cc"]),
    hdrs = glob(["**/common/file/*.h"]),
    deps = [],
)

# ANOTHER WORKAROUND FOR TESTS. DO NOT USE NORMALLY.
cc_library(
    name = "common_for_tests",
    srcs = [],
    hdrs = ["common/base58.cpp"],
    deps = [],
)

cc_library(
    name = "cryptonote_protocol",
    srcs = glob(["**/cryptonote_protocol/*.cpp"]),
    hdrs = glob([
        "**/cryptonote_protocol/*.h",
        "**/cryptonote_protocol/*.inl",
    ]),
    deps = [
        "//src:file",
        "//src:p2p",
        "@boost.multi_index",
    ],
)

cc_library(
    name = "p2p",
    srcs = [
        "cryptonote_protocol/levin_notify.h",
        "p2p/net_node.cpp",
        "p2p/net_peerlist.cpp",
    ],
    hdrs = [
        "p2p/net_node.h",
        "p2p/net_node.inl",
        "p2p/net_node_common.h",
        "p2p/net_peerlist.h",
        "p2p/net_peerlist_boost_serialization.h",
        "p2p/p2p_protocol_defs.h",
        "p2p/stdafx.h",
    ],
    deps = [
        "//other:miniupnpc",
        "//src:cryptonote_core",
        "//src:net",
        "//src:version",
        "//src/boost/archive:boost_extra",
        "@boost.chrono",
        "@boost.filesystem",
        "@boost.multi_index",
        "@boost.program_options",
        "@boost.serialization",
        "@boost.system",
        "@boost.thread",
    ],
)

cc_library(
    name = "ringct_basic",
    srcs = [
        "cryptonote_basic/account.h",
        "cryptonote_basic/blobdatatype.h",
        "cryptonote_basic/cryptonote_basic.h",
        "cryptonote_basic/cryptonote_basic_impl.h",
        "cryptonote_basic/cryptonote_format_utils.h",
        "cryptonote_basic/subaddress_index.h",
        "cryptonote_basic/tx_extra.h",
        "device/device.hpp",
        "ringct/bulletproofs.cc",
        "ringct/multiexp.cc",
        "ringct/rctCryptoOps.c",
        "ringct/rctOps.cpp",
        "ringct/rctTypes.cpp",
        "serialization/binary_archive.h",
        "serialization/binary_utils.h",
        "serialization/container.h",
        "serialization/containers.h",
        "serialization/crypto.h",
        "serialization/debug_archive.h",
        "serialization/json_archive.h",
        "serialization/serialization.h",
        "serialization/variant.h",
    ],
    hdrs = [
        "ringct/bulletproofs.h",
        "ringct/multiexp.h",
        "ringct/rctCryptoOps.h",
        "ringct/rctOps.h",
        "ringct/rctTypes.h",
    ],
    linkopts =
        select({
            "windows": [
                "-Lother/openssl",
                "-lssl",
                "-lcrypto",
                "-lws2_32",
                "-lwsock32",
            ],
            "mac": [],
            "linux": [
                "-Lother/openssl",
                "-lssl",
                "-lcrypto",
                "-ldl",
            ],
        }),
    deps = [
        "//other:crypto",
        "//other:ssl",
        "//src:cncrypto",
        "//src:common",
        "//src/centralnode:dynamic_critical_values",
        "@boost.variant",
        "@boost.variant2",
    ],
)

cc_library(
    name = "ringct",
    srcs = ["ringct/rctSigs.cpp"],
    hdrs = ["ringct/rctSigs.h"],
    linkopts =
        select({
            "windows": [
                "-Lother/openssl",
                "-lssl",
                "-lcrypto",
                "-lws2_32",
                "-lwsock32",
            ],
            "mac": [],
            "linux": [
                "-Lother/openssl",
                "-lssl",
                "-lcrypto",
                "-ldl",
            ],
        }),
    deps = [
        "//other:crypto",
        "//other:ssl",
        "//src:cncrypto",
        "//src:common",
        "//src:cryptonote_basic",
        "//src:device",
    ],
)

cc_library(
    name = "serialization",
    srcs = [
        "rpc/message_data_structs.h",
        "serialization/json_object.cpp",
    ],
    hdrs = ["serialization/json_object.h"],
    deps = [
        "//contrib/epee",
        "//other:rapidjson",
        "//src:cryptonote_basic",
        "//src:cryptonote_core",
        "//src:cryptonote_protocol",
        "//src:version",
        "@boost.chrono",
        "@boost.regex",
        "@boost.system",
        "@boost.thread",
        "@boost.variant",
        "@boost.variant2",
    ],
)

cc_library(
    name = "cryptonote_basic",
    srcs = [
        "blockchain_db/blockchain_db.h",
        "cryptonote_basic/account.cpp",
        "cryptonote_basic/cryptonote_basic_impl.cpp",
        "cryptonote_basic/cryptonote_format_utils.cpp",
        "cryptonote_basic/difficulty.cpp",
        "cryptonote_basic/hardfork.cpp",
        "cryptonote_basic/miner.cpp",
        "cryptonote_protocol/enums.h",
        "ringct/rctSigs.h",
        "serialization/binary_utils.h",
        "serialization/crypto.h",
        "serialization/string.h",
        "serialization/variant.h",
    ],
    hdrs = [
        "cryptonote_basic/account.h",
        "cryptonote_basic/account_boost_serialization.h",
        "cryptonote_basic/connection_context.h",
        "cryptonote_basic/cryptonote_basic.h",
        "cryptonote_basic/cryptonote_basic_impl.h",
        "cryptonote_basic/cryptonote_boost_serialization.h",
        "cryptonote_basic/cryptonote_format_utils.h",
        "cryptonote_basic/difficulty.h",
        "cryptonote_basic/events.h",
        "cryptonote_basic/hardfork.h",
        "cryptonote_basic/miner.h",
        "cryptonote_basic/tx_extra.h",
        "cryptonote_basic/verification_context.h",
    ],
    linkopts = [] + select({
        "windows": [],
        "mac": ["-framework IOKit"],
        "linux": [],
    }),
    deps = [
        "//src:cncrypto",
        "//src:common",
        "//src:device",
        "//src:hardforks",
        "//src/boost/archive:boost_extra",
        "//src/centralnode:dynamic_critical_values",
        "@boost.date_time",
        "@boost.filesystem",
        "@boost.logic",
        "@boost.program_options",
        "@boost.serialization",
        "@boost.system",
        "@boost.thread",
    ],
)

cc_library(
    name = "device",
    srcs = [
        "blockchain_db/blockchain_db.h",
        "blockchain_db/locked_txn.h",
        "checkpoints/checkpoints.h",
        "common/portable_binary_iarchive.hpp",
        "common/portable_binary_oarchive.hpp",
        "crypto/wallet/crypto.h",
        "crypto/wallet/ops.h",
        "cryptonote_basic/account.h",
        "cryptonote_basic/cryptonote_boost_serialization.h",
        "cryptonote_basic/difficulty.h",
        "cryptonote_basic/hardfork.h",
        "cryptonote_basic/miner.h",
        "cryptonote_basic/subaddress_index.h",
        "cryptonote_basic/tx_extra.h",
        "cryptonote_basic/verification_context.h",
        "cryptonote_core/blockchain.h",
        "cryptonote_core/cryptonote_core_common.h",
        "cryptonote_core/cryptonote_tx_utils.h",
        "cryptonote_core/tx_pool.h",
        "cryptonote_protocol/cryptonote_protocol_defs.h",
        "cryptonote_protocol/enums.h",
        "device/device.cpp",
        "device/device_default.cpp",
        "device/device_io_hid.cpp",
        "device/device_ledger.cpp",
        "device/log.cpp",
        "hardforks/hardforks.h",
        "multisig/multisig.h",
        "ringct/rctSigs.h",
        "rpc/core_rpc_server_commands_defs.h",
        "rpc/core_rpc_server_error_codes.h",
        "rpc/message_data_structs.h",
        "rpc/rpc_handler.h",
        "serialization/pair.h",
        "wallet/message_store.h",
        "wallet/message_transporter.h",
        "wallet/node_rpc_proxy.h",
        "wallet/wallet2.h",
        "wallet/wallet_errors.h",
        "wallet/wallet_light_rpc.h",
        "wallet/wallet_rpc_helpers.h",
    ],
    hdrs = [
        "device/device.hpp",
        "device/device_cold.hpp",
        "device/device_default.hpp",
        "device/device_io.hpp",
        "device/device_io_hid.hpp",
        "device/device_ledger.hpp",
        "device/log.hpp",
    ],
    linkopts =
        select({
            "windows": [
                "-Lother/openssl",
                "-lssl",
                "-lcrypto",
                "-lws2_32",
                "-lwsock32",
            ],
            "mac": [],
            "linux": [
                "-Lother/openssl",
                "-lssl",
                "-lcrypto",
                "-ldl",
            ],
        }),
    deps = [
        "//other:crypto",
        "//other:libhidapi",
        "//other:ssl",
        "//src:cncrypto",
        "//src:ringct_basic",
        "//src:version",
        "//src/blocks",
        "//src/centralnode:dynamic_critical_values",
        "@boost.core",
        "@boost.logic",
        "@boost.multi_index",
        "@boost.serialization",
    ] + select({
        "windows": [],
        "mac": [],
        "linux": [
            "//other:supercop51",
            "//other:supercop64",
        ],
    }),
)

cc_library(
    name = "cryptonote_core",
    srcs = [
        "cryptonote_basic/cryptonote_format_utils.h",
        "cryptonote_basic/fwd.h",
        "cryptonote_core/blockchain.cpp",
        "cryptonote_core/cryptonote_core.cpp",
        "cryptonote_core/cryptonote_tx_utils.cpp",
        "cryptonote_core/tx_pool.cpp",
        "cryptonote_core/tx_sanity_check.cpp",
        "cryptonote_protocol/cryptonote_protocol_defs.h",
        "cryptonote_protocol/cryptonote_protocol_handler_common.h",
        "cryptonote_protocol/fwd.h",
        "p2p/net_node_common.h",
        "p2p/p2p_protocol_defs.h",
        "rpc/core_rpc_server_commands_defs.h",
        "rpc/fwd.h",
        "rpc/message_data_structs.h",
        "rpc/rpc_handler.h",
        "rpc/zmq_pub.h",
    ],
    hdrs = [
        "cryptonote_core/blockchain.h",
        "cryptonote_core/blockchain_storage_boost_serialization.h",
        "cryptonote_core/cryptonote_core.h",
        "cryptonote_core/cryptonote_core_common.h",
        "cryptonote_core/cryptonote_tx_utils.h",
        "cryptonote_core/i_core_events.h",
        "cryptonote_core/tx_pool.h",
        "cryptonote_core/tx_sanity_check.h",
    ],
    deps = [
        "//contrib/epee",
        "//src:blockchain_db",
        "//src:checkpoints",
        "//src:cncrypto",
        "//src:common",
        "//src:device",
        "//src:hardforks",
        "//src:multisig",
        "//src:net",
        "//src:ringct",
        "//src:version",
        "@boost.date_time",
        "@boost.filesystem",
        "@boost.multi_index",
        "@boost.program_options",
        "@boost.serialization",
        "@boost.system",
        "@boost.thread",
    ],
)

cc_library(
    name = "blockchain_db",
    srcs = [
        "blockchain_db/blockchain_db.cpp",
        "blockchain_db/lmdb/db_lmdb.cpp",
        "blockchain_db/locked_txn.h",
    ],
    hdrs = [
        "blockchain_db/blockchain_db.h",
        "blockchain_db/lmdb/db_lmdb.h",
        "blockchain_db/testdb.h",
    ],
    deps = [
        "//other:db_drivers",
        "//src:cncrypto",
        "//src:common",
        "//src:ringct",
        "@boost.filesystem",
        "@boost.thread",
    ],
)

cc_library(
    name = "wallet",
    srcs = [
        "rpc/core_rpc_server_commands_defs.h",
        "rpc/rpc_payment_costs.h",
        "serialization/pair.h",
        "wallet/message_store.cpp",
        "wallet/message_transporter.cpp",
        "wallet/node_rpc_proxy.cpp",
        "wallet/ringdb.cpp",
        "wallet/wallet2.cpp",
        "wallet/wallet_args.cpp",
        "wallet/wallet_rpc_payments.cpp",
    ],
    hdrs = [
        "wallet/message_store.h",
        "wallet/message_transporter.h",
        "wallet/node_rpc_proxy.h",
        "wallet/ringdb.h",
        "wallet/wallet2.h",
        "wallet/wallet_args.h",
        "wallet/wallet_errors.h",
        "wallet/wallet_rpc_helpers.h",
        "wallet/wallet_rpc_server_commands_defs.h",
        "wallet/wallet_rpc_server_error_codes.h",
    ],
    deps = [
        "//other:db_drivers",
        "//src:common",
        "//src:cryptonote_core",
        "//src:multisig",
        "//src:net",
        "//src:rpc_base",
        "//src:version",
        "//src/centralnode:dynamic_critical_values",
        "//src/device_trezor",
        "//src/mnemonics",
        "@boost.chrono",
        "@boost.filesystem",
        "@boost.regex",
        "@boost.serialization",
        "@boost.system",
        "@boost.thread",
    ],
)

cc_binary(
    name = "denarii_wallet_rpc_server",
    srcs = [
        "wallet/wallet_rpc_server.cpp",
        "wallet/wallet_rpc_server.h",
    ],
    linkopts = [
        "-lpthread",
        "-llzma",
        "-Lother/openssl",
        "-lssl",
        "-lcrypto",
    ] + select({
        "windows": [
            "-Lother/randomx/build",
            "-lrandomx",
            "-lws2_32",
            "-lwsock32",
            "-lbcrypt",
            "-fPIC",
        ],
        "mac": ["-Lother/openssl"],
        "linux": ["-fPIC"],
    }),
    deps = [
        ":wallet",
        "//other:liblzma",
        "//src:cncrypto",
        "//src:common",
        "//src:cryptonote_core",
        "//src:rpc_base",
        "//src:version",
        "//src/daemonizer",
        "@boost.asio",
        "@boost.chrono",
        "@boost.filesystem",
        "@boost.program_options",
        "@boost.thread",
    ],
)

cc_library(
    name = "net",
    srcs = [
        "net/dandelionpp.cpp",
        "net/error.cpp",
        "net/http.cpp",
        "net/i2p_address.cpp",
        "net/parse.cpp",
        "net/socks.cpp",
        "net/socks_connect.cpp",
        "net/tor_address.cpp",
        "net/zmq.cpp",
    ],
    hdrs = [
        "net/dandelionpp.h",
        "net/error.h",
        "net/fwd.h",
        "net/http.h",
        "net/i2p_address.h",
        "net/parse.h",
        "net/socks.h",
        "net/socks_connect.h",
        "net/tor_address.h",
        "net/zmq.h",
    ] + select({
        "windows": ["net/include/zmq.h"],
        "mac": [],
        "linux": [],
    }),
    deps = [
        "//contrib/epee",
        "//other:libzmq",
        "//src:common",
        "@boost.spirit",
    ] + select({
        "windows": ["@boost.asio"],
        "mac": [],
        "linux": ["@boost.asio"],
    }),
)

cc_library(
    name = "rpc_base",
    srcs = [
        "rpc/rpc_args.cpp",
        "rpc/rpc_handler.cpp",
        "rpc/rpc_payment_signature.cpp",
    ],
    hdrs = [
        "rpc/rpc_args.h",
        "rpc/rpc_handler.h",
        "rpc/rpc_payment_signature.h",
    ],
    deps = [
        "//contrib/epee",
        "//src:common",
        "//src:cryptonote_core",
        "@boost.program_options",
        "@boost.regex",
        "@boost.thread",
    ],
)

cc_library(
    name = "rpc",
    srcs = [
        "rpc/bootstrap_daemon.cpp",
        "rpc/bootstrap_daemon.h",
        "rpc/bootstrap_node_selector.cpp",
        "rpc/bootstrap_node_selector.h",
        "rpc/core_rpc_server.cpp",
        "rpc/core_rpc_server.h",
        "rpc/core_rpc_server_error_codes.h",
        "rpc/cryptonote_instantiations.cpp",
        "rpc/fwd.h",
        "rpc/nodetool_instantiations.cpp",
        "rpc/rpc_payment.cpp",
        "rpc/rpc_payment.h",
        "rpc/rpc_payment_costs.h",
        "rpc/rpc_version_str.cpp",
    ],
    hdrs = [
        "rpc/rpc_handler.h",
        "rpc/rpc_version_str.h",
    ],
    linkopts = select({
        "windows": [
            "-L miniupnp/miniupnpc",
            "-lminiupnpc",
        ],
        "mac": [],
        "linux": [
            "-L miniupnp/miniupnpc",
            "-lminiupnpc",
        ],
    }),
    deps = [
        ":rpc_base",
        "//other:miniupnpc",
        "//other:rapidjson",
        "//src:common",
        "//src:cryptonote_core",
        "//src:cryptonote_protocol",
        "//src:net",
        "//src:version",
        "//src/boost/archive:boost_extra",
        "@boost.regex",
        "@boost.thread",
    ],
)

cc_library(
    name = "rpc_pub",
    srcs = [
        "rpc/fwd.h",
        "rpc/zmq_pub.cpp",
    ],
    hdrs = ["rpc/zmq_pub.h"],
    deps = [
        "//contrib/epee",
        "//other:rapidjson",
        "//src:cryptonote_basic",
        "//src:net",
        "//src:serialization",
        "@boost.thread",
    ],
)

cc_library(
    name = "daemon_messages",
    srcs = [
        "rpc/daemon_messages.cpp",
        "rpc/daemon_rpc_version.h",
        "rpc/message.cpp",
        "rpc/message_data_structs.h",
    ],
    hdrs = [
        "rpc/daemon_messages.h",
        "rpc/message.h",
    ],
    deps = [
        "//other:rapidjson",
        "//src:cryptonote_core",
        "//src:cryptonote_protocol",
        "//src:serialization",
        "//src:version",
    ],
)

cc_library(
    name = "daemon_rpc_server",
    srcs = [
        "rpc/daemon_handler.cpp",
        "rpc/daemon_rpc_version.h",
        "rpc/message_data_structs.h",
        "rpc/zmq_pub.cpp",
        "rpc/zmq_server.cpp",
    ],
    hdrs = [
        "rpc/daemon_handler.h",
        "rpc/daemon_messages.h",
        "rpc/message.h",
        "rpc/zmq_server.h",
    ],
    deps = [
        ":daemon_messages",
        ":rpc",
        ":rpc_pub",
        "//other:libzmq",
        "//other:rapidjson",
        "//src:cryptonote_core",
        "//src:cryptonote_protocol",
        "//src:serialization",
        "//src:version",
        "@boost.chrono",
        "@boost.regex",
        "@boost.system",
        "@boost.thread",
    ],
)

# DO NOT USE NORMALLY THIS IS JUST A WORKAROUND
cc_library(
    name = "daemon_files_for_test",
    srcs = glob([
        "**/daemon/*.c",
        "**/daemon/*.cpp",
        "**/daemon/*.cc",
    ]),
    hdrs = glob([
        "**/daemon/*.h",
        "**/daemon/*.hpp",
    ]),
    deps = [
        ":daemon_rpc_server",
        "//contrib/epee",
        "//other:rapidjson",
        "//src/daemonizer",
    ],
)

cc_binary(
    name = "denarii_blockchain_export",
    srcs = [
        "blockchain_utilities/blockchain_export.cpp",
        "blockchain_utilities/blockchain_utilities.h",
        "blockchain_utilities/blocksdat_file.cpp",
        "blockchain_utilities/blocksdat_file.h",
        "blockchain_utilities/bootstrap_file.cpp",
        "blockchain_utilities/bootstrap_file.h",
        "blockchain_utilities/bootstrap_serialization.h",
        "serialization/difficulty_type.h",
        "serialization/json_utils.h",
    ],
    linkopts = [
        "-Lother/openssl",
        "-lssl",
        "-lcrypto",
    ] + select({
        "windows": [
            "-llzma",
            "-lws2_32",
            "-lwsock32",
        ],
        "mac": [],
        "linux": [
            "-llzma",
            "-ldl",
        ],
    }),
    deps = [
        "//contrib/epee",
        "//other:crypto",
        "//other:liblzma",
        "//other:ssl",
        "//src:blockchain_db",
        "//src:cryptonote_core",
        "//src:version",
        "@boost.filesystem",
        "@boost.system",
        "@boost.thread",
    ],
)

cc_binary(
    name = "denarii_blockchain_import",
    srcs = [
        "blockchain_utilities/blockchain_import.cpp",
        "blockchain_utilities/blockchain_utilities.h",
        "blockchain_utilities/blocksdat_file.cpp",
        "blockchain_utilities/blocksdat_file.h",
        "blockchain_utilities/bootstrap_file.cpp",
        "blockchain_utilities/bootstrap_file.h",
        "blockchain_utilities/bootstrap_serialization.h",
        "serialization/difficulty_type.h",
        "serialization/json_utils.h",
    ],
    linkopts = ["-llzma"],
    deps = [
        "//contrib/epee",
        "//other:liblzma",
        "//src:blockchain_db",
        "//src:cryptonote_core",
        "//src:version",
        "//src/blocks",
        "@boost.asio",
        "@boost.filesystem",
        "@boost.thread",
    ],
)

cc_binary(
    name = "denarii_blockchain_blackball",
    srcs = [
        "blockchain_utilities/blockchain_blackball.cpp",
        "blockchain_utilities/blockchain_utilities.h",
        "blockchain_utilities/blocksdat_file.h",
        "blockchain_utilities/bootstrap_file.h",
        "blockchain_utilities/bootstrap_serialization.h",
        "serialization/difficulty_type.h",
    ],
    linkopts = ["-llzma"],
    deps = [
        "//contrib/epee",
        "//other:liblzma",
        "//src:blockchain_db",
        "//src:cryptonote_core",
        "//src:version",
        "//src:wallet",
        "@boost.filesystem",
        "@boost.thread",
    ],
)

cc_binary(
    name = "denarii_blockchain_usage",
    srcs = ["blockchain_utilities/blockchain_usage.cpp"],
    linkopts = ["-llzma"],
    deps = [
        "//contrib/epee",
        "//other:liblzma",
        "//src:blockchain_db",
        "//src:cryptonote_core",
        "//src:version",
        "@boost.filesystem",
        "@boost.thread",
    ],
)

cc_binary(
    name = "denarii_blockchain_ancestry",
    srcs = ["blockchain_utilities/blockchain_ancestry.cpp"],
    linkopts = ["-llzma"],
    deps = [
        "//contrib/epee",
        "//other:liblzma",
        "//src:blockchain_db",
        "//src:cryptonote_core",
        "//src:version",
        "@boost.filesystem",
        "@boost.thread",
    ],
)

cc_binary(
    name = "denarii_blockchain_prune_known_spent_data",
    srcs = ["blockchain_utilities/blockchain_prune_known_spent_data.cpp"],
    linkopts = ["-llzma"],
    deps = [
        "//contrib/epee",
        "//other:liblzma",
        "//src:blockchain_db",
        "//src:cryptonote_core",
        "//src:p2p",
        "//src:version",
        "@boost.filesystem",
        "@boost.thread",
    ],
)

cc_binary(
    name = "denarii_blockchain_prune",
    srcs = ["blockchain_utilities/blockchain_prune.cpp"],
    linkopts = ["-llzma"],
    deps = [
        "//contrib/epee",
        "//other:liblzma",
        "//src:blockchain_db",
        "//src:cryptonote_core",
        "//src:p2p",
        "//src:version",
        "@boost.filesystem",
        "@boost.thread",
    ],
)

cc_binary(
    name = "denarii_blockchain_depth",
    srcs = ["blockchain_utilities/blockchain_depth.cpp"],
    linkopts = ["-llzma"],
    deps = [
        "//contrib/epee",
        "//other:liblzma",
        "//src:blockchain_db",
        "//src:cryptonote_core",
        "//src:version",
        "@boost.filesystem",
        "@boost.thread",
    ],
)

cc_binary(
    name = "denarii_blockchain_stats",
    srcs = ["blockchain_utilities/blockchain_stats.cpp"],
    linkopts = ["-llzma"],
    deps = [
        "//contrib/epee",
        "//other:liblzma",
        "//src:blockchain_db",
        "//src:cryptonote_core",
        "//src:version",
        "@boost.filesystem",
        "@boost.thread",
    ],
)

cc_binary(
    name = "example_of_error",
    srcs = ["example_of_error.cpp"],
    deps = [
    ],
)

cc_binary(
    name = "cannot_catch_exception",
    srcs = [
        "cannot_catch_exception.cpp",
    ],
    linkopts = [
        "-llzma",
    ],
    deps = [
    ] + select({
        "windows": [
        ],
        "mac": [],
        "linux": ["//other:libunwind"],
    }),
)

cc_binary(
    name = "cannot_catch_boost_interrupt",
    srcs = ["cannot_catch_boost_interrupt.cpp"],
    linkopts = [
        "-llzma",
    ],
    deps = [
        "@boost.thread",
        "@liblzma",
    ] + select({
        "windows": [
        ],
        "mac": [],
        "linux": ["//other:libunwind"],
    }),
)

cc_binary(
    name = "what_is_argv",
    srcs = ["what_is_argv.cpp"],
    deps = ["//other:miniupnpc"],
)

# This doesn't work because on Mac the other parts of the select statment get evaluated and
# that causes the evaluator to recur endlessly.
#cc_binary(
#    name = "general_import_tester",
#    srcs = ["general_import_tester.cpp"],
#    deps = ["@libnorm",]
#)

cc_library(
    name = "checkpoints",
    srcs = ["checkpoints/checkpoints.cpp"],
    hdrs = ["checkpoints/checkpoints.h"],
    deps = [
        "//src:cncrypto",
        "//src:common",
        "//src:cryptonote_basic",
        "@boost.date_time",
        "@boost.filesystem",
        "@boost.program_options",
        "@boost.serialization",
        "@boost.system",
        "@boost.thread",
    ],
)

# WORKAROUND TO GET TESTS WORKING DO NOT USE
cc_library(
    name = "checkpoints_for_tests",
    srcs = [],
    hdrs = ["checkpoints/checkpoints.cpp"],
    deps = [],
)

cc_library(
    name = "hardforks",
    srcs = ["hardforks/hardforks.cpp"],
    hdrs = ["hardforks/hardforks.h"],
    deps = ["//src:version"],
)

cc_library(
    name = "multisig",
    srcs = ["multisig/multisig.cpp"],
    hdrs = ["multisig/multisig.h"],
    deps = [
        "//src:cncrypto",
        "//src:common",
        "//src:cryptonote_basic",
        "//src:ringct",
    ],
)
