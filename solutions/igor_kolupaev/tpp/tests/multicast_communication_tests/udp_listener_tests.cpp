#include "test_registrator.h"

#include <udp_listener.h>

#include <string>
#include <vector>

namespace multicast_communication
{
	namespace tests_
	{
		namespace detail
		{
			void service_thread(boost::asio::io_service& service);
		}

		class message_processor_test : public message_processor
		{
			std::vector<std::string> messages_;

		public:

			std::vector<std::string> messages() const
			{
				return messages_;
			};

			virtual void process_message(const std::string &message)
			{
				messages_.push_back(message);
			};
		};
	}
}

void multicast_communication::tests_::detail::service_thread(boost::asio::io_service& service)
{
	service.run();
}

void multicast_communication::tests_::udp_listener_tests()
{
	BOOST_CHECK_NO_THROW
	(
		message_processor_test mp;
		boost::asio::io_service service;
		udp_listener uw(service, "224.0.0.0", 50000, &mp);
	);

	{
		message_processor_test mp;

		boost::asio::io_service service;
		udp_listener uw(service, "224.0.0.0", 50000, &mp);

		const std::string buffer("\001hello world\003");
		boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string("224.0.0.0"), 50000);
		boost::asio::ip::udp::socket socket(service, endpoint.protocol());
		boost::thread receive_messages(boost::bind(detail::service_thread, boost::ref(service)));
		while (mp.messages().empty())
		{
			socket.send_to(boost::asio::buffer(buffer), endpoint);
			boost::this_thread::sleep_for(boost::chrono::nanoseconds(1));
		}
		service.stop();
		receive_messages.join();
		BOOST_CHECK_EQUAL(strcmp(mp.messages()[0].c_str(), "hello world"), 0);
	}

	{
		message_processor_test mp;

		boost::asio::io_service service;
		udp_listener uw(service, "224.0.0.0", 50000, &mp);

		const std::string buffer("\001hello world\x1fhello1 world1\003");
		boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string("224.0.0.0"), 50000);
		boost::asio::ip::udp::socket socket(service, endpoint.protocol());
		boost::thread receive_messages(boost::bind(detail::service_thread, boost::ref(service)));
		while (mp.messages().empty())
		{
			socket.send_to(boost::asio::buffer(buffer), endpoint);
			boost::this_thread::sleep_for(boost::chrono::nanoseconds(1));
		}
		service.stop();
		receive_messages.join();

		BOOST_CHECK_EQUAL(strcmp(mp.messages()[0].c_str(), "hello world"), 0);
		BOOST_CHECK_EQUAL(strcmp(mp.messages()[1].c_str(), "hello1 world1"), 0);
	}
}
