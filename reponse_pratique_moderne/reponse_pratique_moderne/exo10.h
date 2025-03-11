#pragma once
#include <iostream>

template<typename ...Args>
auto sum(Args... args);

template<typename ...Args>
inline auto sum(Args ...args)
{
	return (args + ...);
}
