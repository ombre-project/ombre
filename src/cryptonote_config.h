// Copyright (c) 2018, Ryo Currency Project
// Portions copyright (c) 2014-2018, The Monero Project
//
// Portions of this file are available under BSD-3 license. Please see ORIGINAL-LICENSE for details
// All rights reserved.
//
// Ryo changes to this code are in public domain. Please note, other licences may apply to the file.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers

#pragma once

#include <assert.h>
#include <boost/uuid/uuid.hpp>
#include <string>

#define CRYPTONOTE_DNS_TIMEOUT_MS 20000

#define CRYPTONOTE_GETBLOCKTEMPLATE_MAX_BLOCK_SIZE 196608 //size of block (bytes) that is the maximum that miners will produce
#define CRYPTONOTE_PUBLIC_ADDRESS_TEXTBLOB_VER 0
#define CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW 60
#define CURRENT_TRANSACTION_VERSION 2
#define MIN_TRANSACTION_VERSION 2
#define MAX_TRANSACTION_VERSION 3
#define CRYPTONOTE_DEFAULT_TX_SPENDABLE_AGE 10

// MONEY_SUPPLY - total number coins to be generated
#define MONEY_SUPPLY                                    ((uint64_t)1000000000000000000) //   1 billion.
#define MONEY_SUPPLY_V4                                 ((uint64_t)500000000000000000)  // 0.5 billion.
#define EMISSION_SPEED_FACTOR                           21
#define FINAL_SUBSIDY                                   ((uint64_t)10000000000) // 1 * pow(10, 9)
#define GENESIS_BLOCK_REWARD                            ((uint64_t)1000000000)

#define CRYPTONOTE_PROJECT_BLOCK_REWARD                  0.02 // Percentage of the total block reward.
// Initial dev fee - drops down rapidly and averages to CRYPTONOTE_PROJECT_BLOCK_REWARD over time
#define CRYPTONOTE_PROJECT_INITIAL_MULTIPLIER           0.06
#define EMISSION_SPEED_FACTOR_PER_MINUTE (20)

#define CRYPTONOTE_REWARD_BLOCKS_WINDOW 60

#define CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE 600
#define CRYPTONOTE_DISPLAY_DECIMAL_POINT 9

#define CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS 1

#define DIFFICULTY_BLOCKS_ESTIMATE_TIMESPAN common_config::DIFFICULTY_TARGET //just alias; used by tests

#define BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT 10000 //by default, blocks ids count in synchronizing
#define BLOCKS_SYNCHRONIZING_DEFAULT_COUNT 10		 //by default, blocks count in blocks downloading
#define CRYPTONOTE_PROTOCOL_HOP_RELAX_COUNT 3		 //value of hop, after which we use only announce of new block

#define CRYPTONOTE_MEMPOOL_TX_LIVETIME 86400				 //seconds, one day
#define CRYPTONOTE_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME 604800 //seconds, one week

#define COMMAND_RPC_GET_BLOCKS_FAST_MAX_COUNT 250

#define P2P_LOCAL_WHITE_PEERLIST_LIMIT 1000
#define P2P_LOCAL_GRAY_PEERLIST_LIMIT 5000

#define P2P_DEFAULT_CONNECTIONS_COUNT 8
#define P2P_DEFAULT_HANDSHAKE_INTERVAL 60	//seconds
#define P2P_DEFAULT_PACKET_MAX_SIZE 50000000 //50000000 bytes maximum packet size
#define P2P_DEFAULT_PEERS_IN_HANDSHAKE 250
#define P2P_DEFAULT_CONNECTION_TIMEOUT 5000		  //5 seconds
#define P2P_DEFAULT_PING_CONNECTION_TIMEOUT 2000  //2 seconds
#define P2P_DEFAULT_INVOKE_TIMEOUT 60 * 2 * 1000  //2 minutes
#define P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT 5000 //5 seconds
#define P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT 70
#define P2P_DEFAULT_ANCHOR_CONNECTIONS_COUNT 2

#define P2P_FAILED_ADDR_FORGET_SECONDS (60 * 60) //1 hour
#define P2P_IP_BLOCKTIME (60 * 60 * 24)			 //24 hour
#define P2P_IP_FAILS_BEFORE_BLOCK 10
#define P2P_IDLE_CONNECTION_KILL_INTERVAL (5 * 60) //5 minutes

#define P2P_SUPPORT_FLAG_FLUFFY_BLOCKS 0x01
#define P2P_SUPPORT_FLAGS P2P_SUPPORT_FLAG_FLUFFY_BLOCKS

