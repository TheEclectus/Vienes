#include <cinttypes>
#include <cstdio>
#include <msgpack.hpp>

#include <format.h>

#include <asio.hpp>
#include "../Shared/AsioSTDPlaceholders.h"

//#include <pipeline.h>
#include <functional>
#include <string>

//#include "TCPServer.h"
#include "../Shared/Packet.h"

using asio::ip::tcp;

struct Svr
{
public:
	//asio::io_service Svc;
	asio::ip::tcp::acceptor Acpt;
	asio::ip::tcp::socket Skt;
	asio::error_code ec;
	asio::ip::tcp::endpoint ep;
	char buf[100];

	Svr(asio::io_service &Svc) :
		//Svc(),
		Acpt(Svc, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8008)),
		Skt(Svc)
	{
		StartAccept();
	}
	
	void StartAccept()
	{
		printf("Waiting for connection...\n");
		Acpt.async_accept(Skt, std::bind(&Svr::DoAccept, this, asio::stdplaceholders::error));
	}

	void StartRead()
	{
		char data[512];
		
		Skt.async_read_some(asio::buffer(data, 512), std::bind(&Svr::DoRead, this, asio::stdplaceholders::error, asio::stdplaceholders::bytes_transferred));
	}

	void DoAccept(const asio::error_code &EC)
	{
		if (!EC)
		{
			printf("Connection to %s established.\n", Skt.remote_endpoint().address().to_string().c_str());
		}
		StartRead();
	}

	void DoRead(const asio::error_code& EC, size_t bytes_transferred)
	{
		if (!EC)
		{
			printf("Recieved %d bytes.\n", bytes_transferred);
			// Ping them back
			std::string buffer = ":3";
			fmt::print("Sending '{}' as ping reply...", buffer);
			size_t bytesSent = asio::write(Skt, asio::buffer(buffer));
			if (EC)
			{
				fmt::print("ERROR: {}\n", EC.message());
			}
			CloseConnection();
			StartAccept();
		}
	}

	void CloseConnection()
	{
		if (Skt.is_open())
		{
			Skt.shutdown(Skt.shutdown_both);
			Skt.close();
			fmt::print("Closed connection.\n\n");
		}
	}

	~Svr()
	{
		CloseConnection();
	}
};

void HandleConnect(const asio::error_code &EC)
{
	if (!EC)
	{
		fmt::print("Connection established.\n");
	}
	else
	{
		fmt::print("Failed to establish connection.\n");
	}
}

void HandleRead(const asio::error_code &EC, size_t Bytes)
{
	if (!EC)
	{
		fmt::print("Read {} bytes.\n", Bytes);
	}
	else
	{
		fmt::print("Read error.\n");
	}
}

int main()
{
	asio::io_service svc;
	Svr svr(svc);
	svc.run();

	return 0;
}