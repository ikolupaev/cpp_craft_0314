#include <fstream>

#include <boost\thread.hpp>
#include <system_processor.h>

#include "fconfigurator.h"
#include "multicast_communicator.h"
#include "market_data_processor.h"

using namespace multicast_communication;

class text_dump_processor : public market_data_processor
{
	std::ofstream out_;
	mutable boost::mutex output_mutex_;

	virtual void new_trade(const trade_message_ptr &msg)
	{
		boost::mutex::scoped_lock lock(output_mutex_);

		out_ << "T " << msg->security_symbol() << " "
			 << msg->price() << " "
			 << msg->volume() << std::endl;
	}

	virtual void new_quote(const quote_message_ptr& msg)
	{
		boost::mutex::scoped_lock lock(output_mutex_);

		out_ << "T " << msg->security_symbol() << " "
			 << msg->bid_price() << " "
			 << msg->bid_volume() << " "
			 << msg->offer_price() << " "
			 << msg->offer_volume() << std::endl;
	}

public:
	
	explicit text_dump_processor(char *output_path) : out_(output_path)
	{

	}

	virtual ~text_dump_processor()
	{
		out_.close();
	}
};

class mediator
{
	market_data_processor *processor;
	multicast_communicator *communicator;

public:

	explicit mediator() 
	{

		configurator *config = new fconfigurator("c:\\users\\igor\\config.ini");
		processor = new text_dump_processor("c:\\users\\igor\\output.txt");

		communicator = new multicast_communicator(*config, *processor);
	};

	void stop()
	{
		communicator->signal_to_stop();
		communicator->join();
	}

	virtual ~mediator()
	{
		delete communicator;
	}
};

BOOL CtrlHandler(DWORD fdwCtrlType)
{
	return 1;
}

int main( int argc, char *argv[] )
{
	using namespace system_utilities::common;
	system_processor::sp sp_ptr = system_processor::init(argc, argv, NULL);

	mediator m;
	sp_ptr->wait_for_stop();
	m.stop();

	return 0;
}
