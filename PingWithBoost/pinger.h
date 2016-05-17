#ifndef PINGER_H
#define PINGER_H

#include "icmp_header.h"
#include "ipv4_header.h"

#include <boost/asio.hpp>

using boost::asio::ip::icmp;
using boost::asio::deadline_timer;
namespace posix_time = boost::posix_time;

class pinger
{
public:
	pinger(boost::asio::io_service& io_service, const char* destination);

	size_t ping();

private:
	void start_send();
	void handle_timeout();
	void start_receive();
	void handle_receive(std::size_t length);
	
	static unsigned short get_identifier()
	{
#if defined(BOOST_ASIO_WINDOWS)
		return static_cast<unsigned short>(::GetCurrentProcessId());//全局函数，widows api，得到进程id
#else
		return static_cast<unsigned short>(::getpid());//linux
#endif
	}

	icmp::resolver resolver_;
	icmp::endpoint destination_;
	icmp::socket socket_;
	deadline_timer timer_;
	unsigned short sequence_number_;
	posix_time::ptime time_sent_;
	boost::asio::streambuf reply_buffer_;
	std::size_t num_replies_;
};

#endif //PINGER_H