#include <boost/asio.hpp>

#include "multicast_communicator.h"
#include "udp_listener.h"

multicast_communication::multicast_communicator::multicast_communicator(
	const configurator &config,
	market_data_processor &market_processor)

	:trade_thread_size(config.trade_thread_size()),
	quote_thread_size(config.trade_thread_size()),
	trade_ports(config.trade_ports()),
	quote_ports(config.quote_ports()),
	processor(market_processor),
	trade_processor_instance(market_processor),
	quote_processor_instance(market_processor)
{
	for (auto port : trade_ports)
	{
		udp_listener *listener = new udp_listener(service_, port.first, port.second, &trade_processor_instance);
	}

	for (auto port : quote_ports)
	{
		udp_listener *listener = new udp_listener(service_, port.first, port.second, &quote_processor_instance);
	}

	communication_thread = new boost::thread(&multicast_communication::multicast_communicator::service_run, this, &service_);

}

void multicast_communication::multicast_communicator::service_run(boost::asio::io_service *service)
{
	service_.run();
}

void multicast_communication::multicast_communicator::signal_to_stop()
{
	service_.stop();
}

void multicast_communication::multicast_communicator::join()
{
	quote_threads.join_all();
	trade_threads.join_all();
}
