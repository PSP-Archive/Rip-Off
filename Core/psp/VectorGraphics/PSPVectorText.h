#pragma once
#include "ui/TextIF.h"

class PSPVectorText: public TextIF
{
private:
	void drawCharLines(const ScePspFVector3 arr[], const int count) const;
	void drawCharStrip(const ScePspFVector3 arr[], const int count) const;
	void a() const;
	void b() const;
	void c() const;
	void d() const;
	void e() const;
	void f() const;
	void g() const;
	void h() const;
	void i() const;
	void j() const;
	void k() const;
	void l() const;
	void m() const;
	void n() const;
	void o() const;
	void p() const;
	void q() const;
	void r() const;
	void s() const;
	void t() const;
	void u() const;
	void v() const;
	void w() const;
	void x() const;
	void y() const;
	void z() const;

	void zero()	const;
	void one()	const;
	void two()	const;
	void three()const;
	void four() const;
	void five() const;
	void six()	const;
	void seven()const;
	void eight()const;
	void nine()	const;
	
public:
	void printChar(const char character) const;

	PSPVectorText(void);
	~PSPVectorText(void);
};

static const ScePspFVector3 char_a[] = {
		{0.00f, 0.00f, 0},
		{0.01f, 0.03f, 0},
		{0.02f, 0.00f, 0}
};

static const ScePspFVector3 char_b[] = {
		{0.00f ,  0.015f,0},
		{0.015f ,  0.0075f,0},
		{0.00f ,  0.00f,0},
		{0.00f ,  0.015f,0},
		{0.00f ,  0.03f,0},
		{0.015f ,  0.0225f,0},
		{0.00f ,  0.015f,0}
	};

static const ScePspFVector3 char_c[] = {
	
		{0.018f ,  0.00f,0},
		{0.00f ,  0.015f,0},
		{0.018f ,  0.03f,0}
	};

static const ScePspFVector3 char_d[] = {
	
		0.00f ,  0.00f,0,
		0.018f ,  0.015f,0,
		0.00f ,  0.03f,0,
		0.00f ,  0.00f,0
	};

static const 	ScePspFVector3 char_e[] = {
	
		{0.00f ,  0.015f,0},
		{0.018f ,  0.015f,0},
		{0.00f ,  0.015f,0},
		{0.018f ,  0.03f,0},
		{0.00f ,  0.015f,0},
		{0.018f ,  0.00f,0}
	};

static const 	ScePspFVector3 char_f[] = {
	
		{0.00f ,  0.000f,0},
		{0.00f ,  0.025f,0},
		{0.00f ,  0.025f,0},
		{0.018f ,  0.03f,0},
		{0.00f ,  0.013f,0},
		{0.018f ,  0.02f,0}
	};

static const 	ScePspFVector3 char_g[] = {
	
		{0.02f ,  0.03f,0},
		{0.00f ,  0.015f,0},
		{0.015f , 0.00f,0},
		{0.015f , 0.01f,0}
	};

static const 	ScePspFVector3 char_h[] = {
	
		{0.00f ,  0.000f,0},
		{0.00f ,  0.03f,0},
		{0.015f , 0.00f,0},
		{0.015f , 0.03f,0},
		{0.00f ,  0.0125f,0},
		{0.015f , 0.0175f,0}
	};

static const 	ScePspFVector3 char_i[] = {
	
		{0.00f ,  0.000f,0},
		{0.002f ,  0.03f,0}
	};


static const	ScePspFVector3 char_j[] = {
	
		{0.01f ,  0.000f,0},
		{0.01f ,  0.029f,0},
		{0.00f ,  0.027f,0},
		{0.02f ,  0.03f,0},
		{0.01f ,  0.00f,0},
		{0.00f ,  0.01f,0}
	};

static const 	ScePspFVector3 char_k[] = {
	
		{0.00f ,  0.00f,0},
		{0.00f ,  0.03f,0},
		{0.00f ,  0.010f,0},
		{0.015f ,  0.03f,0},
		{0.0055f , 0.017f,0},
		{0.015f ,  0.00f,0}
	};

static const ScePspFVector3 char_l[] = {
	
		{0.01f,  0.03f,0},
		{0.00f,  0.00f,0},
		{0.018f,  0.00f,0}
	};

static const 	ScePspFVector3 char_m[] = {
	
		{0.00f ,   0.00f,0},
		{0.005f ,  0.03f,0},
		{0.01f ,   0.02f,0},
		{0.015f ,  0.03f,0},
		{0.02f ,   0.00f,0}
	};

static const 	ScePspFVector3 char_n[] = {
	
		{0.00f ,   0.00f,0},
		{0.005f ,  0.03f,0},
		{0.015f ,  0.00f,0},
		{0.02f ,   0.03f,0}
	};

static const 	ScePspFVector3 char_o[] = {
	
		{0.01f ,   0.00f,0},
		{0.02f ,   0.015f,0},
		{0.01f ,   0.03f,0},
		{0.00f ,   0.015f,0},
		{0.01f ,   0.00f,0}
	};

static const 	ScePspFVector3 char_p[] = {
	
		{0.00f ,   0.00f,0},
		{0.00f ,   0.03f,0},
		{0.015f ,   0.025f,0},
		{0.00f ,   0.015f,0}
	};

static const	ScePspFVector3 char_q[] = {
	
		{0.01f ,   0.00f,0},
		{0.02f ,   0.015f,0},
		{0.02f ,   0.015f,0},
		{0.01f ,   0.03f,0},
		{0.01f ,   0.03f,0},
		{0.00f ,   0.015f,0},
		{0.00f ,   0.015f,0},
		{0.01f ,   0.00f,0},
		{0.02f ,   0.00f,0},
		{0.01f ,   0.015f,0}
	};