#define ALLOW_DEBUG_COMMANDS

#define CRYPTONOTE_NAME "ombre"
#define CRYPTONOTE_POOLDATA_FILENAME "poolstate.bin"
#define CRYPTONOTE_BLOCKCHAINDATA_FILENAME "blockchain.bin"
#define CRYPTONOTE_BLOCKCHAINDATA_LOCK_FILENAME "lock.mdb"
#define P2P_NET_DATA_FILENAME "p2pstate.bin"
#define MINER_CONFIG_FILE_NAME "miner_conf.json"

#define THREAD_STACK_SIZE 5 * 1024 * 1024

#define PER_KB_FEE_QUANTIZATION_DECIMALS 8

#define HASH_OF_HASHES_STEP 256

#define DEFAULT_TXPOOL_MAX_SIZE 648000000ull // 3 days at 300000, in bytes

// coin emission change interval/speed configs
#define COIN_EMISSION_MONTH_INTERVAL                    6  // months to change emission speed
#define COIN_EMISSION_HEIGHT_INTERVAL                   ((uint64_t) (COIN_EMISSION_MONTH_INTERVAL * (30.4375 * 24 * 3600) / cryptonote::common_config::DIFFICULTY_TARGET)) // calculated to # of heights to change emission speed
#define PEAK_COIN_EMISSION_YEAR                         4
#define PEAK_COIN_EMISSION_HEIGHT                       ((uint64_t) (((12 * 30.4375 * 24 * 3600)/cryptonote::common_config::DIFFICULTY_TARGET) * PEAK_COIN_EMISSION_YEAR))// = (# of heights emmitted per year) * PEAK_COIN_EMISSION_YEAR

template <typename T, std::size_t N>
constexpr std::size_t countof(T const (&)[N]) noexcept
{
	return N;
}

// New constants are intended to go here
namespace cryptonote
{
enum network_type : uint8_t
{
	MAINNET = 0,
	TESTNET,
	STAGENET,
	FAKECHAIN,
	UNDEFINED = 255
};

enum hard_fork_feature
{
	FORK_POW_CN_HEAVY,
	FORK_POW_CN_GPU,
	FORK_DEV_FUND_V2,
	FORK_DEV_FUND_V3,
	FORK_FIXED_FEE,
	FORK_DIFF_V2,
	FORK_RINGSIZE_INC,
	FORK_RINGSIZE_INC_REQ,
	FORK_BULLETPROOFS,
	FORK_BULLETPROOFS_REQ,
	FORK_STRICT_TX_SEMANTICS,
	FORK_UNIFORM_IDS,
	FORK_UNIFORM_IDS_REQ
};

struct hardfork_conf
{
	static constexpr uint8_t FORK_ID_DISABLED = 0xff;

	hard_fork_feature ft;
	uint8_t mainnet;
	uint8_t testnet;
	uint8_t stagenet;
};

static constexpr hardfork_conf FORK_CONFIG[] = {
	{FORK_DIFF_V2, 2, 2, 1},
	{FORK_POW_CN_HEAVY,3, 3, 1},
	{FORK_POW_CN_GPU, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED},
	{FORK_DEV_FUND_V2, 4, 4, 1},
	{FORK_DEV_FUND_V3, 5, 4, 1},
	{FORK_FIXED_FEE, 5, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED},
	{FORK_STRICT_TX_SEMANTICS, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED},
	{FORK_RINGSIZE_INC, 5, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED},
	{FORK_RINGSIZE_INC_REQ, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED},
	{FORK_BULLETPROOFS, 5, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED},
	{FORK_BULLETPROOFS_REQ, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED},
	{FORK_UNIFORM_IDS, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED},
	{FORK_UNIFORM_IDS_REQ, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED, hardfork_conf::FORK_ID_DISABLED}
};

// COIN - number of smallest units in one coin
inline constexpr uint64_t MK_COINS(uint64_t coins) { return coins * 1000000000ull; }  // pow(10, 9)

struct common_config
{
	static constexpr size_t MIN_MIXIN_V1 = 10; // default & minimum mixin allowed
	static constexpr size_t MIN_MIXIN_V2 = 10;
	static constexpr size_t MAX_MIXIN = 240;

