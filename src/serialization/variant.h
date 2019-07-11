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

/*! \file variant.h
 *
 * \brief for dealing with variants
 *
 * \detailed Variant: OOP Union
 */
#pragma once

#include "serialization.h"
#include <boost/mpl/empty.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/variant.hpp>

/*! \struct variant_serialization_triats
 * 
 * \brief used internally to contain a variant's traits/possible types
 *
 * \detailed see the macro VARIANT_TAG in serialization.h:140
 */
template <class Archive, class T>
struct variant_serialization_traits
{
};

/*! \struct variant_reader
 *
 * \brief reads a variant
 */
template <class Archive, class Variant, class TBegin, class TEnd>
struct variant_reader
{
	typedef typename Archive::variant_tag_type variant_tag_type;
	typedef typename boost::mpl::next<TBegin>::type TNext;
	typedef typename boost::mpl::deref<TBegin>::type current_type;

	// A tail recursive inline function.... okay...
	static inline bool read(Archive &ar, Variant &v, variant_tag_type t)
	{
		if(variant_serialization_traits<Archive, current_type>::get_tag() == t)
		{
			current_type x;
			if(!::do_serialize(ar, x))
			{
				ar.stream().setstate(std::ios::failbit);
				return false;
			}
			v = x;
		}
		else
		{
			// Tail recursive.... but no mutation is going on. Why?
			return variant_reader<Archive, Variant, TNext, TEnd>::read(ar, v, t);
		}
		return true;
	}
};

// This one just fails when you call it.... okay
// So the TEnd parameter must be specified/different from TBegin
template <class Archive, class Variant, class TBegin>
struct variant_reader<Archive, Variant, TBegin, TBegin>
{
	typedef typename Archive::variant_tag_type variant_tag_type;

	static inline bool read(Archive &ar, Variant &v, variant_tag_type t)
	{
		ar.stream().setstate(std::ios::failbit);
		return false;
	}
};

template <template <bool> class Archive, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct serializer<Archive<false>, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>>
{
	typedef boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> variant_type;
	typedef typename Archive<false>::variant_tag_type variant_tag_type;
	typedef typename variant_type::types types;

	static bool serialize(Archive<false> &ar, variant_type &v)
	{
		variant_tag_type t;
		ar.begin_variant();
		ar.read_variant_tag(t);
		if(!variant_reader<Archive<false>, variant_type,
						   typename boost::mpl::begin<types>::type,
						   typename boost::mpl::end<types>::type>::read(ar, v, t))
		{
			ar.stream().setstate(std::ios::failbit);
			return false;
		}
		ar.end_variant();
		return true;
	}
};

template <template <bool> class Archive, BOOST_VARIANT_ENUM_PARAMS(typename T)>
struct serializer<Archive<true>, boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)>>
{
	typedef boost::variant<BOOST_VARIANT_ENUM_PARAMS(T)> variant_type;
	//typedef typename Archive<true>::variant_tag_type variant_tag_type;

	struct visitor : public boost::static_visitor<bool>
	{
		Archive<true> &ar;

		visitor(Archive<true> &a) : ar(a) {}

		template <class T>
		bool operator()(T &rv) const
		{
			ar.begin_variant();
			ar.write_variant_tag(variant_serialization_traits<Archive<true>, T>::get_tag());
			if(!::do_serialize(ar, rv))
			{
				ar.stream().setstate(std::ios::failbit);
				return false;
			}
			ar.end_variant();
			return true;
		}
	};

	static bool serialize(Archive<true> &ar, variant_type &v)
	{
		return boost::apply_visitor(visitor(ar), v);
	}
};
