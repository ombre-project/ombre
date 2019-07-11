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

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/stream_buffer.hpp>

#include "blockchain_db/blockchain_db.h"
#include "cryptonote_basic/cryptonote_basic.h"
#include "cryptonote_basic/cryptonote_boost_serialization.h"
#include "cryptonote_core/blockchain.h"

#include <algorithm>
#include <atomic>
#include <boost/iostreams/copy.hpp>
#include <cstdio>
#include <fstream>

#include "common/command_line.h"
#include "version.h"

#include "blockchain_utilities.h"

using namespace cryptonote;

class BlocksdatFile
{
  public:
	bool store_blockchain_raw(cryptonote::Blockchain *cs, cryptonote::tx_memory_pool *txp,
							  boost::filesystem::path &output_file, uint64_t use_block_height = 0);

  protected:
	Blockchain *m_blockchain_storage;

	std::ofstream *m_raw_data_file;

	// open export file for write
	bool open_writer(const boost::filesystem::path &file_path, uint64_t block_stop);
	bool initialize_file(uint64_t block_stop);
	bool close();
	void write_block(const crypto::hash &block_hash);

  private:
	uint64_t m_cur_height; // tracks current height during export
	std::vector<crypto::hash> m_hashes;
};
