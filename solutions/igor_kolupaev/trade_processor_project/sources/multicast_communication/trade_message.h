#ifndef _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_

#include <string>
#include <boost/shared_ptr.hpp>
#include "cts_structures.h"

namespace multicast_communication
{
	class trade_message
	{
		std::string security_symbol_;
		double price_;
		double volume_;

	public:
		trade_message(short_trade_message msg);
		trade_message(long_trade_message msg);

		std::string security_symbol() const;
		double price() const;
		double volume() const;
	};

	typedef boost::shared_ptr< trade_message > trade_message_ptr;
}

#endif // _MULTICAST_COMMUNICATION_TRADE_MESSAGE_H_
