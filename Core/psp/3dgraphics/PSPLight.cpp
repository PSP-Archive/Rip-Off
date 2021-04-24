#ifdef _3D

#ifdef _SPSP

#include "PSPLight.h"

#include <libgu.h>
#include <libgum.h>

void PSPLight::applyCoordinates() const{
	/*glLightfv(GL_LIGHT0+m_id, GL_POSITION, m_position.GetArray());

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
	*/

}
void PSPLight::applyLightParameters() const{
	//glLightfv(GL_LIGHT0+m_id, GL_AMBIENT, m_ambient.GetArray());
	//glLightfv(GL_LIGHT0+m_id, GL_DIFFUSE, m_diffuse.GetArray());
	//glLightfv(GL_LIGHT0+m_id, GL_SPECULAR, m_specular.GetArray());
}


void PSPLight::enable() const{
	//if (m_isEnabled)
	//	glEnable(GL_LIGHT0 + m_id);
}
void PSPLight::disable() const{
	//if (m_isEnabled)
	//	glDisable(GL_LIGHT0 + m_id);
}

#endif

#endif