#ifndef _MULTICAST_COMMUNICATION_MULTICAST_COMMUNICATOR_H_
#define _MULTICAST_COMMUNICATION_MULTICAST_COMMUNICATOR_H_

#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include "market_data_processor.h"
#include "trade_processor.h"
#include "quote_processor.h"
#include "configurator.h"
#include "udp_listener.h"

namespace multicast_communication
{
	class multicast_communicator : virtual private boost::noncopyable
	{
	private:
		const size_t trade_thread_size;
		const size_t quote_thread_size;

		const cta_ports_vector &trade_ports;
		const cta_ports_vector &quote_ports;

		market_data_processor &processor;

		boost::thread_group trade_threads;
		boost::thread_group quote_threads;

		boost::thread *communication_thread;

		trade_processor trade_processor_instance;
		quote_processor quote_processor_instance;

		boost::asio::io_service service_;
		void service_run(boost::asio::io_service *service);

	public:
		multicast_communicator(const configurator &config, market_data_processor &processor);

		void signal_to_stop();
		void join();
	};
}

#endif