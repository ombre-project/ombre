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

#pragma once

#define GET_FIELD_FROM_JSON_RETURN_ON_ERROR(json, name, type, jtype, mandatory, def)  \
	type field_##name = def;                                                          \
	bool field_##name##_found = false;                                                \
	(void)field_##name##_found;                                                       \
	do                                                                                \
		if(json.HasMember(#name))                                                     \
		{                                                                             \
			if(json[#name].Is##jtype())                                               \
			{                                                                         \
				field_##name = json[#name].Get##jtype();                              \
				field_##name##_found = true;                                          \
			}                                                                         \
			else                                                                      \
			{                                                                         \
				LOG_ERROR("Field " << #name << " found in JSON, but not " << #jtype); \
				return false;                                                         \
			}                                                                         \
		}                                                                             \
		else if(mandatory)                                                            \
		{                                                                             \
			LOG_ERROR("Field " << #name << " not found in JSON");                     \
			return false;                                                             \
		}                                                                             \
	while(0)
