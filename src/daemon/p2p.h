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

#include "cryptonote_protocol/cryptonote_protocol_handler.h"
#include "daemon/protocol.h"
#include "p2p/net_node.h"

//#undef RYO_DEFAULT_LOG_CATEGORY
//#define RYO_DEFAULT_LOG_CATEGORY "daemon"

namespace daemonize
{

class t_p2p final
{
  private:
	typedef cryptonote::t_cryptonote_protocol_handler<cryptonote::core> t_protocol_raw;
	typedef nodetool::node_server<t_protocol_raw> t_node_server;

  public:
	static void init_options(boost::program_options::options_description &option_spec)
	{
		t_node_server::init_options(option_spec);
	}

  private:
	t_node_server m_server;

  public:
	t_p2p(
		boost::program_options::variables_map const &vm, t_protocol &protocol)
		: m_server{protocol.get()}
	{
		//initialize objects
		MGINFO("Initializing p2p server...");
		if(!m_server.init(vm))
		{
			throw std::runtime_error("Failed to initialize p2p server.");
		}
		MGINFO("p2p server initialized OK");
	}

	t_node_server &get()
	{
		return m_server;
	}

	void run()
	{
		MGINFO("Starting p2p net loop...");
		m_server.run();
		MGINFO("p2p net loop stopped");
	}

	void stop()
	{
		m_server.send_stop_signal();
	}

	~t_p2p()
	{
		MGINFO("Deinitializing p2p...");
		try
		{
			m_server.deinit();
		}
		catch(...)
		{
			MERROR("Failed to deinitialize p2p...");
		}
	}
};
}
