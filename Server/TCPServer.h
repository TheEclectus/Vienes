#pragma once

#include <asio.hpp>
#include <functional>
#include <vector>

#define TCP_CONN_BUFFER_SIZE 1024

class TCPConnection;
class TCPServer;

/*
	1. TCPServer creates TCPConnection with no active connection
	2. TCPServer passes new connection to info TCPConnection
	3. Connection added to connection pool
	4. Async ops start on TCPConnection
*/
class TCPConnection
{
	friend class TCPServer;
private:
	asio::ip::tcp::socket _socket;
	asio::error_code _error;
	bool _bIsConnected, _bIsAuthenticated;
	char _buffer[TCP_CONN_BUFFER_SIZE];
public:
	TCPConnection(asio::io_service &IOService);
	asio::ip::tcp::socket &GetSocketRef();
	const bool bIsAuthenticated() const;
	void Disconnect();

	void StartAsyncRead();
	void AsyncReadHandler(const asio::error_code &EC, size_t Bytes);
	/*void AsyncWriteHandler(const asio::error_code &EC, size_t Bytes);
	*/
};

class TCPServer
{
private:
	asio::io_service _ioService;
	asio::ip::tcp::acceptor _acceptor;
	asio::error_code _error;
	std::vector<TCPConnection*> _connections;

	TCPConnection *_pendingConnection;
	asio::ip::tcp::endpoint _pendingEndpoint;	// Guarenteed to be valid when AsyncAcceptHandler() is invoked.
public:
	TCPServer(const uint16_t Port);
	void Start();
	
	void StartAsyncAccept();
	void AsyncAcceptHandler(const asio::error_code &EC);	// Connection
};