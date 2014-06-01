#ifndef _multicast_communication_cta_ports_vector_h_
#define _multicast_communication_cta_ports_vector_h_

#include <vector>
#include <utility> 

namespace multicast_communication
{
	typedef std::pair<std::string, unsigned short> cta_socket;
	typedef std::vector<cta_socket> cta_ports_vector;
}

#endif