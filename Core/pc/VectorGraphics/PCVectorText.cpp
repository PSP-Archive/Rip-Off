#include "vectorgraphics/VectorText.h"


#ifdef _PC
#include <windows.h>
#include <gl/gl.h>


// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"


PCVectorText::PCVectorText(void)
{

}

PCVectorText::~PCVectorText(void)
{
}

void PCVectorText::printChar(const char character) const
{
	switch(character)
	{
		case 'a':
			a();
			glTranslatef(0.027f*getScale(),0,0);
			break;

		case 'b':
			b();
			glTranslatef(0.023f*getScale(),0,0);
			break;

		case 'c':
			c();
			glTranslatef(0.025f*getScale(),0,0);
			break;

		case 'd':
			d();
			glTranslatef(0.025f*getScale(),0,0);
			break;

		case 'e':
			e();
			glTranslatef(0.025f*getScale(),0,0);
			break;

		case 'f':
			f();
			glTranslatef(0.023f*getScale(),0,0);
			break;

		case 'g':
			g();
			glTranslatef(0.027f*getScale(),0,0);
			break;

		case 'h':
			h();
			glTranslatef(0.025f*getScale(),0,0);
			break;

		case 'i':
			i();
			glTranslatef(0.010f*getScale(),0,0);
			break;

		case 'j':
			j();
			glTranslatef(0.025f*getScale(),0,0);
			break;

		case 'k':
			k();
			glTranslatef(0.024f*getScale(),0,0);
			break;

		case 'l':
			l();
			glTranslatef(0.025f*getScale(),0,0);
			break;

		case 'm':
			m();
			glTranslatef(0.027f*getScale(),0,0);
			break;

		case 'n':
			n();
			glTranslatef(0.025f*getScale(),0,0);
			break;

		case 'o':
			o();
			glTranslatef(0.027f*getScale(),0,0);
			break;

		case 'p':
			p();
			glTranslatef(0.019f*getScale(),0,0);
			break;

		case 'q':
			q();
			glTranslatef(0.027f*getScale(),0,0);
			break;

		case 'r':	
			r();
			glTranslatef(0.023f*getScale(),0,0);
			break;

		case 's':
			s();
			glTranslatef(0.019f*getScale(),0,0);
			break;

		case 't':
			t();
			glTranslatef(0.025f*getScale(),0,0);
			break;

		case 'u':
			u();
			glTranslatef(0.022f*getScale(),0,0);
			break;

		case 'v':
			v();
			glTranslatef(0.025f*getScale(),0,0);
			break;

		case 'w':
			w();
			glTranslatef(0.025f*getScale(),0,0);
			break;

		case 'x':
			x();
			glTranslatef(0.022f*getScale(),0,0);
			break;

		case 'y':
			y();
			glTranslatef(0.021f*getScale(),0,0);
			break;

		case 'z':
			z();
			glTranslatef(0.020f*getScale(),0,0);
			break;

		case '.':
			dot();
			glTranslatef(0.007f*getScale(),0,0);
			break;

		case ' ':
			glTranslatef(0.022f*getScale(),0,0);
			break;

		case '0':
			zero();
			glTranslatef(0.015f*getScale(),0,0);
			break;

		case '1':
			one();
			glTranslatef(0.015f*getScale(),0,0);
			break;

		case '2':
			two();
			glTranslatef(0.015f*getScale(),0,0);
			break;

		case '3':
			three();
			glTranslatef(0.015f*getScale(),0,0);
			break;

		case '4':
			four();
			glTranslatef(0.015f*getScale(),0,0);
			break;

		case '5':
			five();
			glTranslatef(0.015f*getScale(),0,0);
			break;

		case '6':
			six();
			glTranslatef(0.015f*getScale(),0,0);
			break;

		case '7':
			seven();
			glTranslatef(0.015f*getScale(),0,0);
			break;

		case '8':
			eight();
			glTranslatef(0.015f*getScale(),0,0);
			break;

		case '9':
			nine();
			glTranslatef(0.015f*getScale(),0,0);
			break;

	}
}

void PCVectorText::a() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale() , 0.00f*getScale());
	glVertex2f(0.01f *getScale() , 0.03f*getScale());
	glVertex2f(0.02f *getScale() , 0.00f*getScale());
	glEnd();
}

void PCVectorText::b() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale(),  0.015f*getScale());
	glVertex2f(0.015f *getScale(),  0.0075f*getScale());
	glVertex2f(0.00f *getScale(),  0.00f*getScale());
	glVertex2f(0.00f *getScale(),  0.015f*getScale());
	glVertex2f(0.00f *getScale(),  0.03f*getScale());
	glVertex2f(0.015f *getScale(),  0.0225f*getScale());
	glVertex2f(0.00f *getScale(),  0.015f*getScale());
	glEnd();
}

