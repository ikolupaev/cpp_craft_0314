#ifndef _MULTICAST_COMMUNICATION_FCONFIGURATOR_H_
#define _MULTICAST_COMMUNICATION_FCONFIGURATOR_H_

#include <vector>

#include "configurator.h"
#include "cta_ports_vector.h"

namespace multicast_communication
{
	class fconfigurator: configurator
	{
		size_t trade_thread_size_;
		size_t quote_thread_size_;
		cta_ports_vector trade_ports_;
		cta_ports_vector quote_ports_;

		void skip_endl( std::istream &in );
		void read_ports_configs( std::istream &in, cta_ports_vector &ports_vector );

	public:
		virtual const size_t trade_thread_size() const;
		virtual const size_t quote_thread_size() const;
		virtual const cta_ports_vector &trade_ports() const;
		virtual const cta_ports_vector &quote_ports() const;

		explicit fconfigurator( const char *config_path );
	};
}

#endif