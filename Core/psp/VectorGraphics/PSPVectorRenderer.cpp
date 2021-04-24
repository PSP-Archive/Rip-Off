#ifdef _VECTOR

#ifdef _SPSP

#include "PSPVectorRenderer.h"

#include <libgu.h>
#include <libgum.h>

//--------------------------------------------------------------------------------
void
PSPVectorRenderer::Render(LinePrimitive& primitive, const Vector4f& color, float lineWidth,
	const Vector2f& position, float angle, float scale)
{
	angle *= 3.141592 / 180.0;

	unsigned int number = ((unsigned char)(color[3] * 255)) << 24;
	number |= ((unsigned char)(color[2] * 255)) << 16;
	number |= ((unsigned char)(color[1] * 255)) << 8;
	number |= ((unsigned char)(color[0] * 255));

	ScePspFVector3 vector;
	
	//// Set the color and width
	sceGuColor(number);
	//glLineWidth(lineWidth);
	//
	//// Apply transforms
	sceGumPushMatrix();
	//sceGumLoadIdentity();

	//ScePspFVector3 points[2];
	//points[0].x = -1;
	//points[0].y = -1;
	//points[0].z = 0;
	//points[1].x = 1;
	//points[1].y = 1;
	//points[1].z = 0;


	//Apply transformations
	vector.x = 1.0f / getAspectRatio();
	vector.y = 1.0f;
	vector.z = 1.0f;
	sceGumScale(&vector);

	vector.x = position.x;
	vector.y = position.y;
	vector.z = 0.0f;
	sceGumTranslate(&vector);

	sceGumRotateZ(angle);

	ScePspFVector3 s = {scale,scale,1.0f};
	sceGumScale(&s);




		int noPoints = primitive.GetList().size();
		//ScePspFVector3 *points = new ScePspFVector3[noPoints];

		ScePspFVector3 *points = (ScePspFVector3 *)sceGuGetMemory( sizeof( ScePspFVector3 ) * noPoints ) ;

		int i =0;

		std::list<Vector2f>::const_iterator it;
		for(it = primitive.GetList().begin(); it != primitive.GetList().end(); it++)
		{
			points[i].x = it->x;
			points[i].y = it->y;
			points[i].z = 0.0f;

			i++;
		}



		// Begin rendering
	if(primitive.GetLPType() == LinePrimitive::LIST)
			sceGumDrawArray(SCEGU_PRIM_LINES,
			SCEGU_VERTEX_FLOAT,
			noPoints, NULL, points);
		
		else if(primitive.GetLPType() == LinePrimitive::STRIP)
			sceGumDrawArray(SCEGU_PRIM_LINE_STRIP,
			SCEGU_VERTEX_FLOAT,
			noPoints, NULL, points);
		else
		{
			assert	(!"Primitive type not supported");
		}

		//delete[] points;

	sceGumPopMatrix();

	//glLineWidth(1);
	
}

//--------------------------------------------------------------------------------
void
PSPVectorRenderer::init()
{
	sceGuEnable(SCEGU_BLEND);
	sceGuBlendFunc( SCEGU_ADD, SCEGU_SRC_ALPHA, SCEGU_DST_ALPHA,
		0x00000000, 0x00000000 ); // Alpha blend parameters
}

//--------------------------------------------------------------------------------
void
PSPVectorRenderer::cleanUp()
{
	//sceGuDisable(SCEGU_BLEND);
}

//--------------------------------------------------------------------------------
void
PSPVectorRenderer::startRender()
{
	sceGuClear(SCEGU_CLEAR_COLOR);
}

//--------------------------------------------------------------------------------
void
PSPVectorRenderer::endRender()
{

}


#endif //VECTOR

#endif //SPSP