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

#include "common/scoped_message_writer.h"
#include "common/util.h"
#include "daemonizer/posix_fork.h"

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

namespace daemonizer
{
namespace
{
const command_line::arg_descriptor<bool> arg_detach = {
	"detach", "Run as daemon"};
const command_line::arg_descriptor<std::string> arg_pidfile = {
	"pidfile", "File path to write the daemon's PID to (optional, requires --detach)"};
const command_line::arg_descriptor<bool> arg_non_interactive = {
	"non-interactive", "Run non-interactive"};
}

inline void init_options(
	boost::program_options::options_description &hidden_options, boost::program_options::options_description &normal_options)
{
	command_line::add_arg(normal_options, arg_detach);
	command_line::add_arg(normal_options, arg_pidfile);
	command_line::add_arg(normal_options, arg_non_interactive);
}

inline boost::filesystem::path get_default_data_dir()
{
	return boost::filesystem::absolute(tools::get_default_data_dir());
}

inline boost::filesystem::path get_relative_path_base(
	boost::program_options::variables_map const &vm)
{
	return boost::filesystem::current_path();
}

template <typename T_executor>
inline bool daemonize(
	int argc, char* argv[], T_executor &&executor // universal ref
	,
	boost::program_options::variables_map const &vm)
{
	if(command_line::has_arg(vm, arg_detach))
	{
		tools::success_msg_writer() << "Forking to background...";
		std::string pidfile;
		if(command_line::has_arg(vm, arg_pidfile))
		{
			pidfile = command_line::get_arg(vm, arg_pidfile);
		}
		posix::fork(pidfile);
		auto daemon = executor.create_daemon(vm);
		return daemon.run();
	}
	else if(command_line::has_arg(vm, arg_non_interactive))
	{
		return executor.run_non_interactive(vm);
	}
	else
	{
		//LOG_PRINT_L0("Ryo '" << RYO_RELEASE_NAME << "' (" << RYO_VERSION_FULL);
		return executor.run_interactive(vm);
	}
}
}
