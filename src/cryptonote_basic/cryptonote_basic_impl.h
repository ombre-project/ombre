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

#include "crypto/crypto.h"
#include "crypto/hash.h"
#include "cryptonote_basic.h"

namespace cryptonote
{
/************************************************************************/
/*                                                                      */
/************************************************************************/
template <class t_array>
struct array_hasher : std::unary_function<t_array &, std::size_t>
{
	std::size_t operator()(const t_array &val) const
	{
		return boost::hash_range(&val.data[0], &val.data[sizeof(val.data)]);
	}
};

#pragma pack(push, 1)
struct public_address_outer_blob
{
	uint8_t m_ver;
	account_public_address m_address;
	uint8_t check_sum;
};
struct public_integrated_address_outer_blob
{
	uint8_t m_ver;
	account_public_address m_address;
	crypto::hash8 payment_id;
	uint8_t check_sum;
};
#pragma pack(pop)

namespace
{
inline std::string return_first_address(const std::string &url, const std::vector<std::string> &addresses, bool dnssec_valid)
{
	if(addresses.empty())
		return {};
	return addresses[0];
}
}

struct address_parse_info
{
	account_public_address address;
	bool is_subaddress;
	bool has_payment_id;
	bool is_kurz;
	crypto::hash8 payment_id;
};

/************************************************************************/
/* Cryptonote helper functions                                          */
/************************************************************************/
size_t get_min_block_size();
size_t get_max_tx_size();

uint64_t get_dev_fund_amount_v0(uint64_t tx_total, uint64_t already_generated_coins);
uint64_t get_dev_fund_amount_v1(uint64_t tx_total, uint64_t already_generated_coins);

bool get_block_reward(network_type nettype, size_t median_size, size_t current_block_size, uint64_t already_generated_coins, uint64_t &reward, uint64_t height);
uint8_t get_account_address_checksum(const public_address_outer_blob &bl);
uint8_t get_account_integrated_address_checksum(const public_integrated_address_outer_blob &bl);

template <network_type NETTYPE>
std::string get_public_address_as_str(bool subaddress, const account_public_address &adr);

extern template std::string get_public_address_as_str<MAINNET>(bool subaddress, const account_public_address &adr);
extern template std::string get_public_address_as_str<TESTNET>(bool subaddress, const account_public_address &adr);
extern template std::string get_public_address_as_str<STAGENET>(bool subaddress, const account_public_address &adr);

inline std::string get_public_address_as_str(network_type nettype, bool subaddress, const account_public_address &adr)
{
	switch(nettype)
	{
	case MAINNET:
		return get_public_address_as_str<MAINNET>(subaddress, adr);
	case TESTNET:
		return get_public_address_as_str<TESTNET>(subaddress, adr);
	case STAGENET:
		return get_public_address_as_str<STAGENET>(subaddress, adr);
	default:
		return "";
	}
}

template <network_type NETTYPE>
std::string get_account_integrated_address_as_str(const account_public_address &adr, const crypto::hash8 &payment_id);

extern template std::string get_account_integrated_address_as_str<MAINNET>(account_public_address const &adr, crypto::hash8 const &payment_id);
extern template std::string get_account_integrated_address_as_str<TESTNET>(account_public_address const &adr, crypto::hash8 const &payment_id);
extern template std::string get_account_integrated_address_as_str<STAGENET>(account_public_address const &adr, crypto::hash8 const &payment_id);

inline std::string get_account_integrated_address_as_str(network_type nettype, const account_public_address &adr, const crypto::hash8 &payment_id)
{
	switch(nettype)
	{
	case MAINNET:
		return get_account_integrated_address_as_str<MAINNET>(adr, payment_id);
	case TESTNET:
		return get_account_integrated_address_as_str<TESTNET>(adr, payment_id);
	case STAGENET:
		return get_account_integrated_address_as_str<STAGENET>(adr, payment_id);
	default:
		return "";
	}
}

template <network_type NETTYPE>
bool get_account_address_from_str(address_parse_info &info, const std::string &str, const bool silent = false);

inline bool get_account_address_from_str(network_type nettype, address_parse_info &info, const std::string &str, const bool silent = false)
{
	switch(nettype)
	{
	case MAINNET:
		return get_account_address_from_str<MAINNET>(info, str, silent);
	case TESTNET:
		return get_account_address_from_str<TESTNET>(info, str, silent);
	case STAGENET:
		return get_account_address_from_str<STAGENET>(info, str, silent);
	default:
		return false;
	}
}

bool is_coinbase(const transaction &tx);

bool operator==(const cryptonote::transaction &a, const cryptonote::transaction &b);
bool operator==(const cryptonote::block &a, const cryptonote::block &b);
}

bool parse_hash256(const std::string str_hash, crypto::hash &hash);
