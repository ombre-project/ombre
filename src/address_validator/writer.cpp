// Copyright (c) 2018, Ombre Cryptocurrency Project
// Copyright (c) 2018, Ryo Currency Project
// Portions copyright (c) 2014-2018, The Monero Project
//
// Portions of this file are available under BSD-3 license. Please see ORIGINAL-LICENSE for details
// All rights reserved.
//
// Ombre changes to this code are in public domain. Please note, other licences may apply to the file.
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

#include "address_validator/writer.h"

#include <algorithm>
#include <cctype>
#include <string>

/*!
 * \namespace cryptonote
 * \brief Holds cryptonote related classes and helpers.
 */
namespace cryptonote
{
//----------------------------------------------------------------------------------------------------
// overloaded method to remove spaces within the string
template <>
writer &writer::operator<<(const std::string &value)
{
	if(!m_remove_spaces)
		print(value);
	else
	{
		std::string tmp = value;
		tmp.erase(std::remove_if(tmp.begin(), tmp.end(), ::isspace), tmp.end());
		print(tmp);
	}
	return *this;
}

//----------------------------------------------------------------------------------------------------
writer &writer::operator<<(const char *value)
{
	// call string method to filter out spaces if needed
	this->operator<<(std::string(value));
	return *this;
}

//----------------------------------------------------------------------------------------------------
writer &writer::operator<<(const char value)
{
	// call string method to filter out spaces if needed
	this->operator<<(std::string(1, value));
	return *this;
}
}
