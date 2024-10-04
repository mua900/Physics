#pragma once

#ifdef Debug
#include <iostream>
#include <string>
#include <cstddef>
#include <cstdint>
enum class l_level : uint8_t
{
    l_message = 0,
    l_warning,
    l_error
};

static void d_log(const std::string& message, const l_level log_level)
{
	switch (log_level)
	{
		case l_level::l_message:
			std::cout << message << '\n';
			break;
		case l_level::l_warning:
			std::cout << "\n-----WARNING-----";
			std::cout << message << '\n';
			std::cout << "-----WARNING-----\n";
			break;
		case l_level::l_error:
			std::cout << message << '\n';
			exit(2);
			break;
	}
}
#else
#define d_log(x, y)
#endif
