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

namespace serialization
{
namespace detail
{
template <typename Archive, class T>
bool serialize_container_element(Archive &ar, T &e)
{
	return ::do_serialize(ar, e);
}

template <typename Archive>
bool serialize_container_element(Archive &ar, uint32_t &e)
{
	ar.serialize_varint(e);
	return true;
}

template <typename Archive>
bool serialize_container_element(Archive &ar, uint64_t &e)
{
	ar.serialize_varint(e);
	return true;
}

template <typename C>
void do_reserve(C &c, size_t N) {}
}
}

template <template <bool> class Archive, typename C>
bool do_serialize_container(Archive<false> &ar, C &v)
{
	size_t cnt;
	ar.begin_array(cnt);
	if(!ar.stream().good())
		return false;
	v.clear();

	// very basic sanity check
	if(ar.remaining_bytes() < cnt)
	{
		ar.stream().setstate(std::ios::failbit);
		return false;
	}

	::serialization::detail::do_reserve(v, cnt);

	for(size_t i = 0; i < cnt; i++)
	{
		if(i > 0)
			ar.delimit_array();
		typename C::value_type e;
		if(!::serialization::detail::serialize_container_element(ar, e))
			return false;
		::serialization::detail::do_add(v, std::move(e));
		if(!ar.stream().good())
			return false;
	}
	ar.end_array();
	return true;
}

template <template <bool> class Archive, typename C>
bool do_serialize_container(Archive<true> &ar, C &v)
{
	size_t cnt = v.size();
	ar.begin_array(cnt);
	for(auto i = v.begin(); i != v.end(); ++i)
	{
		if(!ar.stream().good())
			return false;
		if(i != v.begin())
			ar.delimit_array();
		if(!::serialization::detail::serialize_container_element(ar, const_cast<typename C::value_type &>(*i)))
			return false;
		if(!ar.stream().good())
			return false;
	}
	ar.end_array();
	return true;
}
