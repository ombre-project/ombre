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

#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <cstddef>
#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

namespace tools
{
//! A global thread pool
class threadpool
{
  public:
	static threadpool &getInstance()
	{
		static threadpool instance;
		return instance;
	}

	// The waiter lets the caller know when all of its
	// tasks are completed.
	class waiter
	{
		boost::mutex mt;
		boost::condition_variable cv;
		int num;

	  public:
		void inc();
		void dec();
		void wait(); //! Wait for a set of tasks to finish.
		waiter() : num(0) {}
		~waiter();
	};

	// Submit a task to the pool. The waiter pointer may be
	// NULL if the caller doesn't care to wait for the
	// task to finish.
	void submit(waiter *waiter, std::function<void()> f);

	int get_max_concurrency();

  private:
	threadpool();
	~threadpool();
	typedef struct entry
	{
		waiter *wo;
		std::function<void()> f;
	} entry;
	std::deque<entry> queue;
	boost::condition_variable has_work;
	boost::mutex mutex;
	std::vector<boost::thread> threads;
	int active;
	int max;
	bool running;
	void run();
};
}
