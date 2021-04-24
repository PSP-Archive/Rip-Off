#pragma once


//this class contains general objects that make the environment
//like background, lights and camera.
//
//It is not platform dependent, as its members are compiled for the
//current platform only.
//
//It also contains a member 'Initializer' that is used to initialize
//OpenGL state for drawing (enable z buffer etc)
//
//USAGE:
//Loading:
//	Use Scene3DLoader(item), where item contains the name of a scene config file.
//			item SCENE_GFX
//				string configFile SceneConfig.dat
//			enditem
//  Example of a scene config file is in SceneConf.dat, i've currently placed it in the
//	documentation folder.
//			
//	
//Runtime:
//	from the game application, call initializeForRendering() before the main
//	game loop.
//	Then call startRender() before drawing any objects in the main loop.
//	You may call endRender at the end, but it is currently not implemented.
//

#ifdef _3D



#include "../graphics/SceneIF.h"
#include "GFX3DInitializer.h"
#include "GFXObject3D.h"
#include "managers/LightManager.h"

#include "GFXCleaner.h"
#include "Camera.h"

#include "Quad.h"

//--------------
#include "Sphere.h"

class Scene3D: public SceneIF{
private:
	//LightManager *m_pLightManager;
	GFX3DInitializer m_initializer;

	Camera m_camera;
	mutable int m_switchCamera;
	mutable Camera m_activeCamera, m_secondCamera;
#ifdef _PC
	vector<GFXObject3D*> m_vpQuads;
#endif
	vector<GFXObject3D*> m_vpGFXObjects;
	//Sphere *m_pSphere;
	GFXCleaner m_gfxCleaner;		//release the platform specific singletons like glex.

private:
	//used to create the background quad
	//void setAspect();
	void onAspectRatioUpdate();

public:
	//the destructor must release all the textures and the materials allocated
	~Scene3D();	

	//initialize attributes like: activate culling, normalize normals etc,
	//which are called after the creation of the window.
	void initializeForRendering();

	//render the elements that contain the environment
	//(like background and other artifacts)
	void startRender() const;

	void endRender() const;

	void cleanUpForRendering() const;

	//setters used by the loader
	//void setBackground(int numQuads);
	
	void setBackground(int numQuads, Material** pMaterial);
	//void setLights(LightManager* pLightManager);
	void addGFXObject(GFXObject3D *pGFXObject);

	//void debug(){
	//	GFXObject3D *p=m_vpGFXObjects[0];
	//}
};



inline void Scene3D::endRender() const{
	m_camera.resetScale();
}

inline void Scene3D::cleanUpForRendering() const{
}

#endif