#pragma once

//class that holds OpenGL extensions
//it only has extensions for vertex buffers;
//if other extensions are needed, the corresponding
//functions should be added in this class

//it is made only for PC. If on PSP and GC the same
//process of loading proc. address is needed we should
//implement an IF in 3dgraphics layer


#ifdef _3D
#ifdef _PC

#include "../../foundation/Singleton.h"


#include "GL/glut.h"
#include "GL/glext.h"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")

class PCBaseGlex{
private:
	PFNGLBINDBUFFERARBPROC glBindBufferARB;
	PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;
	PFNGLGENBUFFERSARBPROC glGenBuffersARB;
	PFNGLISBUFFERARBPROC glIsBufferARB;
	PFNGLBUFFERDATAARBPROC glBufferDataARB;
	PFNGLBUFFERSUBDATAARBPROC glBufferSubDataARB;
	PFNGLGETBUFFERSUBDATAARBPROC glGetBufferSubDataARB;
	PFNGLMAPBUFFERARBPROC glMapBufferARB;
	PFNGLUNMAPBUFFERARBPROC glUnmapBufferARB;
	PFNGLGETBUFFERPARAMETERIVARBPROC glGetBufferParameterivARB;
	PFNGLGETBUFFERPOINTERVARBPROC glGetBufferPointervARB;

public:
	PCBaseGlex();
	bool load();

	void bindBufferARB(unsigned int, unsigned int) ;
	void deleteBuffersARB(int, const unsigned int *);
	void genBuffersARB(int, unsigned int *);
	GLboolean isBufferARB(unsigned int);
	void bufferDataARB(unsigned int, GLsizeiptrARB, const void *, unsigned int);
	void bufferSubDataARB(unsigned int, GLintptrARB, GLsizeiptrARB, const void *);
	void getBufferSubDataARB(unsigned int, GLintptrARB, GLsizeiptrARB, void *);
	GLvoid* mapBufferARB(unsigned int, unsigned int);
	GLboolean unmapBufferARB(unsigned int);

};


inline void PCBaseGlex::bindBufferARB(unsigned int a, unsigned int b){
	glBindBufferARB(a,b);
}

inline void PCBaseGlex::deleteBuffersARB(int a, const unsigned int * b){
	glDeleteBuffersARB(a, b);
}

inline void PCBaseGlex::genBuffersARB(int a, unsigned int *b){
	glGenBuffersARB(a,b);
}

inline GLboolean PCBaseGlex::isBufferARB(unsigned int a){
	glIsBufferARB(a);
}

inline void PCBaseGlex::bufferDataARB(unsigned int a, GLsizeiptrARB b, const void *c, unsigned int d){
	glBufferDataARB(a,b,c,d);
}

inline void PCBaseGlex::bufferSubDataARB(unsigned int a, GLintptrARB b, GLsizeiptrARB c, const void *d){
	glBufferSubDataARB(a,b,c,d);
}

inline void PCBaseGlex::getBufferSubDataARB(unsigned int a, GLintptrARB b, GLsizeiptrARB c, void * d){
	glGetBufferSubDataARB(a,b,c,d);
}

inline GLvoid* PCBaseGlex::mapBufferARB(unsigned int a, unsigned int b){
	glMapBufferARB(a,b);
}

inline GLboolean PCBaseGlex::unmapBufferARB(unsigned int a){
	glUnmapBufferARB(a);
}


typedef Singleton<PCBaseGlex> PCGlex;

#endif
#endif