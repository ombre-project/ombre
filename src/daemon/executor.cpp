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

#include "misc_log_ex.h"

#include "daemon/executor.h"

#include "cryptonote_config.h"
#include "version.h"

#include <string>

//#undef RYO_DEFAULT_LOG_CATEGORY
//#define RYO_DEFAULT_LOG_CATEGORY "daemon"

namespace daemonize
{
std::string const t_executor::NAME = "Ryo Daemon";

void t_executor::init_options(
	boost::program_options::options_description &configurable_options)
{
	t_daemon::init_options(configurable_options);
}

std::string const &t_executor::name()
{
	return NAME;
}

t_daemon t_executor::create_daemon(
	boost::program_options::variables_map const &vm)
{
	LOG_PRINT_L0("Ryo '" << RYO_RELEASE_NAME << "' (" << RYO_VERSION_FULL << ") Daemonised");
	return t_daemon{vm};
}

bool t_executor::run_non_interactive(
	boost::program_options::variables_map const &vm)
{
	return t_daemon{vm}.run(false);
}

bool t_executor::run_interactive(
	boost::program_options::variables_map const &vm)
{
	return t_daemon{vm}.run(true);
}
}
