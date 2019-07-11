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

#pragma once
#include "serialization.h"
#include <memory>

namespace serialization
{
namespace detail
{
template <typename Archive, class T>
bool serialize_pair_element(Archive &ar, T &e)
{
	return ::do_serialize(ar, e);
}

template <typename Archive>
bool serialize_pair_element(Archive &ar, uint64_t &e)
{
	ar.serialize_varint(e);
	return true;
}
}
}

template <template <bool> class Archive, class F, class S>
inline bool do_serialize(Archive<false> &ar, std::pair<F, S> &p)
{
	size_t cnt;
	ar.begin_array(cnt);
	if(!ar.stream().good())
		return false;
	if(cnt != 2)
		return false;

	if(!::serialization::detail::serialize_pair_element(ar, p.first))
		return false;
	if(!ar.stream().good())
		return false;
	ar.delimit_array();
	if(!::serialization::detail::serialize_pair_element(ar, p.second))
		return false;
	if(!ar.stream().good())
		return false;

	ar.end_array();
	return true;
}

template <template <bool> class Archive, class F, class S>
inline bool do_serialize(Archive<true> &ar, std::pair<F, S> &p)
{
	ar.begin_array(2);
	if(!ar.stream().good())
		return false;
	if(!::serialization::detail::serialize_pair_element(ar, p.first))
		return false;
	if(!ar.stream().good())
		return false;
	ar.delimit_array();
	if(!::serialization::detail::serialize_pair_element(ar, p.second))
		return false;
	if(!ar.stream().good())
		return false;
	ar.end_array();
	return true;
}