void PCVectorText::c() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.018f *getScale(),  0.00f*getScale());
	glVertex2f(0.00f *getScale(),  0.015f*getScale());
	glVertex2f(0.018f *getScale(),  0.03f*getScale());
	glEnd();
}
void PCVectorText::d() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale(),  0.00f*getScale());
	glVertex2f(0.018f *getScale(),  0.015f*getScale());
	glVertex2f(0.00f *getScale(),  0.03f*getScale());
	glVertex2f(0.00f *getScale(),  0.00f*getScale());
	glEnd();
}

void PCVectorText::e() const
{
	glBegin(GL_LINES);
	glVertex2f(0.00f *getScale(),  0.015f*getScale());
	glVertex2f(0.018f *getScale(),  0.015f*getScale());
	glVertex2f(0.00f *getScale(),  0.015f*getScale());
	glVertex2f(0.018f *getScale(),  0.03f*getScale());
	glVertex2f(0.00f *getScale(),  0.015f*getScale());
	glVertex2f(0.018f *getScale(),  0.00f*getScale());
	glEnd();
}



void PCVectorText::f() const
{
	glBegin(GL_LINES);
	glVertex2f(0.00f *getScale(),  0.000f*getScale());
	glVertex2f(0.00f *getScale(),  0.025f*getScale());
	glVertex2f(0.00f *getScale(),  0.025f*getScale());
	glVertex2f(0.018f *getScale(),  0.03f*getScale());
	glVertex2f(0.00f *getScale(),  0.013f*getScale());
	glVertex2f(0.018f *getScale(),  0.02f*getScale());
	glEnd();
}

void PCVectorText::g() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.02f *getScale(),  0.03f*getScale());
	glVertex2f(0.00f *getScale(),  0.015f*getScale());
	glVertex2f(0.015f *getScale(), 0.00f*getScale());
	glVertex2f(0.015f *getScale(), 0.01f*getScale());
	glEnd();
}

void PCVectorText::h() const
{
	glBegin(GL_LINES);
	glVertex2f(0.00f *getScale(),  0.000f*getScale());
	glVertex2f(0.00f *getScale(),  0.03f*getScale());
	glVertex2f(0.015f *getScale(), 0.00f*getScale());
	glVertex2f(0.015f *getScale(), 0.03f*getScale());
	glVertex2f(0.00f *getScale(),  0.0125f*getScale());
	glVertex2f(0.015f *getScale(), 0.0175f*getScale());
	glEnd();
}

void PCVectorText::i() const
{
	glBegin(GL_LINES);
	glVertex2f(0.00f *getScale(),  0.000f*getScale());
	glVertex2f(0.002f *getScale(),  0.03f*getScale());
	glEnd();
}

void PCVectorText::j() const
{
	glBegin(GL_LINES);
	glVertex2f(0.01f *getScale(),  0.000f*getScale());
	glVertex2f(0.01f *getScale(),  0.029f*getScale());
	glVertex2f(0.00f *getScale(),  0.027f*getScale());
	glVertex2f(0.02f *getScale(),  0.03f*getScale());
	glVertex2f(0.01f *getScale(),  0.00f*getScale());
	glVertex2f(0.00f *getScale(),  0.01f*getScale());
	glEnd();
}

void PCVectorText::k() const
{
	glBegin(GL_LINES);
	glVertex2f(0.00f *getScale(),  0.00f*getScale());
	glVertex2f(0.00f *getScale(),  0.03f*getScale());
	glVertex2f(0.00f *getScale(),  0.010f*getScale());
	glVertex2f(0.015f *getScale(),  0.03f*getScale());
	glVertex2f(0.0055f *getScale(), 0.017f*getScale());
	glVertex2f(0.015f *getScale(),  0.00f*getScale());
	glEnd();
}

void PCVectorText::l() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.01f *getScale(),  0.03f*getScale());
	glVertex2f(0.00f *getScale(),  0.00f*getScale());
	glVertex2f(0.018f *getScale(),  0.00f*getScale());
	glEnd();
}

void PCVectorText::m() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale(),   0.00f*getScale());
	glVertex2f(0.005f *getScale(),  0.03f*getScale());
	glVertex2f(0.01f *getScale(),   0.02f*getScale());
	glVertex2f(0.015f *getScale(),  0.03f*getScale());
	glVertex2f(0.02f *getScale(),   0.00f*getScale());
	glEnd();
}

void PCVectorText::n() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale(),   0.00f*getScale());
	glVertex2f(0.005f *getScale(),  0.03f*getScale());
	glVertex2f(0.015f *getScale(),  0.00f*getScale());
	glVertex2f(0.02f *getScale(),   0.03f*getScale());
	glEnd();
}

