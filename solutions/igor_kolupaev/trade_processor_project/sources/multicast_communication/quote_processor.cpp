#include "quote_processor.h"

#include <string>
#include <sstream>

#include "market_data_processor.h"

multicast_communication::quote_processor::quote_processor(market_data_processor &p) : processor(p) {}

void multicast_communication::quote_processor::process_message(const std::string &message)
{
	std::stringstream in(message);

	market_message_header header;

	read_header(in, header);

	quote_message_ptr quote_message;

	if (is_short_quote(header))
	{
		quote_message = read_short_message(in);
		processor.new_quote(quote_message);
	}
	else if (is_long_quote(header))
	{
		quote_message = read_long_message(in);
		processor.new_quote(quote_message);
	}
}

bool multicast_communication::quote_processor::is_short_quote(const market_message_header &header) const
{
	return header.MessageType == 'I' && (header.MessageCategory == 'E' || header.MessageCategory == 'L');
}

bool multicast_communication::quote_processor::is_long_quote(const market_message_header &header) const
{
	return header.MessageType == 'B' && (header.MessageCategory == 'B' || header.MessageCategory == 'E' || header.MessageCategory == 'L');
}

multicast_communication::quote_message_ptr multicast_communication::quote_processor::read_short_message(std::istream &stream)
{
	short_quote_message raw_msg;
	stream.read(reinterpret_cast<char*>(&raw_msg), sizeof(raw_msg));

	quote_message_ptr message = quote_message_ptr(new quote_message(raw_msg));
	return message;
}

multicast_communication::quote_message_ptr multicast_communication::quote_processor::read_long_message(std::istream &stream)
{
	long_quote_message raw_msg;
	stream.read(reinterpret_cast<char*>(&raw_msg), sizeof(raw_msg));

	quote_message_ptr message = quote_message_ptr(new quote_message(raw_msg));
	return message;
}

