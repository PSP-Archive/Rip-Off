#include "PSPVectorText.h"


#ifdef _SPSP

#include <libgu.h>
#include <libgum.h>

typedef struct {
	float x, y, z;
} vertex_float;


PSPVectorText::PSPVectorText(void)
{

}

PSPVectorText::~PSPVectorText(void)
{
}

void PSPVectorText::printChar(const char character) const
{
	ScePspFVector3	vec = {0, 0, 0 };


	switch(character)
	{
		case 'a':
			drawCharStrip(char_a, 3);
			vec.x = 0.027f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'b':
			drawCharStrip(char_b, 7);
			vec.x = 0.023f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'c':
			drawCharStrip(char_c, 3);
			vec.x = 0.025f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'd':
			drawCharStrip(char_d, 4);
			vec.x = 0.025f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'e':
			drawCharLines(char_e, 6);
			vec.x = 0.025f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'f':
			drawCharLines(char_f, 6);
			vec.x = 0.023f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'g':
			drawCharStrip(char_g, 4);
			vec.x = 0.027f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'h':
			drawCharLines(char_h, 6);
			vec.x = 0.025f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'i':
			drawCharLines(char_i, 2);
			vec.x = 0.010f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'j':
			drawCharLines(char_j, 6);
			vec.x = 0.025f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'k':
			drawCharLines(char_k, 6);
			vec.x = 0.024f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'l':
			drawCharStrip(char_l, 3);
			vec.x = 0.025f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'm':
			drawCharStrip(char_m, 5);
			vec.x = 0.027f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'n':
			drawCharStrip(char_n, 4);
			vec.x = 0.025f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'o':
			drawCharStrip(char_o, 5);
			vec.x = 0.027f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'p':
			drawCharStrip(char_p, 4);
			vec.x = 0.019f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'q':
			drawCharLines(char_q, 10);
			vec.x = 0.027f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'r':	
			drawCharLines(char_r, 8);
			vec.x = 0.023f*getScale();
			sceGumTranslate(&vec);
			break;

		case 's':
			drawCharStrip(char_s, 4);
			vec.x = 0.019f*getScale();
			sceGumTranslate(&vec);
			break;

		case 't':
			drawCharLines(char_t, 4);
			vec.x = 0.025f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'u':
			drawCharStrip(char_u, 4);
			vec.x = 0.022f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'v':
			drawCharStrip(char_v, 3);
			vec.x = 0.025f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'w':
			drawCharStrip(char_w, 5);
			vec.x = 0.025f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'x':
			drawCharLines(char_x, 4);
			vec.x = 0.022f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'y':
			drawCharLines(char_y, 4);
			vec.x = 0.021f*getScale();
			sceGumTranslate(&vec);
			break;

		case 'z':
			drawCharStrip(char_z, 4);
			vec.x = 0.020f*getScale();
			sceGumTranslate(&vec);
			break;

		case ' ':
			vec.x = 0.022f*getScale();
			sceGumTranslate(&vec);
			break;

		case '0':
			drawCharStrip(num_0, 7);
			vec.x = 0.015f*getScale();
			sceGumTranslate(&vec);
			break;

		case '1':
			drawCharStrip(num_1, 3);
			vec.x = 0.015f*getScale();
			sceGumTranslate(&vec);
			break;

		case '2':
			drawCharStrip(num_2, 4);
			vec.x = 0.015f*getScale();
			sceGumTranslate(&vec);
			break;

		case '3':
			drawCharLines(num_3, 6);
			vec.x = 0.015f*getScale();
			sceGumTranslate(&vec);
			break;

		case '4':
			drawCharLines(num_4, 6);
			vec.x = 0.015f*getScale();
			sceGumTranslate(&vec);
			break;

		case '5':
			drawCharStrip(num_5, 5);
			vec.x = 0.015f*getScale();
			sceGumTranslate(&vec);
			break;

		case '6':
			drawCharStrip(num_6, 5);
			vec.x = 0.015f*getScale();
			sceGumTranslate(&vec);
			break;

		case '7':
			drawCharLines(num_7, 6);
			vec.x = 0.015f*getScale();
			sceGumTranslate(&vec);
			break;

		case '8':
			drawCharStrip(num_8, 5);
			vec.x = 0.015f*getScale();
			sceGumTranslate(&vec);
			break;

		case '9':
			drawCharStrip(num_9, 5);
			vec.x = 0.015f*getScale();
			sceGumTranslate(&vec);
			break;

	}
}

void PSPVectorText::drawCharLines(const ScePspFVector3 arr[], const int count) const
{
	sceGumPushMatrix();
	
	ScePspFVector3 s = {getScale(),getScale(),1.0f};
	sceGumScale(&s);

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			count, 0, arr);

	sceGumPopMatrix();
}

