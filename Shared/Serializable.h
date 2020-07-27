#pragma once

/*
	Provides faculties to serialize class data to JSON and msgpack.
	Can convert readily between JSON and msgpack, and can validate
	either against a JSON schema.
*/

// Placeholders
#define JsonObject int
#define MsgpackObject int

class Serializable
{
private:
	const JsonObject *const _schema;
public:
	// TODO: Find a better way to do this than 'new'
	virtual JsonObject *SerializeToJson();
	virtual MsgpackObject *SerializeToMsgpack();
	
	//     |||||||||
	// === IDEA NOTE ===
	//     |||||||||
	// The number that the server sends as a challenge during
	// login is also the one used for their session ticket.
	// By 'used', think 'encrypted using'.
};