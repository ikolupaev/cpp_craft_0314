#include "test_registrator.h"

#include "market_message_header.h"
#include "trade_message.h"

void multicast_communication::tests_::trade_message_tests()
{
	BOOST_CHECK_EQUAL(sizeof(market_message_header), 24);
	BOOST_CHECK_EQUAL(sizeof(short_trade_message), 44 - sizeof(market_message_header));
	BOOST_CHECK_EQUAL(sizeof(long_trade_message), 82 - sizeof(market_message_header));

	{
		short_trade_message message;

		strcpy(message.SecuritySymbol, "ABC");
		strcpy(message.TradePrice, "12345.78");
		strcpy(message.TradeVolume, "1234");

		trade_message tm(message);

		BOOST_CHECK_EQUAL(tm.security_symbol(), "ABC");
		BOOST_CHECK_EQUAL(tm.price(), 12345.78);
		BOOST_CHECK_EQUAL(tm.volume(), 1234.0);
	}

	{
		long_trade_message message;

		strcpy(message.SecuritySymbol, "12345678901");
		strcpy(message.TradePrice, "12345.789012");
		strcpy(message.TradeVolume, "123456789");

		trade_message tm(message);

		BOOST_CHECK_EQUAL(tm.security_symbol(), "12345678901");
		BOOST_CHECK_EQUAL(tm.price(), 12345.789012);
		BOOST_CHECK_EQUAL(tm.volume(), 123456789);
	}
}
