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
#include <boost/optional/optional.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/positional_options.hpp>
#include <boost/program_options/variables_map.hpp>

#include "common/command_line.h"

namespace wallet_args
{
command_line::arg_descriptor<std::string> arg_generate_from_json();
command_line::arg_descriptor<std::string> arg_wallet_file();

const char *tr(const char *str);

/*! Processes command line arguments (`argc` and `argv`) using `desc_params`
  and `positional_options`, while adding parameters for log files and
  concurrency. Log file and concurrency arguments are handled, along with basic
  global init for the wallet process.

  \param error_code error code of the parsing process: zero means no errors, else non zero
  \return The list of parsed options, if there are no errors.*/
boost::optional<boost::program_options::variables_map> main(
	int argc, char **argv,
	const char *const usage,
	const char *const notice,
	boost::program_options::options_description desc_params,
	const boost::program_options::positional_options_description &positional_options,
	const std::function<void(const std::string &, bool)> &print,
	const char *default_log_name, int &error_code, bool log_to_console = false);
}
