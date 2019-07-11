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

#include "wallet/api/wallet2_api.h"
#include "wallet/wallet2.h"

namespace Ryo
{

class WalletImpl;

class AddressBookImpl : public AddressBook
{
  public:
	AddressBookImpl(WalletImpl *wallet);
	~AddressBookImpl();

	// Fetches addresses from Wallet2
	void refresh();
	std::vector<AddressBookRow *> getAll() const;
	bool addRow(const std::string &dst_addr, const std::string &payment_id, const std::string &description);
	bool deleteRow(std::size_t rowId);

	// Error codes. See AddressBook:ErrorCode enum in wallet2_api.h
	std::string errorString() const { return m_errorString; }
	int errorCode() const { return m_errorCode; }

	int lookupPaymentID(const std::string &payment_id) const;

  private:
	void clearRows();
	void clearStatus();

  private:
	WalletImpl *m_wallet;
	std::vector<AddressBookRow *> m_rows;
	std::string m_errorString;
	int m_errorCode;
};
}
