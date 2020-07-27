#include <functional>

namespace asio
{
	namespace stdplaceholders
	{
		static decltype (std::placeholders::_1) &error = ::std::placeholders::_1;
		static decltype (std::placeholders::_2) &bytes_transferred = ::std::placeholders::_2;
		static decltype (std::placeholders::_2) &iterator = ::std::placeholders::_2;
		static decltype (std::placeholders::_2) &signal_number = ::std::placeholders::_2;
	}
}