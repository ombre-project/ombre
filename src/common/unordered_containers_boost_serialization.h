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

#include <boost/serialization/split_free.hpp>
#include <unordered_map>
#include <unordered_set>

namespace boost
{
namespace serialization
{
template <class Archive, class h_key, class hval>
inline void save(Archive &a, const std::unordered_map<h_key, hval> &x, const boost::serialization::version_type ver)
{
	size_t s = x.size();
	a << s;
	for(auto &v : x)
	{
		a << v.first;
		a << v.second;
	}
}

template <class Archive, class h_key, class hval>
inline void load(Archive &a, std::unordered_map<h_key, hval> &x, const boost::serialization::version_type ver)
{
	x.clear();
	size_t s = 0;
	a >> s;
	for(size_t i = 0; i != s; i++)
	{
		h_key k;
		hval v;
		a >> k;
		a >> v;
		x.insert(std::pair<h_key, hval>(k, v));
	}
}

template <class Archive, class h_key, class hval>
inline void save(Archive &a, const std::unordered_multimap<h_key, hval> &x, const boost::serialization::version_type ver)
{
	size_t s = x.size();
	a << s;
	for(auto &v : x)
	{
		a << v.first;
		a << v.second;
	}
}

template <class Archive, class h_key, class hval>
inline void load(Archive &a, std::unordered_multimap<h_key, hval> &x, const boost::serialization::version_type ver)
{
	x.clear();
	size_t s = 0;
	a >> s;
	for(size_t i = 0; i != s; i++)
	{
		h_key k;
		hval v;
		a >> k;
		a >> v;
		x.emplace(k, v);
	}
}

template <class Archive, class hval>
inline void save(Archive &a, const std::unordered_set<hval> &x, const boost::serialization::version_type ver)
{
	size_t s = x.size();
	a << s;
	for(auto &v : x)
	{
		a << v;
	}
}

template <class Archive, class hval>
inline void load(Archive &a, std::unordered_set<hval> &x, const boost::serialization::version_type ver)
{
	x.clear();
	size_t s = 0;
	a >> s;
	for(size_t i = 0; i != s; i++)
	{
		hval v;
		a >> v;
		x.insert(v);
	}
}

template <class Archive, class h_key, class hval>
inline void serialize(Archive &a, std::unordered_map<h_key, hval> &x, const boost::serialization::version_type ver)
{
	split_free(a, x, ver);
}

template <class Archive, class h_key, class hval>
inline void serialize(Archive &a, std::unordered_multimap<h_key, hval> &x, const boost::serialization::version_type ver)
{
	split_free(a, x, ver);
}

template <class Archive, class hval>
inline void serialize(Archive &a, std::unordered_set<hval> &x, const boost::serialization::version_type ver)
{
	split_free(a, x, ver);
}
}
}
