#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <sstream>

template< typename T >
std::string NumberToHexString(T i)
{
	std::stringstream stream;
	stream << "0x" << std::hex << i;
	return stream.str();
}

template <typename T>
std::string NumberToString(T i)
{
	std::stringstream stream;
	stream << i;
	return stream.str();
}

void PrintLastErrorMessage();

#endif