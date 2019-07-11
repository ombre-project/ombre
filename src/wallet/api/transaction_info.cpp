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

#include "transaction_info.h"

using namespace std;

namespace Ryo
{

TransactionInfo::~TransactionInfo() {}

TransactionInfo::Transfer::Transfer(uint64_t _amount, const string &_address)
	: amount(_amount), address(_address) {}

TransactionInfoImpl::TransactionInfoImpl()
	: m_direction(Direction_Out), m_pending(false), m_failed(false), m_amount(0), m_fee(0), m_blockheight(0), m_subaddrAccount(0), m_timestamp(0), m_confirmations(0), m_unlock_time(0)
{
}

TransactionInfoImpl::~TransactionInfoImpl()
{
}

int TransactionInfoImpl::direction() const
{
	return m_direction;
}

bool TransactionInfoImpl::isPending() const
{
	return m_pending;
}

bool TransactionInfoImpl::isFailed() const
{
	return m_failed;
}

uint64_t TransactionInfoImpl::amount() const
{
	return m_amount;
}

uint64_t TransactionInfoImpl::fee() const
{
	return m_fee;
}

uint64_t TransactionInfoImpl::blockHeight() const
{
	return m_blockheight;
}

std::set<uint32_t> TransactionInfoImpl::subaddrIndex() const
{
	return m_subaddrIndex;
}

uint32_t TransactionInfoImpl::subaddrAccount() const
{
	return m_subaddrAccount;
}

string TransactionInfoImpl::label() const
{
	return m_label;
}

string TransactionInfoImpl::hash() const
{
	return m_hash;
}

std::time_t TransactionInfoImpl::timestamp() const
{
	return m_timestamp;
}

string TransactionInfoImpl::paymentId() const
{
	return m_paymentid;
}

const std::vector<TransactionInfo::Transfer> &TransactionInfoImpl::transfers() const
{
	return m_transfers;
}

uint64_t TransactionInfoImpl::confirmations() const
{
	return m_confirmations;
}

uint64_t TransactionInfoImpl::unlockTime() const
{
	return m_unlock_time;
}

} // namespace
