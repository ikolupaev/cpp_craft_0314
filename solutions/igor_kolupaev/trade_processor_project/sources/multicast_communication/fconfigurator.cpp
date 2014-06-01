#include <fstream>
#include <string>

#include "cta_ports_vector.h"
#include "fconfigurator.h"

using namespace multicast_communication;

void fconfigurator::skip_endl( std::istream &in )
{
	std::string skipstr;
	std::getline( in, skipstr );
}

void fconfigurator::read_ports_configs( std::istream &in, cta_ports_vector &ports_vector )
{
	size_t trade_ports_amount;
	in >> trade_ports_amount;

	while( ( trade_ports_amount-- ) > 0 )
	{
		skip_endl( in );

		std::string address;
		std::getline( in, address, ' ' );

		unsigned short port;
		in >> port;

		ports_vector.push_back( cta_socket( address, port ) );
	}
}

fconfigurator::fconfigurator( const char *config_path )
{
	std::ifstream fin( config_path );

	fin >> trade_thread_size_;
	fin >> quote_thread_size_;

	read_ports_configs( fin, trade_ports_ );
	read_ports_configs( fin, quote_ports_ );
}

const size_t fconfigurator::trade_thread_size() const
{
	return trade_thread_size_;
}

const size_t fconfigurator::quote_thread_size() const
{
	return quote_thread_size_;
}
const cta_ports_vector& fconfigurator::trade_ports() const
{
	return trade_ports_;
}

const cta_ports_vector& fconfigurator::quote_ports() const
{
	return quote_ports_;
}
