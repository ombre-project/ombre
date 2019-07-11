// Copyright (c) 2018, Ryo Currency Project 
//
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

#include <inttypes.h>

struct prng_handle;

class prng
{
public:
	prng() {}
	~prng();

	/**
	* @brief Generate cryptographic grade random numbers
	*
	* @param output output pointer
	* @param size_bytes output size
	*/

	void generate_random(uint8_t* output, size_t size_bytes);
	inline void generate_random(void* output, size_t size_bytes) { generate_random(reinterpret_cast<uint8_t*>(output), size_bytes); }

	/**
	* @brief Get singleton instance. One instance exists per thread.
	* 
	* @return Singleton reference
	*/

	inline static prng& inst()
	{
		static thread_local prng inst;
		return inst;
	}

private:
	// This stops us from allocating system resources earlier than needed
	void start();
	void generate_system_random_bytes(uint8_t* result, size_t n);
	prng_handle* hnd = nullptr;
};
