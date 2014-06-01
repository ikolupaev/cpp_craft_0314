#ifndef _MULTICAST_COMMUNICATION_TRADE_PROCESSOR_H_
#define _MULTICAST_COMMUNICATION_TRADE_PROCESSOR_H_

#include <string>
#include <iostream>

#include "message_processor.h"
#include "market_data_processor.h"
#include "market_message_header.h"
#include "cts_structures.h"

namespace multicast_communication
{
	class trade_processor : public message_processor
	{
		market_data_processor &processor;

		bool is_short_trade(const market_message_header &header) const;
		bool is_long_trade(const market_message_header &header) const;
		trade_message_ptr read_short_message(std::istream &stream);
		trade_message_ptr read_long_message(std::istream &stream);

	public:
		trade_processor(market_data_processor &p);
		virtual void process_message(const std::string &message);
	};
}
#endif