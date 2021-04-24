#ifdef _PC

#include "pc/PCFile.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
PCFile::PCFile()
{
	// empty
}

//--------------------------------------------------------------------------------
PCFile::~PCFile()
{
	if(m_file.is_open())
	{
		close();
	}
}

//--------------------------------------------------------------------------------
bool
PCFile::open(const std::string& filepath)
{
	m_file.open(filepath.c_str());
	return m_file.is_open();
}

//--------------------------------------------------------------------------------
bool
PCFile::isOpen() const
{
	return m_file.is_open();
}

//--------------------------------------------------------------------------------
void
PCFile::close()
{
	m_file.close();
}

//--------------------------------------------------------------------------------
bool
PCFile::readLine(std::string& line)
{
	if(m_file.eof())
	{
		return false;
	}
	
	getline(m_file, line);
	return true;
}

//--------------------------------------------------------------------------------
bool
PCFile::read(unsigned int nBytes, char* buffer)
{
	if(m_file.eof())
	{
		return false;
	}

	m_file.read(buffer, nBytes);
	return true;
}

//--------------------------------------------------------------------------------
bool
PCFile::writeLineToFile (char * filepath, std::string & line)
{
	std::ofstream out (filepath);
	if (out)	{
		out << line;
		out.close ();	
	} else {
		return false;
	}
	return true;
}

#endif