void PSPVectorText::drawCharStrip(const ScePspFVector3 arr[], const int count) const
{
	sceGumPushMatrix();
	
	ScePspFVector3 s = {getScale(),getScale(),1.0f};
	sceGumScale(&s);

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			count, 0, arr);

	sceGumPopMatrix();
}

void PSPVectorText::a() const
{
	sceGumPushMatrix();
	
	ScePspFVector3 s = {getScale(),getScale(),1.0f};
	sceGumScale(&s);


	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			3, 0, char_a);

	sceGumPopMatrix();
}

void PSPVectorText::b() const
{
	ScePspFVector3 arr[] = {
		{0.00f *getScale(),  0.015f*getScale(),0},
		{0.015f *getScale(),  0.0075f*getScale(),0},
		{0.00f *getScale(),  0.00f*getScale(),0},
		{0.00f *getScale(),  0.015f*getScale(),0},
		{0.00f *getScale(),  0.03f*getScale(),0},
		{0.015f *getScale(),  0.0225f*getScale(),0},
		{0.00f *getScale(),  0.015f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			7, 0, arr);

}

void PSPVectorText::c() const
{
	ScePspFVector3 arr[] = {
	
		{0.018f *getScale(),  0.00f*getScale(),0},
		{0.00f *getScale(),  0.015f*getScale(),0},
		{0.018f *getScale(),  0.03f*getScale(),0}
	};
	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			3, 0, arr);

}
void PSPVectorText::d() const
{
	ScePspFVector3 arr[] = {
	
		0.00f *getScale(),  0.00f*getScale(),0,
		0.018f *getScale(),  0.015f*getScale(),0,
		0.00f *getScale(),  0.03f*getScale(),0,
		0.00f *getScale(),  0.00f*getScale(),0
	};
	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			4, 0, arr);
}

void PSPVectorText::e() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),  0.015f*getScale(),0},
		{0.018f *getScale(),  0.015f*getScale(),0},
		{0.00f *getScale(),  0.015f*getScale(),0},
		{0.018f *getScale(),  0.03f*getScale(),0},
		{0.00f *getScale(),  0.015f*getScale(),0},
		{0.018f *getScale(),  0.00f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			6, 0, arr);

}



void PSPVectorText::f() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),  0.000f*getScale(),0},
		{0.00f *getScale(),  0.025f*getScale(),0},
		{0.00f *getScale(),  0.025f*getScale(),0},
		{0.018f *getScale(),  0.03f*getScale(),0},
		{0.00f *getScale(),  0.013f*getScale(),0},
		{0.018f *getScale(),  0.02f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			6, 0, arr);


}

void PSPVectorText::g() const
{
	ScePspFVector3 arr[] = {
	
		{0.02f *getScale(),  0.03f*getScale(),0},
		{0.00f *getScale(),  0.015f*getScale(),0},
		{0.015f *getScale(), 0.00f*getScale(),0},
		{0.015f *getScale(), 0.01f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			4, 0, arr);
}

void PSPVectorText::h() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),  0.000f*getScale(),0},
		{0.00f *getScale(),  0.03f*getScale(),0},
		{0.015f *getScale(), 0.00f*getScale(),0},
		{0.015f *getScale(), 0.03f*getScale(),0},
		{0.00f *getScale(),  0.0125f*getScale(),0},
		{0.015f *getScale(), 0.0175f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			6, 0, arr);

}

void PSPVectorText::i() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),  0.000f*getScale(),0},
		{0.002f *getScale(),  0.03f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			2, 0, arr);

}

void PSPVectorText::j() const
{
	ScePspFVector3 arr[] = {
	
		{0.01f *getScale(),  0.000f*getScale(),0},
		{0.01f *getScale(),  0.029f*getScale(),0},
		{0.00f *getScale(),  0.027f*getScale(),0},
		{0.02f *getScale(),  0.03f*getScale(),0},
		{0.01f *getScale(),  0.00f*getScale(),0},
		{0.00f *getScale(),  0.01f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			6, 0, arr);

}

void PSPVectorText::k() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),  0.00f*getScale(),0},
		{0.00f *getScale(),  0.03f*getScale(),0},
		{0.00f *getScale(),  0.010f*getScale(),0},
		{0.015f *getScale(),  0.03f*getScale(),0},
		{0.0055f *getScale(), 0.017f*getScale(),0},
		{0.015f *getScale(),  0.00f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			6, 0, arr);
}

