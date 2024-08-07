/*
 * Client code that handles the interaction with the Denarii API on behalf of the caller.
 * See: https://web.getmonero.org/resources/developer-guides/wallet-rpc.html
 */

#ifndef DENARII_CLIENT_H
#define DENARII_CLIENT_H

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <jni.h>

#include "curl/curl.h"
#include "include/nlohmann/json.hpp"
#include "src/bigint.h"
#include "src/randomx.h"

#include "Client/RandomX/randomx_client.h"
#include "Proto/wallet.pb.h"
#include "ProtoBuf/TextProto/read_text_proto.h"
#include "Tools/General/Strings/hex.h"
#include "Tools/General/Strings/replace.h"


#ifdef __cplusplus
extern "C" {
#endif
/**
 * JNI calls used to call the equivalent C++ functions below.
 */
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_createWallet(JNIEnv *, jobject, jstring);
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_transferMoney(JNIEnv *, jobject, jdouble, jstring, jstring);
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_getAddress(JNIEnv *, jobject, jstring);
JNIEXPORT jdouble JNICALL Java_com_keiros_client_denarii_DenariiClient_getBalanceOfWallet(JNIEnv *, jobject, jstring);
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_setCurrentWallet(JNIEnv *, jobject, jstring);
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_getBlockHashingBlob(JNIEnv *, jobject, jstring, jstring);
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_restoreWallet(JNIEnv*, jobject, jstring);
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_querySeed(JNIEnv*, jobject, jstring);
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_createNoLabelAddress(JNIEnv*, jobject, jstring);
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_createAddress(JNIEnv*, jobject, jstring, jstring);
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_startMining(JNIEnv*, jobject, jboolean, jboolean, jint);
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_stopMining(JNIEnv*, jobject);
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_initRandomX(JNIEnv *, jobject, jstring, jstring);
JNIEXPORT void JNICALL Java_com_keiros_client_denarii_DenariiClient_shutdownRandomX(JNIEnv *, jobject);
JNIEXPORT jint JNICALL Java_com_keiros_client_denarii_DenariiClient_attemptMineBlock(JNIEnv *, jobject, jint, jint, jstring, jstring, jlong, jstring);
JNIEXPORT jboolean JNICALL Java_com_keiros_client_denarii_DenariiClient_attemptSubmitBlock(JNIEnv *, jobject, jstring);

#ifdef __cplusplus
}
#endif


namespace common {

class DenariiClient {
public:

  ~DenariiClient();

  // Sends a command to the wallet rpc or daemon. Params should be a json object in its string representation.
  // This does not work with non json rpcs.
  // See: https://www.getmonero.org/resources/developer-guides/daemon-rpc.html#get_block_template
  // Or: https://web.getmonero.org/resources/developer-guides/wallet-rpc.html
  static void sendCommandToWalletRPC(const std::string& method, const std::string& params, std::string* output);
  static void sendCommandToDaemon(const std::string& method, const std::string& params, std::string* output);
  static void sendCommandToOldDaemon(const std::string& method, const std::string& params, std::string *output);
  static void sendCommand(const std::string& ip, const std::string& port, const std::string& method,
      const std::string& params, std::string* output);
  static void sendCommand(const std::string &method, const std::string &params, std::string *output);

  // Creates a wallet with the given wallet info. By default will use English as the language.
  static bool createWallet(const common::Wallet& wallet);

  // Creates a new sub address.
  static bool createAddress(common::Wallet* wallet);
  static bool createAddress(const std::string &label, common::Wallet* wallet);

  // Transfers the specified amount of money from one wallet to the other.
  static bool transferMoney(double amount, const common::Wallet &sender, const common::Wallet &receiver);

  // Gets an address for the given wallet info. And fills the address field.
  // This assumes you have already set the current wallet.
  static bool getAddress(common::Wallet *wallet);

  // Retrieves the balance of the wallet.
  static double getBalanceOfWallet(const common::Wallet& wallet);

  // Sets the current open wallet to the passed wallet.
  static bool setCurrentWallet(const common::Wallet& wallet);

  // Gets a block hashing blob for the current block. True if successful. False otherwise
  static bool getBlockHashingBlob(const Wallet& wallet, nlohmann::json* result);

  // Starts mining with the specified number of threads.
  static bool startMining(bool doBackgroundMining, bool ignoreBattery, int threads);

  // Stop mining with the specified number of threads.
  static bool stopMining();

  // Initializes RandomX so it can be used to mine. Returns true on success and false otherwise.
  static bool initRandomX(std::string& mode, const std::string& key);
  static bool initRandomX(std::string& mode, char* key, int keySize);

  // Shuts down RandomX.
  static void shutdownRandomX();

  // Attempts to mine a block. This will fail if the block nonce cannot be found after n attempts.
  // If successful then minedBlock will be set. Returns the current nonce.
  // Also specifies the wallet that will receive the funds.
  static int attemptMineBlock(int nonce, int attempts, const std::string& blockHashingBlob, const std::string& blockTemplateBlob,
      uint64_t difficulty, std::string* minedBlock);

  // Attempt to submit a mined block. Returns true on success and false otherwise.
  static bool attemptSubmitBlock(const std::string& minedBlock);

  // Restore a deterministic wallet from a mnemonic phrase. The wallet should have the name, password, and phrase in it.
  static bool restoreWallet(common::Wallet* wallet);

  // Query for the mnemonic seed of the wallet. Assumes the current wallet has been set.
  static bool querySeed(common::Wallet* wallet);

};

} // denarii_services



#endif //DENARII_CLIENT_H
