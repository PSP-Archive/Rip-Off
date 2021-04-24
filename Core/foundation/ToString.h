#pragma once
#include <sstream>

template <class T>
inline std::string toString (const T &item) {
	stringstream stream;
	stream << item;
	return stream.str();
};
