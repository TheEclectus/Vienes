#pragma once

#include <cstdint>
#include <msgpack.hpp>
#include "xxhash.h"

#include "Serializable.h"

struct PacketTypeEnums
{
	// SERVER_ means server -> client
	// CLIENT_ means client -> server
	enum {
		SERVER_ERROR			= 0x00,	// Error code (optionally with message)

		CLIENT_AUTH_REQUEST		= 0x01,	// Client username, password via SSL
		SERVER_AUTH_CHALLENGE	= 0x02, // Random number
		CLIENT_AUTH_RESPONSE	= 0x03,	// ^ hashed with password
	};
};

/*
	Packet layout:
	+-----------------+---------------------+
	| Type (7+1 bits) | Extra parameters... |
	+-----------------+---------------------+
*/
class Packet : public Serializable
{
private:
	const uint8_t MASK_TYPE = 0b01111111;	// & with type variable
											// assert(_type == _type & MASK_TYPE) to verify
public:
	
};