#include "test_registrator.h"

#include "market_message_header.h"
#include "cqs_structures.h"
#include "quote_message.h"

void multicast_communication::tests_::quote_message_tests()
{
	BOOST_CHECK_EQUAL(sizeof(short_quote_message), 58 - sizeof(market_message_header));
	BOOST_CHECK_EQUAL(sizeof(long_quote_message), 102 - sizeof(market_message_header));

	{
		short_quote_message message;

		strcpy(message.SecuritySymbol, "ABC");
		strcpy(message.BidShortPrice, "12345.78");
		strcpy(message.BidSizeUnitsofTrade, "123");
		strcpy(message.OfferShortPrice, "1234.678");
		strcpy(message.OfferSizeinUnitsofTrade, "123");

		quote_message qm(message);

		BOOST_CHECK_EQUAL(qm.security_symbol(), "ABC");
		BOOST_CHECK_EQUAL(qm.bid_price(), 12345.78);
		BOOST_CHECK_EQUAL(qm.bid_volume(), 123);
		BOOST_CHECK_EQUAL(qm.offer_price(), 1234.678);
		BOOST_CHECK_EQUAL(qm.offer_volume(), 123);
	}

	{
		long_quote_message message;

		strcpy(message.SecuritySymbol, "ABC45678901");
		strcpy(message.BidPrice, "12345678.012");
		strcpy(message.BidSizeinUnitsofTrade, "1234567");
		strcpy(message.OfferPrice, "12345678.012");
		strcpy(message.OfferSizeinUnitsofTrade, "1234567");

		quote_message qm(message);

		BOOST_CHECK_EQUAL(qm.security_symbol(), "ABC45678901");
		BOOST_CHECK_EQUAL(qm.bid_price(), 12345678.012);
		BOOST_CHECK_EQUAL(qm.bid_volume(), 1234567);
		BOOST_CHECK_EQUAL(qm.offer_price(), 12345678.012);
		BOOST_CHECK_EQUAL(qm.offer_volume(), 1234567);
	}
}
