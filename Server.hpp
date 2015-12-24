#pragma once
#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include <functional>
#include "Key.hpp"
#include "GameObject.hpp"

class Server
:
public GameObject
{
	boost::asio::io_service io_service;
	boost::asio::streambuf streambuf;
	boost::asio::ip::udp::socket socket;
	std::shared_ptr<LocalController> localController;
	std::shared_ptr<NetworkController> networkController;
	boost::asio::ip::udp::endpoint receiver_endpoint;
	boost::asio::ip::udp::endpoint endpoint;
	boost::asio::mutable_buffers_1 mb;
public:

	void rec(boost::system::error_code const & errom, int len)
	{
		std::cout << "bigingo" << std::endl;
		using udp = boost::asio::ip::udp;
		udp::resolver resolver(io_service);
		networkController->key = static_cast<Key>(*boost::asio::buffer_cast<int const *>(streambuf.data()));
		if(*boost::asio::buffer_cast<int const *>(streambuf.data()))
		std::cout << "rec_key:" << *boost::asio::buffer_cast<int const *>(streambuf.data()) << std::endl;
		//std::cout << streambuf.size() << std::endl;
		streambuf.consume(sizeof(networkController->key));
		io_service.reset();
		socket.async_receive_from(mb, endpoint, [&](auto e, auto l){this->rec(e,l);});
		std::cout << "endngo" << std::endl;
	}

	Server(std::shared_ptr<LocalController> localController, std::shared_ptr<NetworkController> networkController)
	:
	io_service(),
	streambuf(),
	socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 14514)),
	//socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 14515)),
	localController(localController),
	networkController(networkController),
	mb(streambuf.prepare(512))
	{
		using udp = boost::asio::ip::udp;
		udp::resolver resolver(io_service);
		//receiver_endpoint = *resolver.resolve(udp::resolver::query(udp::v4(), "localhost", "14514"));
		receiver_endpoint = *resolver.resolve(udp::resolver::query(udp::v4(), "localhost", "14515"));
		socket.async_receive_from(mb, endpoint, [&](auto e, auto l){this->rec(e,l);});
	}

	void draw() const{};

	void run()
	{
		io_service.poll();
		using udp = boost::asio::ip::udp;
		std::array<int, 1> a = {{static_cast<int>(localController->key)}};
		if (a[0])
		std::cout << "send_key:" << a[0] << std::endl;
		socket.send_to(boost::asio::buffer(a), receiver_endpoint);
	}
};
