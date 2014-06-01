#include "test_registrator.h"
#include "multicast_communicator.h"

namespace multicast_communication
{
	namespace tests_
	{
		class config_test_helper: public virtual configurator
		{
		public:
			config_test_helper() {};

			virtual const size_t trade_thread_size() const
			{
				return 1;
			};

			virtual const size_t quote_thread_size() const
			{
				return 1;
			};

			virtual const cta_ports_vector& trade_ports() const
			{
				cta_ports_vector v;
				v.push_back( cta_socket( "233.200.79.0", 61000 ) );
			
				return v;
			};

			virtual const cta_ports_vector& quote_ports() const
			{
				cta_ports_vector v;
				v.push_back( cta_socket( "233.200.79.128", 62128 ) );

				return v;
			};
		};

		class market_data_processor_comm_test_helper: public virtual market_data_processor
		{
		public:
			explicit market_data_processor_comm_test_helper() {}
			virtual ~market_data_processor_comm_test_helper() {}
		private:
			virtual void new_trade(const trade_message_ptr&) {}
			virtual void new_quote(const quote_message_ptr&) {}
		};
	}
}



void multicast_communication::tests_::multicast_communicator_tests()
{
	config_test_helper config;
	market_data_processor_comm_test_helper processor;

	multicast_communicator comm( config, processor );
}