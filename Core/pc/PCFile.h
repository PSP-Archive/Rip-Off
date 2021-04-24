#pragma once

#include <fstream>
#include <ostream>
#include "foundation/FileIF.h"

//--------------------------------------------------------------------------------
/**
	PC implementation of an accessible file.
*/
class PCFile : public FileIF
{
public:
	PCFile();
	~PCFile();
	
	bool open(const std::string& filepath);
	bool isOpen() const;
	void close();
	bool readLine(std::string& line);
	bool read(unsigned int nBytes, char* buffer);
	bool writeLineToFile (char * filepath, std::string & line);

private:
	// Prevent copying
	PCFile(const PCFile&);
	PCFile& operator=(const PCFile&);

	std::ifstream m_file;
};
