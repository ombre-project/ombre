// Copyright (c) 2018, Ryo Currency Project
// Portions copyright (c) 2014-2018, The Monero Project
//
// Portions of this file are available under BSD-3 license. Please see ORIGINAL-LICENSE for details
// All rights reserved.
//
// ombre changes to this code are in public domain. Please note, other licences may apply to the file.
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

#include "include_base_utils.h"

using namespace epee;

#include "checkpoints.h"

#include "common/dns_utils.h"
#include "include_base_utils.h"
#include "serialization/keyvalue_serialization.h"
#include "storages/portable_storage_template_helper.h" // epee json include
#include "string_tools.h"

//#undef RYO_DEFAULT_LOG_CATEGORY
//#define RYO_DEFAULT_LOG_CATEGORY "checkpoints"

namespace cryptonote
{
/**
   * @brief struct for loading a checkpoint from json
   */
struct t_hashline
{
	uint64_t height;  //!< the height of the checkpoint
	std::string hash; //!< the hash for the checkpoint
	BEGIN_KV_SERIALIZE_MAP()
	KV_SERIALIZE(height)
	KV_SERIALIZE(hash)
	END_KV_SERIALIZE_MAP()
};

/**
   * @brief struct for loading many checkpoints from json
   */
struct t_hash_json
{
	std::vector<t_hashline> hashlines; //!< the checkpoint lines from the file
	BEGIN_KV_SERIALIZE_MAP()
	KV_SERIALIZE(hashlines)
	END_KV_SERIALIZE_MAP()
};

//---------------------------------------------------------------------------
checkpoints::checkpoints()
{
}
//---------------------------------------------------------------------------
bool checkpoints::add_checkpoint(uint64_t height, const std::string &hash_str)
{
	crypto::hash h = crypto::null_hash;
	bool r = epee::string_tools::parse_tpod_from_hex_string(hash_str, h);
	CHECK_AND_ASSERT_MES(r, false, "Failed to parse checkpoint hash string into binary representation!");

	// return false if adding at a height we already have AND the hash is different
	if(m_points.count(height))
	{
		CHECK_AND_ASSERT_MES(h == m_points[height], false, "Checkpoint at given height already exists, and hash for new checkpoint was different!");
	}
	m_points[height] = h;
	return true;
}
//---------------------------------------------------------------------------
bool checkpoints::is_in_checkpoint_zone(uint64_t height) const
{
	return !m_points.empty() && (height <= (--m_points.end())->first);
}
//---------------------------------------------------------------------------
bool checkpoints::check_block(uint64_t height, const crypto::hash &h, bool &is_a_checkpoint) const
{
	auto it = m_points.find(height);
	is_a_checkpoint = it != m_points.end();
	if(!is_a_checkpoint)
		return true;

	if(it->second == h)
	{
		MINFO("CHECKPOINT PASSED FOR HEIGHT " << height << " " << h);
		return true;
	}
	else
	{
		MWARNING("CHECKPOINT FAILED FOR HEIGHT " << height << ". EXPECTED HASH: " << it->second << ", FETCHED HASH: " << h);
		return false;
	}
}
//---------------------------------------------------------------------------
bool checkpoints::check_block(uint64_t height, const crypto::hash &h) const
{
	bool ignored;
	return check_block(height, h, ignored);
}
//---------------------------------------------------------------------------
//FIXME: is this the desired behavior?
bool checkpoints::is_alternative_block_allowed(uint64_t blockchain_height, uint64_t block_height) const
{
	if(0 == block_height)
		return false;

	auto it = m_points.upper_bound(blockchain_height);
	// Is blockchain_height before the first checkpoint?
	if(it == m_points.begin())
		return true;

	--it;
	uint64_t checkpoint_height = it->first;
	return checkpoint_height < block_height;
}
//---------------------------------------------------------------------------
uint64_t checkpoints::get_max_height() const
{
	std::map<uint64_t, crypto::hash>::const_iterator highest =
		std::max_element(m_points.begin(), m_points.end(),
						 (boost::bind(&std::map<uint64_t, crypto::hash>::value_type::first, _1) <
						  boost::bind(&std::map<uint64_t, crypto::hash>::value_type::first, _2)));
	return highest->first;
}
//---------------------------------------------------------------------------
const std::map<uint64_t, crypto::hash> &checkpoints::get_points() const
{
	return m_points;
}

bool checkpoints::check_for_conflicts(const checkpoints &other) const
{
	for(auto &pt : other.get_points())
	{
		if(m_points.count(pt.first))
		{
			CHECK_AND_ASSERT_MES(pt.second == m_points.at(pt.first), false, "Checkpoint at given height already exists, and hash for new checkpoint was different!");
		}
	}
	return true;
}

bool checkpoints::init_default_checkpoints(network_type nettype)
{
	if(nettype == TESTNET)
	{
		return true;
	}
	if(nettype == STAGENET)
	{
		return true;
	}
	else
	{
		ADD_CHECKPOINT(1,   "70993660d8935714ccc7f5ffbb2a270954b38033e1288e72846a8ac23c674d3b");
		ADD_CHECKPOINT(10,  "370ef03bafc23e96cc3b8075d9b11d637363a87d6961e6a0497ec32cecb46750");
		ADD_CHECKPOINT(100, "b31ac0e238926c24a209479e9d85f2567cd80402efa3ff7ffa074ac979e687d5");
		ADD_CHECKPOINT(200, "32b2909e2d2b82c7cdfea6284152ca2f29475bfeddaf1e3b040d470c369c7016");
		ADD_CHECKPOINT(500, "4c8af01873e68644eca9334c2407387988d9ccf731519516c0512b59da53319b");
		ADD_CHECKPOINT(10000, "9d923965202d3f10d78417ff1468b5036812f8eb7c694683f2e26cb67a9e11b2");
		ADD_CHECKPOINT(20000, "1eba0557e26eed29e68226b1228211ea4f91aa32337c46d6c85a995a7c38ff17");
		ADD_CHECKPOINT(50000, "8a308882d1888890d61b294c328f895f9447935f78391879b59b614e28749bcc");
		ADD_CHECKPOINT(58500, "8a52ec5f274b7a5ee9e29dbb38178785de4fa654fc8e86a832ef5ae7c371fb9d");
		ADD_CHECKPOINT(80000, "c6b1c3602b12648b43da2ff34813ac1c6c85774178384c37c8cf516934296d0d");
		ADD_CHECKPOINT(130000, "bd21eb916acc4e7bf7f5a3f3dbad3615e569251808ade00179741c7f282e77b0");
		ADD_CHECKPOINT(180000, "ff52af1b221cac6985e998f1560b38176382d5c72468b5e83aa8448b1b3e8744");
		ADD_CHECKPOINT(230000, "b0d7671a414e70e9e598cf93df202fbb95324b10bab3486105050c4bdb572de6");
		ADD_CHECKPOINT(280000, "22f0f0a98a0c22be76efb4c210c91943384fcc467d43b8088233144e08f4eaa7");
		ADD_CHECKPOINT(330000, "a85a08a366a4f0a0216092f01b4ffe24c928c021680f2cff2ed313e348b7d1a4");
		ADD_CHECKPOINT(380000, "e2801fcd55d0e3e6804e530d9dfe1ebcdde5c8b9dbb128f88841c6145bd0e13f");
		ADD_CHECKPOINT(430000, "a7db947c7c30f9a5255f04f5b6ca89d5f9c807c176dd7327189231e94580c931");
		ADD_CHECKPOINT(480000, "51b78c46bbda72c93f883155db846aa48ed67140d6bfc343ecd6350d1dd22ecc");
		ADD_CHECKPOINT(530000, "1b033ed106a0300b6682a9d2ce04c81cb5f026f096250abdc3922c13b9a6a5fc");
		ADD_CHECKPOINT(580000, "1910ed4a460d19dcd365fc0fb48da08efd5bb43406803d14546244d3f66027f5");
		ADD_CHECKPOINT(630000, "3b57b158a9e10c0150767e19fec09daf561da0578533a8d25f6142d786bc856f");
		ADD_CHECKPOINT(680000, "01a174b66bce597acca9a025f2c41bed083359d0d129532894a623eeeb6bd9c6");
		ADD_CHECKPOINT(730000, "c1c9e81479a2fca351fc8ac2c88df5b890c88cb61de322d9acd4f14c27d00da1");
	}

	return true;
}

bool checkpoints::load_checkpoints_from_json(const std::string &json_hashfile_fullpath)
{
	boost::system::error_code errcode;
	if(!(boost::filesystem::exists(json_hashfile_fullpath, errcode)))
	{
		LOG_PRINT_L1("Blockchain checkpoints file not found");
		return true;
	}

	LOG_PRINT_L1("Adding checkpoints from blockchain hashfile");

	uint64_t prev_max_height = get_max_height();
	LOG_PRINT_L1("Hard-coded max checkpoint height is " << prev_max_height);
	t_hash_json hashes;
	if(!epee::serialization::load_t_from_json_file(hashes, json_hashfile_fullpath))
	{
		MERROR("Error loading checkpoints from " << json_hashfile_fullpath);
		return false;
	}
	for(std::vector<t_hashline>::const_iterator it = hashes.hashlines.begin(); it != hashes.hashlines.end();)
	{
		uint64_t height;
		height = it->height;
		if(height <= prev_max_height)
		{
			LOG_PRINT_L1("ignoring checkpoint height " << height);
		}
		else
		{
			std::string blockhash = it->hash;
			LOG_PRINT_L1("Adding checkpoint height " << height << ", hash=" << blockhash);
			ADD_CHECKPOINT(height, blockhash);
		}
		++it;
	}

	return true;
}

bool checkpoints::load_checkpoints_from_dns(network_type nettype)
{
	return true; //Temporarily disabled

	std::vector<std::string> records;

	// All four MoneroPulse domains have DNSSEC on and valid
	static const std::vector<std::string> dns_urls = {"checkpoints.moneropulse.se", "checkpoints.moneropulse.org", "checkpoints.moneropulse.net", "checkpoints.moneropulse.co"};

	static const std::vector<std::string> testnet_dns_urls = {"testpoints.moneropulse.se", "testpoints.moneropulse.org", "testpoints.moneropulse.net", "testpoints.moneropulse.co"};

	static const std::vector<std::string> stagenet_dns_urls = {"stagenetpoints.moneropulse.se", "stagenetpoints.moneropulse.org", "stagenetpoints.moneropulse.net", "stagenetpoints.moneropulse.co"};

	if(!tools::dns_utils::load_txt_records_from_dns(records, nettype == TESTNET ? testnet_dns_urls : nettype == STAGENET ? stagenet_dns_urls : dns_urls))
		return true; // why true ?

	for(const auto &record : records)
	{
		auto pos = record.find(":");
		if(pos != std::string::npos)
		{
			uint64_t height;
			crypto::hash hash;

			// parse the first part as uint64_t,
			// if this fails move on to the next record
			std::stringstream ss(record.substr(0, pos));
			if(!(ss >> height))
			{
				continue;
			}

			// parse the second part as crypto::hash,
			// if this fails move on to the next record
			std::string hashStr = record.substr(pos + 1);
			if(!epee::string_tools::parse_tpod_from_hex_string(hashStr, hash))
			{
				continue;
			}

			ADD_CHECKPOINT(height, hashStr);
		}
	}
	return true;
}

bool checkpoints::load_new_checkpoints(const std::string &json_hashfile_fullpath, network_type nettype, bool dns)
{
	bool result;

	result = load_checkpoints_from_json(json_hashfile_fullpath);
	if(dns)
	{
		result &= load_checkpoints_from_dns(nettype);
	}

	return result;
}
}
