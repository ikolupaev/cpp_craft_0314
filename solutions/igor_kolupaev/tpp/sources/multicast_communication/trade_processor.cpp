#include "trade_processor.h"

#include <string>
#include <sstream>

#include "market_data_processor.h"

multicast_communication::trade_processor::trade_processor(market_data_processor &p) : processor(p) {}

void multicast_communication::trade_processor::process_message(const std::string &message)
{
	std::stringstream in(message);

	market_message_header header;

	read_header(in, header);

	trade_message_ptr trade_message;

	if (is_short_trade(header))
	{
		trade_message = read_short_message(in);
		processor.new_trade(trade_message);
	}
	else if (is_long_trade(header))
	{
		trade_message = read_long_message(in);
		processor.new_trade(trade_message);
	}
}

bool multicast_communication::trade_processor::is_short_trade(const market_message_header &header) const
{
	return header.MessageType == 'I' && (header.MessageCategory == 'E' || header.MessageCategory == 'L');
}

bool multicast_communication::trade_processor::is_long_trade(const market_message_header &header) const
{
	return header.MessageType == 'B' && (header.MessageCategory == 'B' || header.MessageCategory == 'E' || header.MessageCategory == 'L');
}

multicast_communication::trade_message_ptr multicast_communication::trade_processor::read_short_message(std::istream &stream)
{
	short_trade_message raw_msg;
	stream.read(reinterpret_cast<char*>(&raw_msg), sizeof(raw_msg));

	trade_message_ptr message = trade_message_ptr(new trade_message(raw_msg));
	return message;
}

multicast_communication::trade_message_ptr multicast_communication::trade_processor::read_long_message(std::istream &stream)
{
	long_trade_message raw_msg;
	stream.read(reinterpret_cast<char*>(&raw_msg), sizeof(raw_msg));

	trade_message_ptr message = trade_message_ptr(new trade_message(raw_msg));
	return message;
}

