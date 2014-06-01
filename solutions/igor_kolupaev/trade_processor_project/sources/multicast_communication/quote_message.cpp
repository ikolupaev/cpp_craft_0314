#include "quote_message.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

multicast_communication::quote_message::quote_message(const short_quote_message &msg)
{
	security_symbol_ = std::string(msg.SecuritySymbol, sizeof(msg.SecuritySymbol));
	boost::algorithm::trim(security_symbol_);

	bid_price_ = boost::lexical_cast<double>(std::string(msg.BidShortPrice, sizeof(msg.BidShortPrice)));
	bid_volume_ = boost::lexical_cast<double>(std::string(msg.BidSizeUnitsofTrade, sizeof(msg.BidSizeUnitsofTrade)));
	offer_price_ = boost::lexical_cast<double>(std::string(msg.OfferShortPrice, sizeof(msg.OfferShortPrice)));
	offer_volume_ = boost::lexical_cast<double>(std::string(msg.OfferSizeinUnitsofTrade, sizeof(msg.OfferSizeinUnitsofTrade)));
}

multicast_communication::quote_message::quote_message(const long_quote_message &msg)
{
	security_symbol_ = std::string(msg.SecuritySymbol, sizeof(msg.SecuritySymbol));
	boost::algorithm::trim(security_symbol_);

	bid_price_ = boost::lexical_cast<double>(std::string(msg.BidPrice, sizeof(msg.BidPrice)));
	bid_volume_ = boost::lexical_cast<double>(std::string(msg.BidSizeinUnitsofTrade, sizeof(msg.BidSizeinUnitsofTrade)));
	offer_price_ = boost::lexical_cast<double>(std::string(msg.OfferPrice, sizeof(msg.OfferPrice)));
	offer_volume_ = boost::lexical_cast<double>(std::string(msg.OfferSizeinUnitsofTrade, sizeof(msg.OfferSizeinUnitsofTrade)));
}

std::string multicast_communication::quote_message::security_symbol() const
{
	return security_symbol_;
}

double multicast_communication::quote_message::bid_price() const
{
	return bid_price_;
}

double multicast_communication::quote_message::bid_volume() const
{
	return bid_volume_;
}

double multicast_communication::quote_message::offer_price() const
{
	return offer_price_;
}

double multicast_communication::quote_message::offer_volume() const
{
	return offer_volume_;
}
