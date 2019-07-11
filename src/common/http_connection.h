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

#include "net/http_client.h"
#include "string_tools.h"
#include <chrono>

namespace tools
{

class t_http_connection
{
  private:
	epee::net_utils::http::http_simple_client *mp_http_client;
	bool m_ok;

  public:
	static constexpr std::chrono::seconds TIMEOUT()
	{
		return std::chrono::minutes(3) + std::chrono::seconds(30);
	}

	t_http_connection(epee::net_utils::http::http_simple_client *p_http_client)
		: mp_http_client(p_http_client), m_ok(false)
	{
		m_ok = mp_http_client->connect(TIMEOUT());
	}

	~t_http_connection()
	{
		if(m_ok)
		{
			mp_http_client->disconnect();
		}
	}

	bool is_open() const
	{
		return m_ok;
	}
}; // class t_http_connection

} // namespace tools
