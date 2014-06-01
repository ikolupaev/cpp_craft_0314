#include "test_registrator.h"

#include "trade_processor.h"
#include "quote_processor.h"

#include <vector>
#include <fstream>
#include <string>

namespace multicast_communication
{
	namespace trade_processor_tests_
	{
		class market_data_processor_test_helper : public market_data_processor
		{
		public:
			explicit market_data_processor_test_helper(){}
			virtual ~market_data_processor_test_helper(){}

			std::vector<quote_message_ptr> quotes;
			std::vector<trade_message_ptr> trades;

		private:
			virtual void new_trade(const trade_message_ptr& trade)
			{
				trades.push_back(trade);
			};

			virtual void new_quote(const quote_message_ptr& quote)
			{
				quotes.push_back(quote);
			};
		};

		void read_message(std::istream &in, std::string &message)
		{
			const char SOH = 0x01;
			const char ETX = 0x03;
			const char US = 0x1f;

			while (in)
			{
				char ch;
				in.read(&ch, 1);

				if (ch == SOH)
				{
					message = "";
					continue;
				}

				if (ch == ETX || ch == US)
				{
					return;
				}

				message += ch;
			}
		}
	}
}

void multicast_communication::tests_::trade_processor_tests()
{
	multicast_communication::trade_processor_tests_::market_data_processor_test_helper p;
	trade_processor processor( p );

	std::ifstream in(SOURCE_DIR "/tests/data/233.200.79.128.udp");

	while (in)
	{
		std::string msg("");

		multicast_communication::trade_processor_tests_::read_message(in, msg);
		processor.process_message(msg);
	}

	in.close();

	BOOST_CHECK_EQUAL(p.trades.size(), 500);
}

void multicast_communication::tests_::quote_processor_tests()
{
	multicast_communication::trade_processor_tests_::market_data_processor_test_helper p;
	quote_processor processor(p);

	std::ifstream in(SOURCE_DIR "/tests/data/233.200.79.0.udp");

	while (in)
	{
		std::string msg("");

		multicast_communication::trade_processor_tests_::read_message(in, msg);
		processor.process_message(msg);
	}

	in.close();

	BOOST_CHECK_EQUAL(p.quotes.size(), 195);
}