	static constexpr uint64_t POISSON_CHECK_TRIGGER = 10;  // Reorg size that triggers poisson timestamp check
	static constexpr uint64_t POISSON_CHECK_DEPTH = 60;   // Main-chain depth of the poisson check. The attacker will have to tamper 50% of those blocks
	static constexpr double POISSON_LOG_P_REJECT = -75.0; // Reject reorg if the probablity that the timestamps are genuine is below e^x, -75 = 10^-33

	/////////////// V1 difficulty constants
	static constexpr uint64_t DIFFICULTY_WINDOW_V1 = 720; // blocks
	static constexpr uint64_t DIFFICULTY_LAG_V1 = 15;	 // !!!
	static constexpr uint64_t DIFFICULTY_CUT_V1 = 60;	 // timestamps to cut after sorting
	static constexpr uint64_t DIFFICULTY_BLOCKS_COUNT_V1 = DIFFICULTY_WINDOW_V1 + DIFFICULTY_LAG_V1;
	static constexpr uint64_t BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW_V1 = 60;
	static constexpr uint64_t DIFFICULTY_TARGET = 60;

	/////////////// V2 difficulty constants
	static constexpr uint64_t DIFFICULTY_WINDOW_V2 = 93;
	static constexpr uint64_t DIFFICULTY_CUT_V2 = 60;
	static constexpr uint64_t DIFFICULTY_BLOCKS_COUNT_V2 = DIFFICULTY_WINDOW_V2;
	static constexpr uint64_t BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW_V2 = 60;

	static constexpr uint64_t BLOCK_FUTURE_TIME_LIMIT = 60 * 24;

	static constexpr uint64_t CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE = 240 * 1024; // 240 kB
	static constexpr uint64_t BLOCK_SIZE_GROWTH_FAVORED_ZONE = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE * 4;
	static constexpr uint64_t TRANSACTION_SIZE_LIMIT = 300 * 1024;			// 300 kB
	static constexpr uint64_t BLOCK_SIZE_LIMIT_ABSOLUTE = 16 * 1024 * 1024; // 16 MB
	static constexpr uint64_t FEE_PER_KB = 500000;
	static constexpr uint64_t FEE_PER_RING_MEMBER = 500000;
	static constexpr uint64_t DYNAMIC_FEE_PER_KB_BASE_FEE = 500000;				  // 0.0005 * pow(10, 9)
	static constexpr uint64_t DYNAMIC_FEE_PER_KB_BASE_BLOCK_REWARD = 64000000000; // 64 * pow(10, 9)

	static constexpr uint64_t CRYPTONOTE_MAX_BLOCK_NUMBER = 500000000;

	static constexpr uint64_t BULLETPROOF_MAX_OUTPUTS = 16;

	///////////////// Dev fund constants
	static constexpr const char* DEV_FUND_ADDRESS_V1 = "cashCdYTudG44DDXfmWFxv9mFBbZ4rmaB2HcB5uCWQRXfdnjSBf8CDT3d8KtR4vAos8U3YrJKqu3CGacg6iQSqDR1PTekywzyt";
	static constexpr const char* DEV_FUND_VIEWKEY_V1 = "\xbf\xfa\x80\x3b\xb4\x06\x1d\x93\xa8\x3a\x36\x13\xff\x47\x8c\x5b\x5e\x5c\xb0\xb0\x33\x7a\x73\x5e\x1a\x13\x04\xca\x9f\xab\x18\x07";
	static constexpr const char* DEV_FUND_ADDRESS_V2 = "cashCcaFrjhH1hNgK7TSXW4imEJA81zd2fwUzPvNKmzcLkG3US2YnQo8xiLze5RRZJMKkV15YpqgqZUu4Vxht7bK9zLRN2UCNM";
	static constexpr const char* DEV_FUND_VIEWKEY_V2 = "\xee\xe5\xc6\xcd\x5d\xed\xff\xbd\x21\xc1\x57\x6c\xd7\x0e\xbf\x33\x25\x3d\xc5\xee\x52\xc6\xf7\xb0\x73\xc9\xcd\x0e\xd8\x2b\x95\x00";
	//secret eee5c6cd5dedffbd21c1576cd70ebf33253dc5ee52c6f7b073c9cd0ed82b9500
	//public af9af800002f97d66e7bbcd191798140ec546d4d8ec230f071b763fcf6ed3145
	static constexpr const char* RYO_DONATION_ADDR = "cashL7NzHYoHrGvWRJvMygcqwb2pKKC6DCsCKuvoeiRBbPYBkUNF7Fh7F3qFY9WAnKUWCiS99PFXQfmuUJHcfF7X5LYbMYDP4P";
};

template <network_type type>
struct config : public common_config
{
};

template <>
struct config<MAINNET>
{
	static constexpr uint64_t LEGACY_LONG_ADDRESS_BASE58_PREFIX = 0xd7bd299; // Shade
	static constexpr uint64_t LEGACY_LONG_INTEGRATED_ADDRESS_BASE58_PREFIX = 0xb285bd299; // Shadow
	static constexpr uint64_t RYO_KURZ_SUBADDRESS_BASE58_PREFIX = 0x3c9299; // Shae
	static constexpr uint64_t RYO_KURZ_ADDRESS_BASE58_PREFIX = 0x6bb9299; // Shad3
	static constexpr uint64_t RYO_LONG_ADDRESS_BASE58_PREFIX = 0xe1f54; // cash
	static constexpr uint64_t RYO_LONG_INTEGRATED_ADDRESS_BASE58_PREFIX = 0xe9f54; // casi
	static constexpr uint64_t RYO_LONG_SUBADDRESS_BASE58_PREFIX = 0x1b19a;         // Suba
	static constexpr uint16_t P2P_DEFAULT_PORT = 19743;
	static constexpr uint16_t RPC_DEFAULT_PORT = 19744;
	static constexpr uint16_t ZMQ_RPC_DEFAULT_PORT = 19745;

