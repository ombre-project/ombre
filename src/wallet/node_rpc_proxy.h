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

#pragma once

#include "include_base_utils.h"
#include "net/http_client.h"
#include <boost/thread/mutex.hpp>
#include <string>

namespace tools
{

class NodeRPCProxy
{
  public:
	NodeRPCProxy(epee::net_utils::http::http_simple_client &http_client, boost::mutex &mutex);

	void invalidate();

	boost::optional<std::string> get_rpc_version(uint32_t &version) const;
	boost::optional<std::string> get_height(uint64_t &height) const;
	void set_height(uint64_t h);
	boost::optional<std::string> get_target_height(uint64_t &height) const;
	boost::optional<std::string> get_earliest_height(uint8_t version, uint64_t &earliest_height) const;

  private:
	epee::net_utils::http::http_simple_client &m_http_client;
	boost::mutex &m_daemon_rpc_mutex;

	mutable uint64_t m_height;
	mutable time_t m_height_time;
	mutable uint64_t m_earliest_height[256];
	mutable uint64_t m_dynamic_per_kb_fee_estimate;
	mutable uint64_t m_dynamic_per_kb_fee_estimate_cached_height;
	mutable uint64_t m_dynamic_per_kb_fee_estimate_grace_blocks;
	mutable uint32_t m_rpc_version;
	mutable uint64_t m_target_height;
	mutable time_t m_target_height_time;
};
}