void PCVectorText::o() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.01f *getScale(),   0.00f*getScale());
	glVertex2f(0.02f *getScale(),   0.015f*getScale());
	glVertex2f(0.01f *getScale(),   0.03f*getScale());
	glVertex2f(0.00f *getScale(),   0.015f*getScale());
	glVertex2f(0.01f *getScale(),   0.00f*getScale());
	glEnd();
}

void PCVectorText::p() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale(),   0.00f*getScale());
	glVertex2f(0.00f *getScale(),   0.03f*getScale());
	glVertex2f(0.015f *getScale(),   0.025f*getScale());
	glVertex2f(0.00f *getScale(),   0.015f*getScale());
	glEnd();
}

void PCVectorText::q() const
{
	glBegin(GL_LINES);
	glVertex2f(0.01f *getScale(),   0.00f*getScale());
	glVertex2f(0.02f *getScale(),   0.015f*getScale());
	glVertex2f(0.02f *getScale(),   0.015f*getScale());
	glVertex2f(0.01f *getScale(),   0.03f*getScale());
	glVertex2f(0.01f *getScale(),   0.03f*getScale());
	glVertex2f(0.00f *getScale(),   0.015f*getScale());
	glVertex2f(0.00f *getScale(),   0.015f*getScale());
	glVertex2f(0.01f *getScale(),   0.00f*getScale());
	glVertex2f(0.02f *getScale(),   0.00f*getScale());
	glVertex2f(0.01f *getScale(),   0.015f*getScale());
	glEnd();
}

void PCVectorText::r() const
{
	glBegin(GL_LINES);
	glVertex2f(0.00f *getScale(),   0.00f*getScale());
	glVertex2f(0.00f *getScale(),   0.03f*getScale());
	glVertex2f(0.00f *getScale(),   0.03f*getScale());
	glVertex2f(0.015f *getScale(),   0.025f*getScale());
	glVertex2f(0.015f *getScale(),   0.025f*getScale());
	glVertex2f(0.00f *getScale(),   0.015f*getScale());
	glVertex2f(0.007f *getScale(),   0.019f*getScale());
	glVertex2f(0.015f *getScale(),   0.00f*getScale());
	glEnd();
}

void PCVectorText::s() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.015f *getScale(),   0.03f*getScale());
	glVertex2f(0.00f *getScale(),   0.02f*getScale());
	glVertex2f(0.01f *getScale(),   0.015f*getScale());
	glVertex2f(0.00f *getScale(),   0.000f*getScale());
	glEnd();
}

void PCVectorText::t() const
{
	glBegin(GL_LINES);
	glVertex2f(0.01f *getScale(),  0.000f*getScale());
	glVertex2f(0.01f *getScale(),  0.028f*getScale());
	glVertex2f(0.00f *getScale(),  0.024f*getScale());
	glVertex2f(0.02f *getScale(),  0.03f*getScale());
	glEnd();
}


void PCVectorText::u() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale(),   0.03f*getScale());
	glVertex2f(0.00f *getScale(),   0.00f*getScale());
	glVertex2f(0.010f *getScale(),   0.00f*getScale());
	glVertex2f(0.017f *getScale(),   0.03f*getScale());
	glEnd();
}

void PCVectorText::v() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale(),   0.03f*getScale());
	glVertex2f(0.01f *getScale(),   0.00f*getScale());
	glVertex2f(0.02f *getScale(),   0.03f*getScale());
	glEnd();
}

void PCVectorText::w() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale(),   0.03f*getScale());
	glVertex2f(0.005f *getScale(),  0.00f*getScale());
	glVertex2f(0.01f *getScale(),   0.01f*getScale());
	glVertex2f(0.015f *getScale(),  0.00f*getScale());
	glVertex2f(0.02f *getScale(),   0.03f*getScale());
	glEnd();
}

void PCVectorText::x() const
{
	glBegin(GL_LINES);
	glVertex2f(0.00f *getScale(),  0.00f*getScale());
	glVertex2f(0.017f *getScale(),  0.03f*getScale());
	glVertex2f(0.00f *getScale(),  0.03f*getScale());
	glVertex2f(0.017f *getScale(),  0.00f*getScale());
	glEnd();
}

void PCVectorText::y() const
{
	glBegin(GL_LINES);
	glVertex2f(0.00f *getScale(),  0.00f*getScale());
	glVertex2f(0.017f *getScale(),  0.03f*getScale());
	glVertex2f(0.0085f *getScale(), 0.015f*getScale());
	glVertex2f(0.00f *getScale(),  0.03f*getScale());
	glEnd();
}

