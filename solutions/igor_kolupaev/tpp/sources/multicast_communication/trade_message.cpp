#include "trade_message.h"

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

multicast_communication::trade_message::trade_message(short_trade_message msg)
{
	security_symbol_ = std::string(msg.SecuritySymbol, sizeof(msg.SecuritySymbol));
	boost::algorithm::trim(security_symbol_);

	price_ = boost::lexical_cast<double>(std::string(msg.TradePrice, sizeof(msg.TradePrice)));
	volume_ = boost::lexical_cast<double>(std::string(msg.TradeVolume, sizeof(msg.TradeVolume)));
}

multicast_communication::trade_message::trade_message(long_trade_message msg)
{
	security_symbol_ = std::string(msg.SecuritySymbol, sizeof(msg.SecuritySymbol));
	boost::algorithm::trim(security_symbol_);

	price_ = boost::lexical_cast<double>(std::string(msg.TradePrice, sizeof(msg.TradePrice)));
	volume_ = boost::lexical_cast<double>(std::string(msg.TradeVolume, sizeof(msg.TradeVolume)));
}

std::string multicast_communication::trade_message::security_symbol() const
{
	return security_symbol_;
}

double multicast_communication::trade_message::price() const
{
	return price_;
}

double multicast_communication::trade_message::volume() const
{
	return volume_;
}
