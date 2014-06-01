#ifndef _MULTICAST_COMMUNICATION_CONFIGURATOR_H_
#define _MULTICAST_COMMUNICATION_CONFIGURATOR_H_

#include <vector>

#include "cta_ports_vector.h"

namespace multicast_communication
{
	class configurator
	{
	public:
		virtual const size_t trade_thread_size() const = 0;
		virtual const size_t quote_thread_size() const = 0;
		virtual const cta_ports_vector &trade_ports() const = 0;
		virtual const cta_ports_vector &quote_ports() const = 0;

		explicit configurator() {}
		virtual ~configurator() {}
	};
}

#endif