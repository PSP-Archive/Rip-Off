#include "PCPositioner.h"

#ifdef _3D
#ifdef _PC

#include "GL/glut.h"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")

void PCPositioner::applyTransforms(const Vector2f& position2D, float angleRot) const{
	glPushMatrix();

	glTranslatef(position2D.x,position2D.y,0);
	glRotatef(angleRot,0,0,1);

}

void PCPositioner::resetTransforms() const{
	glPopMatrix();
}

//void PCPositioner::setZ(float z){
//	m_z=z;
//}

#endif
#endif