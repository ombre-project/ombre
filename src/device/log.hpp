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

#include <cstddef>
#include <string>

#include "crypto/crypto.h"
#include "cryptonote_basic/account.h"
#include "ringct/rctOps.h"

#include "device.hpp"

namespace hw
{

#ifdef WITH_DEVICE_LEDGER
namespace ledger
{

void buffer_to_str(char *to_buff, size_t to_len, const char *buff, size_t len);
void log_hexbuffer(std::string msg, const char *buff, size_t len);
void log_message(std::string msg, std::string info);
#ifdef DEBUG_HWDEVICE
#define TRACK printf("file %s:%d\n", __FILE__, __LINE__)
//#define TRACK MCDEBUG("ledger"," At file " << __FILE__ << ":" << __LINE__)
//#define TRACK while(0);

void decrypt(char *buf, size_t len);
crypto::key_derivation decrypt(const crypto::key_derivation &derivation);
cryptonote::account_keys decrypt(const cryptonote::account_keys &keys);
crypto::secret_key decrypt(const crypto::secret_key &sec);
rct::key decrypt(const rct::key &sec);
crypto::ec_scalar decrypt(const crypto::ec_scalar &res);
rct::keyV decrypt(const rct::keyV &keys);

void check32(std::string msg, std::string info, const char *h, const char *d, bool crypted = false);
void check8(std::string msg, std::string info, const char *h, const char *d, bool crypted = false);

void set_check_verbose(bool verbose);
#endif
}
#endif
}
