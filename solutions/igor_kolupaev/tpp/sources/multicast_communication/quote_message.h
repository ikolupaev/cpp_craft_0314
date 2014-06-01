#ifndef _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
#define _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_

#include <boost/shared_ptr.hpp>
#include "market_message_header.h"
#include "cqs_structures.h"

namespace multicast_communication
{
	class quote_message
	{
		std::string security_symbol_;
		double bid_price_;
		double bid_volume_;
		double offer_price_;
		double offer_volume_;

	public:
		std::string security_symbol() const;
		double bid_price() const;
		double bid_volume() const;
		double offer_price() const;
		double offer_volume() const;

		quote_message(const short_quote_message &msg);
		quote_message(const long_quote_message &msg);
	};

	typedef boost::shared_ptr< quote_message > quote_message_ptr;
}

#endif // _MULTICAST_COMMUNICATION_QUOTE_MESSAGE_H_
