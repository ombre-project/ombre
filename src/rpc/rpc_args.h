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
#pragma once

#include <boost/optional/optional.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <string>

#include "common/command_line.h"
#include "common/password.h"

namespace cryptonote
{
//! Processes command line arguments related to server-side RPC
struct rpc_args
{
	// non-static construction prevents initialization order issues
	struct descriptors
	{
		descriptors();
		descriptors(const descriptors &) = delete;
		descriptors(descriptors &&) = delete;
		descriptors &operator=(const descriptors &) = delete;
		descriptors &operator=(descriptors &&) = delete;

		const command_line::arg_descriptor<std::string> rpc_bind_ip;
		const command_line::arg_descriptor<std::string> rpc_login;
		const command_line::arg_descriptor<bool> confirm_external_bind;
		const command_line::arg_descriptor<std::string> rpc_access_control_origins;
	};

	static const char *tr(const char *str);
	static void init_options(boost::program_options::options_description &desc);

	//! \return Arguments specified by user, or `boost::none` if error
	static boost::optional<rpc_args> process(const boost::program_options::variables_map &vm);

	std::string bind_ip;
	std::vector<std::string> access_control_origins;
	boost::optional<tools::login> login; // currently `boost::none` if unspecified by user
};
}
