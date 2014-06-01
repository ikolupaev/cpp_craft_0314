#include <boost/test/test_tools.hpp>

namespace multicast_communication
{
	namespace tests_
	{
		void multicast_communicator_tests();

		void udp_listener_tests();

		void configurator_tests();
		void quote_message_tests();
		void trade_message_tests();

		void trade_processor_tests();
		void quote_processor_tests();

		void market_data_processor_tests();
	}
}
