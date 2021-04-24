#pragma once

#include <string>
#include <cassert>

// Disable warning for unreferenced formal parameters as this is an interface
#pragma warning( disable: 4100 )

//--------------------------------------------------------------------------------
/**
	Interface for platform specific file access implementations.
*/
class FileIF
{
public:
	// Opens the file. Returns true if the operation was successful and false
	// otherwise.
	bool open(const std::string& filepath) { assert(!"Interface not implemented"); }

	// Returns true if the file is open, false otherwise.
	bool isOpen() const { assert(!"Interface not implemented"); return false; }

	// Closes the file and cleans up.
	void close() { assert(!"Interface not implemented"); }

	// Reads a line and saves it the passed string. Returns false if there is
	// no more data to read in the file, true otherwise.
	bool readLine(std::string& line) { assert(!"Interface not implemented"); return false; }

	// Reads n bytes and saves them in the passed buffer. Returns false if there is
	// no more data to read in the file, true otherwise.
	bool read(unsigned int nBytes, char* buffer) { assert(!"Interface not implemented"); return false; }
};
