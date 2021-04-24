#include "PCGlex.h"

#ifdef _3D
#ifdef _PC

PCBaseGlex::PCBaseGlex(){
	load();
}

bool PCBaseGlex::load(){
	if (!wglGetCurrentContext()) return false;
	PROC p=0;


	p = wglGetProcAddress("glBindBufferARB");
	if (p) {
		glBindBufferARB = (PFNGLBINDBUFFERARBPROC)p;
	}
	
	p = wglGetProcAddress("glDeleteBuffersARB");
	if (p) {
		glDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)p;
	}
	
	p = wglGetProcAddress("glGenBuffersARB");
	if (p) {
		glGenBuffersARB = (PFNGLGENBUFFERSARBPROC)p;
	}
	
	p = wglGetProcAddress("glIsBufferARB");
	if (p) {
		glIsBufferARB = (PFNGLISBUFFERARBPROC)p;
	}
	
	p = wglGetProcAddress("glBufferDataARB");
	if (p) {
		glBufferDataARB = (PFNGLBUFFERDATAARBPROC)p;
	}
	
	p = wglGetProcAddress("glBufferSubDataARB");
	if (p) {
		glBufferSubDataARB = (PFNGLBUFFERSUBDATAARBPROC)p;
	}
	
	p = wglGetProcAddress("glGetBufferSubDataARB");
	if (p) {
		glGetBufferSubDataARB = (PFNGLGETBUFFERSUBDATAARBPROC)p;
	}
	
	p = wglGetProcAddress("glMapBufferARB");
	if (p) {
		glMapBufferARB = (PFNGLMAPBUFFERARBPROC)p;
	}
	
	p = wglGetProcAddress("glUnmapBufferARB");
	if (p) {
		glUnmapBufferARB = (PFNGLUNMAPBUFFERARBPROC)p;
	}
	return true;
}

#endif
#endif