void PSPVectorText::l() const
{
	sceGumPushMatrix();

	ScePspFVector3 s = {getScale(),getScale(),1.0f};
	sceGumScale(&s);

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			3, 0, char_l);

	sceGumPopMatrix();
}

void PSPVectorText::m() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),   0.00f*getScale(),0},
		{0.005f *getScale(),  0.03f*getScale(),0},
		{0.01f *getScale(),   0.02f*getScale(),0},
		{0.015f *getScale(),  0.03f*getScale(),0},
		{0.02f *getScale(),   0.00f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			5, 0, arr);

}

void PSPVectorText::n() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),   0.00f*getScale(),0},
		{0.005f *getScale(),  0.03f*getScale(),0},
		{0.015f *getScale(),  0.00f*getScale(),0},
		{0.02f *getScale(),   0.03f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			4, 0, arr);

}

void PSPVectorText::o() const
{
	ScePspFVector3 arr[] = {
	
		{0.01f *getScale(),   0.00f*getScale(),0},
		{0.02f *getScale(),   0.015f*getScale(),0},
		{0.01f *getScale(),   0.03f*getScale(),0},
		{0.00f *getScale(),   0.015f*getScale(),0},
		{0.01f *getScale(),   0.00f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			5, 0, arr);

}

void PSPVectorText::p() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),   0.00f*getScale(),0},
		{0.00f *getScale(),   0.03f*getScale(),0},
		{0.015f *getScale(),   0.025f*getScale(),0},
		{0.00f *getScale(),   0.015f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			4, 0, arr);

}

void PSPVectorText::q() const
{
	ScePspFVector3 arr[] = {
	
		{0.01f *getScale(),   0.00f*getScale(),0},
		{0.02f *getScale(),   0.015f*getScale(),0},
		{0.02f *getScale(),   0.015f*getScale(),0},
		{0.01f *getScale(),   0.03f*getScale(),0},
		{0.01f *getScale(),   0.03f*getScale(),0},
		{0.00f *getScale(),   0.015f*getScale(),0},
		{0.00f *getScale(),   0.015f*getScale(),0},
		{0.01f *getScale(),   0.00f*getScale(),0},
		{0.02f *getScale(),   0.00f*getScale(),0},
		{0.01f *getScale(),   0.015f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			10, 0, arr);
}

void PSPVectorText::r() const
{
	float f = getScale();

	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),   0.00f*getScale(),0},
		{0.00f *getScale(),   0.03f*getScale(),0},
		{0.00f *getScale(),   0.03f*getScale(),0},
		{0.015f *getScale(),   0.025f*getScale(),0},
		{0.015f *getScale(),   0.025f*getScale(),0},
		{0.00f *getScale(),   0.015f*getScale(),0},
		{0.007f *getScale(),   0.019f*getScale(),0},
		{0.015f *getScale(),   0.00f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			8, 0, arr);
}

void PSPVectorText::s() const
{
	ScePspFVector3 arr[] = {
	
		{0.015f *getScale(),   0.03f*getScale(),0},
		{0.00f *getScale(),   0.02f*getScale(),0},
		{0.01f *getScale(),   0.015f*getScale(),0},
		{0.00f *getScale(),   0.000f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			4, 0, arr);
}

void PSPVectorText::t() const
{
	ScePspFVector3 arr[] = {
	
		{0.01f *getScale(),  0.000f*getScale(),0},
		{0.01f *getScale(),  0.028f*getScale(),0},
		{0.00f *getScale(),  0.024f*getScale(),0},
		{0.02f *getScale(),  0.03f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			4, 0, arr);


}


void PSPVectorText::u() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),   0.03f*getScale(),0},
		{0.00f *getScale(),   0.00f*getScale(),0},
		{0.010f *getScale(),   0.00f*getScale(),0},
		{0.017f *getScale(),   0.03f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			4, 0, arr);

}

void PSPVectorText::v() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),   0.03f*getScale(),0},
		{0.01f *getScale(),   0.00f*getScale(),0},
		{0.02f *getScale(),   0.03f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			3, 0, arr);
}

void PSPVectorText::w() const
{

	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),   0.03f*getScale(),0},
		{0.005f *getScale(),  0.00f*getScale(),0},
		{0.01f *getScale(),   0.01f*getScale(),0},
		{0.015f *getScale(),  0.00f*getScale(),0},
		{0.02f *getScale(),   0.03f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			5, 0, arr);

}

void PSPVectorText::x() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),  0.00f*getScale(),0},
		{0.017f *getScale(),  0.03f*getScale(),0},
		{0.00f *getScale(),  0.03f*getScale(),0},
		{0.017f *getScale(),  0.00f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			4, 0, arr);
}

