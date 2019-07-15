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
// Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers

#pragma once
#include "serialization.h"
#include <memory>

template <template <bool> class Archive>
inline bool do_serialize(Archive<false> &ar, std::string &str)
{
	size_t size = 0;
	ar.serialize_varint(size);
	if(ar.remaining_bytes() < size)
	{
		ar.stream().setstate(std::ios::failbit);
		return false;
	}

	std::unique_ptr<std::string::value_type[]> buf(new std::string::value_type[size]);
	ar.serialize_blob(buf.get(), size);
	str.erase();
	str.append(buf.get(), size);
	return true;
}

template <template <bool> class Archive>
inline bool do_serialize(Archive<true> &ar, std::string &str)
{
	size_t size = str.size();
	ar.serialize_varint(size);
	ar.serialize_blob(const_cast<std::string::value_type *>(str.c_str()), size);
	return true;
}
