#pragma once

#include <fstream>

#include <sstream>

#include <iofilemgr.h>
#include "foundation/FileIF.h"

//--------------------------------------------------------------------------------
/**
	PC implementation of an accessible file.
*/
class PSPFile : public FileIF
{
public:
	PSPFile();
	~PSPFile();
	
	bool open(const _STL::string& filepath);
	bool isOpen() const;
	void close();
	bool readLine(_STL::string& line);
	bool read(unsigned int nBytes, char* buffer);
	bool writeLineToFile (char * filepath, _STL::string & line);

private:
	// Prevent copying
	PSPFile(const PSPFile&);
	PSPFile& operator=(const PSPFile&);

	//_STL::fstream m_file;
	
	std::stringstream m_file;
};
