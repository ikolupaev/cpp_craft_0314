#ifndef _MULTICAST_COMMUNICATION_QUOTE_PROCESSOR_H_
#define _MULTICAST_COMMUNICATION_QUOTE_PROCESSOR_H_

#include <string>

#include "message_processor.h"
#include "market_data_processor.h"

namespace multicast_communication
{
	class quote_processor : public message_processor
	{
		market_data_processor &processor;

		bool is_short_quote(const market_message_header &header) const;
		bool is_long_quote(const market_message_header &header) const;
		quote_message_ptr read_short_message(std::istream &stream);
		quote_message_ptr read_long_message(std::istream &stream);

	public:
		quote_processor(market_data_processor &p);
		virtual void process_message(const std::string &message);
	};
}
#endif