#ifdef _3D

#ifdef _PC

#include "PCLight.h"

#include "GL/glut.h"
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glut32.lib")

void PCLight::applyCoordinates() const{
	glLightfv(GL_LIGHT0+m_id, GL_POSITION, m_position.GetArray());

	glDisable(GL_LIGHTING);
	glColor3f(1,0,0);
	glPointSize(12);
	
	glPushMatrix();
		glBegin(GL_POINTS);
			glVertex3fv(m_position.GetArray());
		glEnd();
	glPopMatrix();

	glPointSize(1);
	glColor3f(1,1,1);
	glEnable(GL_LIGHTING);
	//glTranslatef(m_position[0],m_position[1],m_position[2]);
	//todo: adjust this only if we want to use spotlights
	//glLightfv(GL_LIGHT0+m_id, GL_SPOT_DIRECTION, m_direction.GetArray());
}
void PCLight::applyLightParameters() const{
	glLightfv(GL_LIGHT0+m_id, GL_AMBIENT, m_ambient.GetArray());
	glLightfv(GL_LIGHT0+m_id, GL_DIFFUSE, m_diffuse.GetArray());
	glLightfv(GL_LIGHT0+m_id, GL_SPECULAR, m_specular.GetArray());
}

//--------------------------------------------------

void PCLight::enable() const{
	if (m_isEnabled)
		glEnable(GL_LIGHT0 + m_id);
}
void PCLight::disable() const{
	if (m_isEnabled)
		glDisable(GL_LIGHT0 + m_id);
}

#endif

#endif