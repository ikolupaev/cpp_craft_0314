#ifndef _MULTICAST_COMMUNICATION_MESSAGE_PROCESSOR_H_
#define _MULTICAST_COMMUNICATION_MESSAGE_PROCESSOR_H_

#include <string>
#include "market_message_header.h"

namespace multicast_communication
{
	class message_processor
	{
		public: 
			virtual void process_message(const std::string &message) = 0;

			void read_header(std::istream &stream, market_message_header &header)
			{
				stream.read(reinterpret_cast<char*>(&header), sizeof(header));
			};
	};
}

#endif