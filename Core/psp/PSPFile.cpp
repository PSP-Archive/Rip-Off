#ifdef _SPSP

#include "psp/PSPFile.h"
#include <string.h>
#include <kernel.h>
#include "foundation/GlobalTimer.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
PSPFile::PSPFile()
{
	// empty
}

//--------------------------------------------------------------------------------
PSPFile::~PSPFile()
{
	//if(m_file.is_open())
	//{
	//	close();
	//}
}

//--------------------------------------------------------------------------------
bool
PSPFile::open(const std::string& filepath)
{
	//GlobalTimer::get()->reset();
	SceUID fd = sceIoOpen(filepath.c_str(), SCE_O_RDONLY, 0);

	//first find the file size
	SceUInt32 sourceSize = (SceUInt32)sceIoLseek(fd, (SceOff)0, SCE_SEEK_END);

	//allocate buffer
	int id = sceKernelAllocMemoryBlock(filepath.c_str(), SCE_KERNEL_SMEM_LOW, sourceSize, NULL);
	void* buffer;
	sceKernelGetMemoryBlockAddr(id, &buffer);

	memset(buffer, '\0', sourceSize);

	//char* buffer = new char[sourceSize];

	//set the file pointer back to the beginning
	sceIoLseek(fd, 0, SCE_SEEK_SET);

	sceIoRead(fd, buffer, sourceSize);

	//m_file << buffer;
	m_file << (char*)buffer;

	//delete [] buffer;
	sceKernelFreeMemoryBlock(id);

	memset(buffer, '\0', sourceSize);

	sceIoClose(fd);
	sceKernelDcacheWritebackInvalidateAll();
	//printf("Finish load %s at %f sec\n", filepath.c_str(), GlobalTimer::get()->getTime());
	
	return true;
}

//--------------------------------------------------------------------------------
bool
PSPFile::isOpen() const
{
	//return m_file.is_open();
	return true;
}

//--------------------------------------------------------------------------------
void
PSPFile::close()
{
	//m_file.close();
}

//--------------------------------------------------------------------------------
bool
PSPFile::readLine(std::string& line)
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
PSPFile::read(unsigned int nBytes, char* buffer)
{
	//if(m_file.eof())
	//{
	//	return false;
	//}

	//m_file.read(buffer, nBytes);
	return true;
}

//--------------------------------------------------------------------------------
bool
PSPFile::writeLineToFile (char * filepath, _STL::string & line) 
{
	printf("write to %s, with data %s\n", filepath, line.c_str());
	SceUID fd = sceIoOpen(filepath, SCE_O_WRONLY, 0);
	
	sceIoWrite(fd, line.c_str(), line.size());
	
	sceIoClose(fd);
	sceKernelDcacheWritebackInvalidateAll();
}

#endif
