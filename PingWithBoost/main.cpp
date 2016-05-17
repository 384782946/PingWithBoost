//
// ping.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//


#include <istream>
#include <iostream>
#include <ostream>

#include <boost/asio.hpp>

#include "pinger.h"

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: ping <host>" << std::endl;
#if !defined(BOOST_ASIO_WINDOWS)
			std::cerr << "(You may need to run this program as root.)" << std::endl;
#endif
			return 1;
		}

		boost::asio::io_service io_service;
		pinger p(io_service, argv[1]);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
	}

	system("pause");
}