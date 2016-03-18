#pragma once

#include <boost/function.hpp>
#include <boost/asio/io_service.hpp>
#include <thread>
#include <atomic>
#include "common.h"

namespace stratum
{
	class miner_pool
	{
	public:
		typedef boost::function<void(uint32_t)> job_callback;

		miner_pool(unsigned thread_num = std::thread::hardware_concurrency());
		~miner_pool();

		void set_job(const binary& blob, double difficulty, job_callback cb);
	private:
		static void calc(const binary& blob, double difficulty, 
			job_callback cb, std::atomic_flag& stop);

		void stop();
		void start();

		boost::asio::io_service io_service_;
		boost::asio::io_service::work working_;
		std::vector<std::thread> pool_;
		unsigned thread_num_;
		std::atomic_flag stop_flag_;
	};
}