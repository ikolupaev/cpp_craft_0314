#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "cta_ports_vector.h"
#include "test_registrator.h"
#include "fconfigurator.h"

namespace multicast_communication
{
	namespace tests_
	{
		typedef std::vector<std::string> test_config_lines;

		void save_trade_thread_size( std::ofstream &test_config_stream )
		{
			test_config_stream << 4 << std::endl;
		};

		void save_quote_thread_size( std::ofstream &test_config_stream )
		{
			test_config_stream << 4 << std::endl;
		};

		void save_socket_configs( std::ofstream &test_config_stream, test_config_lines &lines )
		{
			test_config_stream << lines.size() << std::endl;

			for( auto str : lines )
			{
				test_config_stream << str << std::endl;
			}
		};

		bool compare_ports( const multicast_communication::cta_ports_vector &p1, test_config_lines &p2 )
		{
			if( p1.size() != p2.size() )
			{
				return false;
			}

			auto it1 = p1.cbegin();
			auto it2 = p2.cbegin();

			while( it1 != p1.cend() && it2 != p2.cend() )
			{
				std::ostringstream oss;

				oss << it1->first << " " << it1->second;

				if( oss.str() != *it2 )
				{
					return false;
				}

				it1++;
				it2++;
			}

			return true;
		};
	}
}

void multicast_communication::tests_::configurator_tests()
{
	const char *config_path = "test_config.ini";

	test_config_lines trade_ports;
	trade_ports.push_back( "233.200.79.0 61000" );
	trade_ports.push_back( "233.200.79.1 61001" );

	test_config_lines quote_ports;
	quote_ports.push_back( "233.200.79.128 62128" );
	quote_ports.push_back( "233.200.79.129 62129" );
	quote_ports.push_back( "233.200.79.130 62130" );
	quote_ports.push_back( "233.200.79.131 62131" );

	{
		std::ofstream test_config_stream( config_path );

		save_trade_thread_size( test_config_stream );
		save_quote_thread_size( test_config_stream );

		save_socket_configs( test_config_stream, trade_ports );
		save_socket_configs( test_config_stream, quote_ports );

		test_config_stream.close();
	}

	fconfigurator config( config_path );

	BOOST_CHECK_EQUAL( config.trade_thread_size(), 4 );
	BOOST_CHECK_EQUAL( config.quote_thread_size(), 4 );

	BOOST_CHECK_EQUAL( config.trade_ports().size(), trade_ports.size() );
	BOOST_CHECK_EQUAL( config.quote_ports().size(), quote_ports.size() );

	BOOST_CHECK_EQUAL( compare_ports( config.trade_ports(), trade_ports ), true );
}