static const	ScePspFVector3 char_r[] = {
	
		{0.00f ,   0.00f,0},
		{0.00f ,   0.03f,0},
		{0.00f ,   0.03f,0},
		{0.015f ,   0.025f,0},
		{0.015f ,   0.025f,0},
		{0.00f ,   0.015f,0},
		{0.007f ,   0.019f,0},
		{0.015f ,   0.00f,0}
	};

static const 	ScePspFVector3 char_s[] = {
	
		{0.015f ,   0.03f,0},
		{0.00f ,   0.02f,0},
		{0.01f ,   0.015f,0},
		{0.00f ,   0.000f,0}
	};

static const 	ScePspFVector3 char_t[] = {
	
		{0.01f ,  0.000f,0},
		{0.01f ,  0.028f,0},
		{0.00f ,  0.024f,0},
		{0.02f ,  0.03f,0}
	};

static const 	ScePspFVector3 char_u[] = {
	
		{0.00f ,   0.03f,0},
		{0.00f ,   0.00f,0},
		{0.010f ,   0.00f,0},
		{0.017f ,   0.03f,0}
	};

static const 	ScePspFVector3 char_v[] = {
	
		{0.00f ,   0.03f,0},
		{0.01f ,   0.00f,0},
		{0.02f ,   0.03f,0}
	};

static const 	ScePspFVector3 char_w[] = {
	
		{0.00f ,   0.03f,0},
		{0.005f ,  0.00f,0},
		{0.01f ,   0.01f,0},
		{0.015f ,  0.00f,0},
		{0.02f ,   0.03f,0}
	};

static const 	ScePspFVector3 char_x[] = {
	
		{0.00f ,  0.00f,0},
		{0.017f ,  0.03f,0},
		{0.00f ,  0.03f,0},
		{0.017f ,  0.00f,0}
	};

static const 	ScePspFVector3 char_y[] = {
	
		{0.00f ,  0.00f,0},
		{0.017f ,  0.03f,0},
		{0.0085f , 0.015f,0},
		{0.00f ,  0.03f,0}
	};

static const	ScePspFVector3 char_z[] = {
	
		{0.00f ,   0.028f,0},
		{0.01f ,   0.028f,0},
		{0.000f ,   0.00f,0},
		{0.015f ,   0.000f,0}
	};

static const 	ScePspFVector3 num_0[] = {
	
		{0.005f ,  0.00f,0},
		{0.01f ,   0.01f,0},
		{0.01f ,   0.02f,0},
		{0.005f ,  0.03f,0},
		{0.00f ,   0.02f,0},
		{0.00f ,   0.01f,0},
		{0.005f ,  0.00f,0}
	};

static const 	ScePspFVector3 num_1[] = {
	
		{0.007f ,   0.00f,0},
		{0.01f ,   0.03f,0},
		{0.00f ,   0.02f,0}
	};

static const 	ScePspFVector3 num_2[] = {
	
		{0.01f ,   0.00f,0},
		{0.00f ,   0.00f,0},
		{0.01f ,   0.03f,0},
		{0.000f ,   0.023f,0}
	};

static const 	ScePspFVector3 num_3[] = {
	
		{0.01f ,  0.015f,0},
		{0.00f ,  0.015f,0},
		{0.01f ,  0.015f,0},
		{0.00f ,  0.03f,0},
		{0.01f ,  0.015f,0},
		{0.00f ,  0.00f,0}
	};

static const 	ScePspFVector3 num_4[] = {
	
		{0.00f ,   0.028f,0},
		{0.00f ,   0.02f,0},
		{0.00f ,   0.02f,0},
		{0.01f ,   0.015f,0},
		{0.01f ,   0.000f,0},
		{0.01f ,   0.028f,0}
	};

static const 	ScePspFVector3 num_5[] = {
	
		{0.00f ,   0.00f,0},
		{0.01f ,   0.01f,0},
		{0.00f ,   0.017f,0},
		{0.00f ,   0.025f,0},
		{0.01f ,   0.03f,0}
	};

static const 	ScePspFVector3 num_6[] = {
	
		{0.01f ,   0.03f,0},
		{0.00f ,   0.01f,0},
		{0.00f ,   0.00f,0},
		{0.01f ,   0.01f,0},
		{0.00f ,   0.01f,0}
	};

static const	ScePspFVector3 num_7[] = {
	
		{0.000f ,  0.00f,0},
		{0.01f ,   0.03f,0},
		{0.01f ,   0.03f,0},
		{0.00f ,   0.023f,0},
		{0.00f ,   0.01f,0},
		{0.01f ,   0.01f,0}
	};

static const 	ScePspFVector3 num_8[] = {
	
		{0.00f ,   0.028f,0},
		{0.009f ,   0.028f,0},
		{0.00f ,   0.00f,0},
		{0.009f ,   0.00f,0},
		{0.00f ,   0.028f,0}
	};

static const 	ScePspFVector3 num_9[] = {
	
		{0.00f ,   0.00f,0},
		{0.01f ,   0.02f,0},
		{0.01f ,   0.03f,0},
		{0.00f ,   0.020f,0},
		{0.01f ,   0.02f,0}
	};
//static const ScePspFVector3 char_p[] = {
//	
//		{0.00f ,   0.00f,0},
//		{0.00f ,   0.03f,0},
//		{0.015f ,   0.025f,0},
//		{0.00f ,   0.015f,0}
//	};