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
#include "copyable_atomic.h"
#include "net/net_utils_base.h"
#include <atomic>
#include <unordered_set>

namespace cryptonote
{

struct cryptonote_connection_context : public epee::net_utils::connection_context_base
{
	cryptonote_connection_context() : m_state(state_before_handshake), m_remote_blockchain_height(0), m_last_response_height(0),
									  m_last_request_time(boost::posix_time::microsec_clock::universal_time()), m_callback_request_count(0), m_last_known_hash(crypto::null_hash) {}

	enum state
	{
		state_before_handshake = 0, //default state
		state_synchronizing,
		state_standby,
		state_idle,
		state_normal
	};

	state m_state;
	std::list<crypto::hash> m_needed_objects;
	std::unordered_set<crypto::hash> m_requested_objects;
	uint64_t m_remote_blockchain_height;
	uint64_t m_last_response_height;
	boost::posix_time::ptime m_last_request_time;
	epee::copyable_atomic m_callback_request_count; //in debug purpose: problem with double callback rise
	crypto::hash m_last_known_hash;
	//size_t m_score;  TODO: add score calculations
};

inline std::string get_protocol_state_string(cryptonote_connection_context::state s)
{
	switch(s)
	{
	case cryptonote_connection_context::state_before_handshake:
		return "state_before_handshake";
	case cryptonote_connection_context::state_synchronizing:
		return "state_synchronizing";
	case cryptonote_connection_context::state_standby:
		return "state_standby";
	case cryptonote_connection_context::state_idle:
		return "state_idle";
	case cryptonote_connection_context::state_normal:
		return "state_normal";
	default:
		return "unknown";
	}
}
}
