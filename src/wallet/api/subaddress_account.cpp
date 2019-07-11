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

#include "subaddress_account.h"
#include "common_defines.h"
#include "crypto/hash.h"
#include "wallet.h"
#include "wallet/wallet2.h"

#include <vector>

namespace Ryo
{

SubaddressAccount::~SubaddressAccount() {}

SubaddressAccountImpl::SubaddressAccountImpl(WalletImpl *wallet)
	: m_wallet(wallet) {}

void SubaddressAccountImpl::addRow(const std::string &label)
{
	m_wallet->m_wallet->add_subaddress_account(label);
	refresh();
}

void SubaddressAccountImpl::setLabel(uint32_t accountIndex, const std::string &label)
{
	m_wallet->m_wallet->set_subaddress_label({accountIndex, 0}, label);
	refresh();
}

void SubaddressAccountImpl::refresh()
{
	LOG_PRINT_L2("Refreshing subaddress account");

	clearRows();
	for(uint32_t i = 0; i < m_wallet->m_wallet->get_num_subaddress_accounts(); ++i)
	{
		m_rows.push_back(new SubaddressAccountRow(
			i,
			m_wallet->m_wallet->get_subaddress_as_str({i, 0}).substr(0, 6),
			m_wallet->m_wallet->get_subaddress_label({i, 0}),
			cryptonote::print_money(m_wallet->m_wallet->balance(i)),
			cryptonote::print_money(m_wallet->m_wallet->unlocked_balance(i))));
	}
}

void SubaddressAccountImpl::clearRows()
{
	for(auto r : m_rows)
	{
		delete r;
	}
	m_rows.clear();
}

std::vector<SubaddressAccountRow *> SubaddressAccountImpl::getAll() const
{
	return m_rows;
}

SubaddressAccountImpl::~SubaddressAccountImpl()
{
	clearRows();
}

} // namespace