	static constexpr boost::uuids::uuid NETWORK_ID = { { 0x04, 0x06, 0xdf, 0xce, 0xfc, 0x7c, 0x27, 0x4a, 0x24, 0xd4, 0xf3, 0x8d, 0x41, 0x42, 0x43, 0x41  } }; 

	static constexpr const char *GENESIS_TX =
		"013c01ff00018094ebdc0302bc7ae26c871f8f18415e0fbd4776f9d4dbd5297c126bd99e26cf218ea0d6ec4a2101450a7665ca17a5ef3c691898068994569bb033012598c43068161b1194592327";
	static constexpr uint32_t GENESIS_NONCE = 10000;

	////////////////////// Dev fund constants
	// How ofen do we add the dev reward
	static constexpr uint64_t DEV_FUND_PERIOD = 10; // 10 min
	static constexpr uint64_t DEV_FUND_AMOUNT = MK_COINS(2000000);
	static constexpr uint64_t DEV_FUND_LENGTH = 52 * 6; // 6 years
	static constexpr uint64_t DEV_FUND_START  = 797770;
};

template <>
struct config<TESTNET>
{
	static constexpr uint64_t LEGACY_LONG_ADDRESS_BASE58_PREFIX = 0x37751a;			   // Suto
	static constexpr uint64_t LEGACY_LONG_INTEGRATED_ADDRESS_BASE58_PREFIX = 0x34f51a; // Suti
	static constexpr uint64_t RYO_KURZ_SUBADDRESS_BASE58_PREFIX = 0x3fa0;			  // Tr
	static constexpr uint64_t RYO_KURZ_ADDRESS_BASE58_PREFIX = 0x7420;			  // Tu
	static constexpr uint64_t RYO_LONG_ADDRESS_BASE58_PREFIX = 0x211f;            // Te
	static constexpr uint64_t RYO_LONG_INTEGRATED_ADDRESS_BASE58_PREFIX = 0x629f; // Ti
	static constexpr uint64_t RYO_LONG_SUBADDRESS_BASE58_PREFIX = 0x59a0;         // Ts
	static constexpr uint16_t P2P_DEFAULT_PORT = 29743; 
	static constexpr uint16_t RPC_DEFAULT_PORT = 29744; 
	static constexpr uint16_t ZMQ_RPC_DEFAULT_PORT = 29745; 
 
	static constexpr boost::uuids::uuid NETWORK_ID = { {  0x12, 0x04, 0x06, 0xdf, 0xce, 0xfc, 0x7c, 0x27, 0x4a, 0x24, 0xd4, 0xf3, 0x41, 0x44, 0x44, 0x43 } }; 

	static constexpr const char *GENESIS_TX =
		"013c01ff0001bbbad6adf00d029b2e4c0281c0b02e7c53291a94d1d0cbff8883f8024f5142ee494ffbbd0880712101b20e782a04028cf9326ccd66e0d683f50dd1b261f4e81fac4bfa0c73d0601102";
	static constexpr uint32_t GENESIS_NONCE = 10001;
	
