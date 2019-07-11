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

#include <boost/utility/value_init.hpp>
#include <iostream>
#include <stddef.h>

#include "generic-ops.h"
#include "hex.h"
#include "span.h"

namespace crypto
{

extern "C" {
#include "hash-ops.h"
}

#pragma pack(push, 1)
struct hash
{
	char data[HASH_SIZE];
};
struct hash8
{
	char data[8];
};
#pragma pack(pop)

static_assert(sizeof(hash) == HASH_SIZE, "Invalid structure size");
static_assert(sizeof(hash8) == 8, "Invalid structure size");

/*
    Cryptonight hash functions
  */

inline void cn_fast_hash(const void *data, std::size_t length, hash &hash)
{
	cn_fast_hash(data, length, reinterpret_cast<char *>(&hash));
}

inline hash cn_fast_hash(const void *data, std::size_t length)
{
	hash h;
	cn_fast_hash(data, length, reinterpret_cast<char *>(&h));
	return h;
}

inline void tree_hash(const hash *hashes, std::size_t count, hash &root_hash)
{
	tree_hash(reinterpret_cast<const char(*)[HASH_SIZE]>(hashes), count, reinterpret_cast<char *>(&root_hash));
}

inline std::ostream &operator<<(std::ostream &o, const crypto::hash &v)
{
	epee::to_hex::formatted(o, epee::as_byte_span(v));
	return o;
}
inline std::ostream &operator<<(std::ostream &o, const crypto::hash8 &v)
{
	epee::to_hex::formatted(o, epee::as_byte_span(v));
	return o;
}

const static crypto::hash null_hash = boost::value_initialized<crypto::hash>();
const static crypto::hash8 null_hash8 = boost::value_initialized<crypto::hash8>();
}

CRYPTO_MAKE_HASHABLE(hash)
CRYPTO_MAKE_COMPARABLE(hash8)