void PSPVectorText::y() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),  0.00f*getScale(),0},
		{0.017f *getScale(),  0.03f*getScale(),0},
		{0.0085f *getScale(), 0.015f*getScale(),0},
		{0.00f *getScale(),  0.03f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			4, 0, arr);
}

void PSPVectorText::z() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),   0.028f*getScale(),0},
		{0.01f *getScale(),   0.028f*getScale(),0},
		{0.000f *getScale(),   0.00f*getScale(),0},
		{0.015f *getScale(),   0.000f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			4, 0, arr);
;
}

void PSPVectorText::zero() const
{
	ScePspFVector3 arr[] = {
	
		{0.005f *getScale(),  0.00f*getScale(),0},
		{0.01f *getScale(),   0.01f*getScale(),0},
		{0.01f *getScale(),   0.02f*getScale(),0},
		{0.005f *getScale(),  0.03f*getScale(),0},
		{0.00f *getScale(),   0.02f*getScale(),0},
		{0.00f *getScale(),   0.01f*getScale(),0},
		{0.005f *getScale(),  0.00f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			7, 0, arr);

}
void PSPVectorText::one() const
{
	ScePspFVector3 arr[] = {
	
		{0.007f *getScale(),   0.00f*getScale(),0},
		{0.01f *getScale(),   0.03f*getScale(),0},
		{0.00f *getScale(),   0.02f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			3, 0, arr);
}

void PSPVectorText::two() const
{
	ScePspFVector3 arr[] = {
	
		{0.01f *getScale(),   0.00f*getScale(),0},
		{0.00f *getScale(),   0.00f*getScale(),0},
		{0.01f *getScale(),   0.03f*getScale(),0},
		{0.000f *getScale(),   0.023f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			4, 0, arr);
}

void PSPVectorText::three() const
{
	ScePspFVector3 arr[] = {
	
		{0.01f *getScale(),  0.015f*getScale(),0},
		{0.00f *getScale(),  0.015f*getScale(),0},
		{0.01f *getScale(),  0.015f*getScale(),0},
		{0.00f *getScale(),  0.03f*getScale(),0},
		{0.01f *getScale(),  0.015f*getScale(),0},
		{0.00f *getScale(),  0.00f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			6, 0, arr);
}

void PSPVectorText::four() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),   0.028f*getScale(),0},
		{0.00f *getScale(),   0.02f*getScale(),0},
		{0.00f *getScale(),   0.02f*getScale(),0},
		{0.01f *getScale(),   0.015f*getScale(),0},
		{0.01f *getScale(),   0.000f*getScale(),0},
		{0.01f *getScale(),   0.028f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			6, 0, arr);


}

void PSPVectorText::five() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),   0.00f*getScale(),0},
		{0.01f *getScale(),   0.01f*getScale(),0},
		{0.00f *getScale(),   0.017f*getScale(),0},
		{0.00f *getScale(),   0.025f*getScale(),0},
		{0.01f *getScale(),   0.03f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			5, 0, arr);


}

void PSPVectorText::six() const
{
	ScePspFVector3 arr[] = {
	
		{0.01f *getScale(),   0.03f*getScale(),0},
		{0.00f *getScale(),   0.01f*getScale(),0},
		{0.00f *getScale(),   0.00f*getScale(),0},
		{0.01f *getScale(),   0.01f*getScale(),0},
		{0.00f *getScale(),   0.01f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			5, 0, arr);


}

void PSPVectorText::seven() const
{
	ScePspFVector3 arr[] = {
	
		{0.000f *getScale(),  0.00f*getScale(),0},
		{0.01f *getScale(),   0.03f*getScale(),0},
		{0.01f *getScale(),   0.03f*getScale(),0},
		{0.00f *getScale(),   0.023f*getScale(),0},
		{0.00f *getScale(),   0.01f*getScale(),0},
		{0.01f *getScale(),   0.01f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			6, 0, arr);

}

void PSPVectorText::eight() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),   0.028f*getScale(),0},
		{0.009f *getScale(),   0.028f*getScale(),0},
		{0.00f *getScale(),   0.00f*getScale(),0},
		{0.009f *getScale(),   0.00f*getScale(),0},
		{0.00f *getScale(),   0.028f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			5, 0, arr);

}

void PSPVectorText::nine() const
{
	ScePspFVector3 arr[] = {
	
		{0.00f *getScale(),   0.00f*getScale(),0},
		{0.01f *getScale(),   0.02f*getScale(),0},
		{0.01f *getScale(),   0.03f*getScale(),0},
		{0.00f *getScale(),   0.020f*getScale(),0},
		{0.01f *getScale(),   0.02f*getScale(),0}
	};

	sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			5, 0, arr);

}

#endif