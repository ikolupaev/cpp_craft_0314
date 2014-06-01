#ifndef _MULTICAST_COMMUNICATION_UDP_LISTENER_H_
#define _MULTICAST_COMMUNICATION_UDP_LISTENER_H_

#include <string>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "message_processor.h"

namespace multicast_communication
{
	class udp_listener: virtual private boost::noncopyable
	{
		static const size_t default_buffer_size;

		boost::asio::io_service& io_service_;

		boost::asio::ip::udp::endpoint listen_endpoint_;
		boost::asio::ip::udp::socket socket_;

		std::string multicast_address_;

		typedef boost::shared_ptr< std::string > buffer_type;

		message_processor *processor_;

		mutable boost::mutex protect_messages_;

	public:
		explicit udp_listener( boost::asio::io_service& io_service, const std::string& multicast_address, unsigned short port, message_processor *processor );
		~udp_listener();
		const std::vector< std::string > messages() const;
	private:
		void socket_reload_();
		void register_listen_( buffer_type pre_buffer = buffer_type(), const size_t previous_size = 0 );
		void listen_handler_( buffer_type bt, const boost::system::error_code& error, const size_t bytes_received );
		static void enlarge_buffer_( buffer_type& bt );

		void read_message(std::istream &in, std::string &message);
	};
}

#endif // _MULTICAST_COMMUNICATION_UDP_LISTENER_H_
