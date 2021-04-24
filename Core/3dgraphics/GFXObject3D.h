#pragma once


//this class is an abstraction of a 3Dobject
//that contains geometry data
//
//USAGE:
//	at loading:
//		use GFXObject3DLoader
//
//	runtime:
//		call method render(const Vector2f& position, float angle)
//		from the main game loop

#ifdef _3D

#include "Icon3D.h"
#include "../graphics/GFXObjectIF.h"
#include "Material.h"
#include "Positioner.h"
#include "Shape3D.h"




class GFXObject3D:public GFXObjectIF{
private:
	Positioner m_positioner;
	const Material *m_pMaterial;

	Icon3D *m_pIcon, *m_pIconBack;			//some objects might have a surrounding blooming texture

	Shape3D *m_pShape;


private:
	//virtual void renderGeometry() const=0;
	Vector3f m_centre;

public:
	GFXObject3D();
	virtual ~GFXObject3D();

	void setMaterial(const Material* pMaterial);

	void render(const Vector2f& position, float angle) const;
	
	//virtual const Vector3f& getPivot() const=0;

	void setCentre(const Vector3f& centre);
	void setShape(Shape3D* pShape);
	void setIcon(Icon3D *pIcon);
	void setIconBack(Icon3D *pIcon);

	const Vector3f& getCentre() const;
	
	
};

#endif