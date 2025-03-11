#pragma once
#include <iostream>

template<typename ...Args>
auto print(Args... args);

template<typename ...Args>
inline auto print(Args ...args)
{
	((std::cout << args << " "), ...);
}