void PCVectorText::z() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale(),   0.028f*getScale());
	glVertex2f(0.01f *getScale(),   0.028f*getScale());
	glVertex2f(0.000f *getScale(),   0.00f*getScale());
	glVertex2f(0.015f *getScale(),   0.000f*getScale());
	glEnd();
}

void PCVectorText::dot() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.000f *getScale(),  0.00f*getScale());
	glVertex2f(0.002f *getScale(),  0.003f*getScale());
	glVertex2f(0.004f *getScale(),  0.00f*getScale());
	glVertex2f(0.000f *getScale(),  0.00f*getScale());
	glEnd();
}

void PCVectorText::zero() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.005f *getScale(),  0.00f*getScale());
	glVertex2f(0.01f *getScale(),   0.01f*getScale());
	glVertex2f(0.01f *getScale(),   0.02f*getScale());
	glVertex2f(0.005f *getScale(),  0.03f*getScale());
	glVertex2f(0.00f *getScale(),   0.02f*getScale());
	glVertex2f(0.00f *getScale(),   0.01f*getScale());
	glVertex2f(0.005f *getScale(),  0.00f*getScale());
	glEnd();
}
void PCVectorText::one() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.007f *getScale(),   0.00f*getScale());
	glVertex2f(0.01f *getScale(),   0.03f*getScale());
	glVertex2f(0.00f *getScale(),   0.02f*getScale());
	glEnd();
}

void PCVectorText::two() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.01f *getScale(),   0.00f*getScale());
	glVertex2f(0.00f *getScale(),   0.00f*getScale());
	glVertex2f(0.01f *getScale(),   0.03f*getScale());
	glVertex2f(0.000f *getScale(),   0.023f*getScale());
	glEnd();
}

void PCVectorText::three() const
{
	glBegin(GL_LINES);
	glVertex2f(0.01f *getScale(),  0.015f*getScale());
	glVertex2f(0.00f *getScale(),  0.015f*getScale());
	glVertex2f(0.01f *getScale(),  0.015f*getScale());
	glVertex2f(0.00f *getScale(),  0.03f*getScale());
	glVertex2f(0.01f *getScale(),  0.015f*getScale());
	glVertex2f(0.00f *getScale(),  0.00f*getScale());
	glEnd();
}

void PCVectorText::four() const
{
	glBegin(GL_LINES);
	glVertex2f(0.00f *getScale(),   0.028f*getScale());
	glVertex2f(0.00f *getScale(),   0.02f*getScale());
	glVertex2f(0.00f *getScale(),   0.02f*getScale());
	glVertex2f(0.01f *getScale(),   0.015f*getScale());
	glVertex2f(0.01f *getScale(),   0.000f*getScale());
	glVertex2f(0.01f *getScale(),   0.028f*getScale());
	glEnd();
}

void PCVectorText::five() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale(),   0.00f*getScale());
	glVertex2f(0.01f *getScale(),   0.01f*getScale());
	glVertex2f(0.00f *getScale(),   0.017f*getScale());
	glVertex2f(0.00f *getScale(),   0.025f*getScale());
	glVertex2f(0.01f *getScale(),   0.03f*getScale());
	glEnd();
}

void PCVectorText::six() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.01f *getScale(),   0.03f*getScale());
	glVertex2f(0.00f *getScale(),   0.01f*getScale());
	glVertex2f(0.00f *getScale(),   0.00f*getScale());
	glVertex2f(0.01f *getScale(),   0.01f*getScale());
	glVertex2f(0.00f *getScale(),   0.01f*getScale());
	glEnd();
}

void PCVectorText::seven() const
{
	glBegin(GL_LINES);
	glVertex2f(0.000f *getScale(),  0.00f*getScale());
	glVertex2f(0.01f *getScale(),   0.03f*getScale());
	glVertex2f(0.01f *getScale(),   0.03f*getScale());
	glVertex2f(0.00f *getScale(),   0.023f*getScale());
	glVertex2f(0.00f *getScale(),   0.01f*getScale());
	glVertex2f(0.01f *getScale(),   0.01f*getScale());
	glEnd();
}

void PCVectorText::eight() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale(),   0.028f*getScale());
	glVertex2f(0.009f *getScale(),   0.028f*getScale());
	glVertex2f(0.00f *getScale(),   0.00f*getScale());
	glVertex2f(0.009f *getScale(),   0.00f*getScale());
	glVertex2f(0.00f *getScale(),   0.028f*getScale());
	glEnd();
}

void PCVectorText::nine() const
{
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.00f *getScale(),   0.00f*getScale());
	glVertex2f(0.01f *getScale(),   0.02f*getScale());
	glVertex2f(0.01f *getScale(),   0.03f*getScale());
	glVertex2f(0.00f *getScale(),   0.020f*getScale());
	glVertex2f(0.01f *getScale(),   0.02f*getScale());
	glEnd();
}

#endif