	////////////////////// Dev fund constants
	// How ofen do we add the dev reward
	static constexpr uint64_t DEV_FUND_PERIOD = 15 * 24; // 1 day
	static constexpr uint64_t DEV_FUND_AMOUNT = MK_COINS(8000000);
	static constexpr uint64_t DEV_FUND_LENGTH = 7 * 52 * 6; // 6 years (one day period)
	static constexpr uint64_t DEV_FUND_START  = 129750;
};

template <>
struct config<STAGENET>
{
	static constexpr uint64_t LEGACY_LONG_ADDRESS_BASE58_PREFIX = 0x37751a;			   // Suto
	static constexpr uint64_t LEGACY_LONG_INTEGRATED_ADDRESS_BASE58_PREFIX = 0x34f51a; // Suti
	static constexpr uint64_t LEGACY_LONG_SUBADDRESS_BASE58_PREFIX = 0x1d351a;		   // Susu

	static constexpr uint64_t RYO_KURZ_SUBADDRESS_BASE58_PREFIX = 0xdc2192;			  // RYosG
	static constexpr uint64_t RYO_KURZ_ADDRESS_BASE58_PREFIX = 0x1fc2192;			  // RYosK
	static constexpr uint64_t RYO_LONG_ADDRESS_BASE58_PREFIX = 0xd1c2192;			  // RYosT
	static constexpr uint64_t RYO_LONG_INTEGRATED_ADDRESS_BASE58_PREFIX = 0x1fbbe192; // RYosE
	static constexpr uint64_t RYO_LONG_SUBADDRESS_BASE58_PREFIX = 0xe3c2192;		  // RYosU

	static constexpr uint16_t P2P_DEFAULT_PORT = 39743; 
	static constexpr uint16_t RPC_DEFAULT_PORT = 39744; 
	static constexpr uint16_t ZMQ_RPC_DEFAULT_PORT = 39745; 
 
	static constexpr boost::uuids::uuid NETWORK_ID = { { 0x15, 0x77, 0x3a, 0x26, 0x42, 0xa0, 0x3f, 0xf3, 0xe5, 0x79, 0x72, 0x8d, 0x4e, 0x5a, 0xf2, 0x98 } }; 

	static constexpr const char *GENESIS_TX =
		"013c01ff0001ffffffffffff0302df5d56da0c7d643ddd1ce61901c7bdc5fb1738bfe39fbe69c28a3a7032729c0f2101168d0c4ca86fb55a4cf6a36d31431be1c53a3bd7411bb24e8832410289fa6f3b";
	static constexpr uint32_t GENESIS_NONCE = 10002;
	
	////////////////////// Dev fund constants
	// How ofen do we add the dev reward
	static constexpr uint64_t DEV_FUND_PERIOD = 15 * 24; // 1 day
	static constexpr uint64_t DEV_FUND_AMOUNT = MK_COINS(8000000);
	static constexpr uint64_t DEV_FUND_LENGTH = 7 * 52 * 6; // 6 years (one day period)
	static constexpr uint64_t DEV_FUND_START  = 129750;
};

extern template struct config<MAINNET>;
extern template struct config<TESTNET>;
extern template struct config<STAGENET>;

inline uint16_t config_get_p2p_port(network_type type)
{
	switch(type)
	{
	case MAINNET:
		return config<MAINNET>::P2P_DEFAULT_PORT;
	case STAGENET:
		return config<STAGENET>::P2P_DEFAULT_PORT;
	case TESTNET:
		return config<TESTNET>::P2P_DEFAULT_PORT;
	default:
		return 0;
	}
}

inline uint16_t config_get_rpc_port(network_type type)
{
	switch(type)
	{
	case MAINNET:
		return config<MAINNET>::RPC_DEFAULT_PORT;
	case STAGENET:
		return config<STAGENET>::RPC_DEFAULT_PORT;
	case TESTNET:
		return config<TESTNET>::RPC_DEFAULT_PORT;
	default:
		return 0;
	}
}

inline uint8_t get_fork_v(network_type nt, hard_fork_feature ft)
{
	for(size_t i = 0; i < countof(FORK_CONFIG); i++)
	{
		if(FORK_CONFIG[i].ft == ft)
		{
			switch(nt)
			{
			case MAINNET:
				return FORK_CONFIG[i].mainnet;
			case TESTNET:
				return FORK_CONFIG[i].testnet;
			case STAGENET:
				return FORK_CONFIG[i].stagenet;
			default:
				assert(false);
			}
		}
	}

	assert(false);
	return hardfork_conf::FORK_ID_DISABLED;
}
}
