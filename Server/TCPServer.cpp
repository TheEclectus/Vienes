#include "TCPServer.h"

#include <format.h>

#include "../Shared/AsioSTDPlaceholders.h"

using namespace asio::ip;

TCPConnection::TCPConnection(asio::io_service &IOService) :
	_socket(IOService),
	_bIsAuthenticated(false)
{
		
}

tcp::socket &TCPConnection::GetSocketRef()
{
	return _socket;
}

const bool TCPConnection::bIsAuthenticated() const
{
	return _bIsAuthenticated;
}

void TCPConnection::Disconnect()
{
	fmt::print("[{}:{}] Closing socket.\n", _socket.remote_endpoint().address().to_string(), _socket.remote_endpoint().port());
	asio::error_code EC;
	_socket.shutdown(tcp::socket::shutdown_type::shutdown_both, EC);
	_socket.close();
}

void TCPConnection::StartAsyncRead()
{
	// READ
	// ME
	// ,
	// DIPSHIT
	// !!!

	// You're going to take all of these async ops and give them lambdas with
	// 'this' in the capture list, so they can access themselves in the call-
	// backs. EVERY. SINGLE. FUCKING. ONE.
	// Welcome to hell, future Neb.

	_socket.async_read_some(asio::buffer(_buffer), std::bind(&TCPConnection::AsyncReadHandler, this, asio::stdplaceholders::error, asio::stdplaceholders::bytes_transferred));
}

void TCPConnection::AsyncReadHandler(const asio::error_code &EC, size_t Bytes)
{
	//fmt::print("[{}:{}] Server recieved {} bytes.\n", _socket.)
	if (!EC)
	{
		fmt::print("Recieved {} bytes.\n", Bytes);
	}
	else
	{
		fmt::print("Error.\n");
		if (EC == asio::error::connection_aborted || EC == asio::error::eof || EC == asio::error::interrupted || EC == asio::error::shut_down)
		{
			Disconnect();
		}
	}
	StartAsyncRead();
}

TCPServer::TCPServer(const uint16_t Port) :
	_ioService(),
	_acceptor(_ioService, tcp::endpoint(tcp::v4(), Port)),
	_pendingConnection(new TCPConnection(_ioService))
{
	
}

void TCPServer::Start()
{
	StartAsyncAccept();
	_ioService.run();
}

void TCPServer::StartAsyncAccept()
{
	_acceptor.async_accept(_pendingConnection->GetSocketRef(), _pendingEndpoint, std::bind(&TCPServer::AsyncAcceptHandler, this, asio::stdplaceholders::error));
}

void TCPServer::AsyncAcceptHandler(const asio::error_code &EC)
{
	if (!EC)
	{
		auto EndPt = _pendingConnection->GetSocketRef().remote_endpoint();
		fmt::print("[{}:{}] Connection accepted.\n", EndPt.address().to_string(), EndPt.port());
		_pendingConnection->StartAsyncRead();
		_connections.push_back(_pendingConnection);

		_pendingConnection = new TCPConnection(_ioService);	// TODO: Make and use an allocator for this shit.
	}
	else
	{
		auto EndPt = _pendingConnection->GetSocketRef().remote_endpoint();
		fmt::print("[{}:{}] Connection error!.\n{}\n", EndPt.address().to_string(), EndPt.port(), EC.message());
	}
	StartAsyncAccept();
}