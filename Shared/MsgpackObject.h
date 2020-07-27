#pragma once

#include <msgpack.hpp>

class MsgpackObject
{
private:
	msgpack::sbuffer _buffer;
public:
	MsgpackObject();
};