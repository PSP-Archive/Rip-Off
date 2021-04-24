#include "Scene3D.h"
#ifdef _3D

#include "managers/TextureManager.h"
#include "managers/MeshManager.h"
#include "managers/MaterialManager.h"
#include "managers/RandomHashTable.h"
#include <cassert>

Scene3D::~Scene3D(){

#ifdef _PC
	//delete quads
	vector<GFXObject3D*>::iterator it=m_vpQuads.begin();
	for (;it!=m_vpQuads.end();it++){
		delete (*it);
	}
	m_vpQuads.clear();
#endif

	vector<GFXObject3D*>::iterator itGfx=m_vpGFXObjects.begin();
	for (;itGfx!=m_vpGFXObjects.end();itGfx++){
		delete (*itGfx);
	}
	m_vpGFXObjects.clear();

	LightManager::release();
	m_gfxCleaner.clean();
}

#include "../input/InputManager.h"


void Scene3D::startRender() const{

	if(InputManager::get()->isButtonJustReleased(0, InputDevice::BUTTON4)){
		m_switchCamera=(m_switchCamera+1)%2;
	}
	
	m_initializer.startRendering();

	if (m_switchCamera)
		m_secondCamera.applyLookAt();
	else
		m_activeCamera.applyLookAt();
	
	LightManager::get()->renderLights();			//must be done after the camera transformations,
												//as it updates lights positions

	#ifdef _PC
		float z=0;
		if (m_vpQuads.size()>0){
			z=m_vpQuads[0]->getCentre().z();
		}
		vector<GFXObject3D*>::const_iterator it=m_vpQuads.begin();
		for (;it!=m_vpQuads.end();it++){
			Vector3f p=(*it)->getCentre();
			Vector3f pn(p.x(),p.y(),z);
			m_camera.adjustScale(pn,p.z()-z);
			(*it)->render(Vector2f(0,0),0.0f);
			m_camera.resetScale();
		}
	#endif

	

	
	vector<GFXObject3D*>::const_iterator itGfx=m_vpGFXObjects.begin();
	for (;itGfx!=m_vpGFXObjects.end();itGfx++){
		Vector3f p=(*itGfx)->getCentre();
		m_camera.adjustScale(p);
		(*itGfx)->render(Vector2f(0,0),0.0f);
		m_camera.resetScale();
	}

	m_camera.adjustScale(Vector3f(0,0,0));
}

void Scene3D::onAspectRatioUpdate(){
	int width,height;
	m_initializer.getScreenSize(&width,&height);
	m_camera.setAspect(width,height);
}



void Scene3D::setBackground(int numQuads, Material** ppMaterials){
#ifdef _PC
	onAspectRatioUpdate();
	float size=max(2*m_camera.getAspect(),2.0f);
	float z=-80;
	float size2=size/2.0f;
	Quad* pQuad;

	if (numQuads==1){
		GFXObject3D* pGFXObject=new GFXObject3D();
		pQuad= (Quad*)(MeshManager::get()->hasMesh("BgrQuad0"));
		if (!pQuad){
			pQuad=new Quad();
			pQuad->create(size,size,Vector3f(1,0,0), Vector3f(0,1,0));
			MeshManager::get()->addMesh(pQuad);
		}
		pGFXObject->setCentre(Vector3f(0,0,z));
		pGFXObject->setMaterial(*ppMaterials);
		pGFXObject->setShape(pQuad);
		m_vpQuads.push_back(pGFXObject);
	}else{
	//todo
		//----------------------------------------------------------------------------------------------
		//bottom
		//----------------------------------------------------------------------------------------------
		GFXObject3D* pGFXObject=new GFXObject3D();
		pQuad= (Quad*)(MeshManager::get()->hasMesh("BgrQuad0"));
		if (!pQuad){
			pQuad=new Quad();
			pQuad->create(size,size,Vector3f(1,0,0), Vector3f(0,1,0));
			MeshManager::get()->addMesh(pQuad);
		}
		pGFXObject->setCentre(Vector3f(0,0,z));
		pGFXObject->setMaterial(*ppMaterials);
		pGFXObject->setShape(pQuad);
		m_vpQuads.push_back(pGFXObject);


		//----------------------------------------------------------------------------------------------
		//left
		//----------------------------------------------------------------------------------------------

		pGFXObject=new GFXObject3D();
		pQuad= (Quad*)(MeshManager::get()->hasMesh("BgrQuad1"));
		if (!pQuad){
			pQuad=new Quad();
			pQuad->create(size,size, Vector3f(0,1,0),Vector3f(0,0,1));
			MeshManager::get()->addMesh(pQuad);
		}
		pGFXObject->setCentre(Vector3f(-size2,0,size2+z));
		pGFXObject->setMaterial(*(ppMaterials+1));
		pGFXObject->setShape(pQuad);
		m_vpQuads.push_back(pGFXObject);


		//----------------------------------------------------------------------------------------------
		//front
		//----------------------------------------------------------------------------------------------
		
		pGFXObject=new GFXObject3D();
		pQuad= (Quad*)(MeshManager::get()->hasMesh("BgrQuad2"));
		if (!pQuad){
			pQuad=new Quad();
			pQuad->create(size,size, Vector3f(1,0,0), Vector3f(0,0,1));
			MeshManager::get()->addMesh(pQuad);
		}
		pGFXObject->setCentre(Vector3f(0.0f,size2,size2+z));
		pGFXObject->setMaterial(*(ppMaterials+2));
		pGFXObject->setShape(pQuad);
		m_vpQuads.push_back(pGFXObject);


		//----------------------------------------------------------------------------------------------
		//right
		//----------------------------------------------------------------------------------------------

		pGFXObject=new GFXObject3D();
		pQuad= (Quad*)(MeshManager::get()->hasMesh("BgrQuad3"));
		if (!pQuad){
			pQuad=new Quad();
			pQuad->create(size,size, Vector3f(0,-1,0), Vector3f(0,0,1));
			MeshManager::get()->addMesh(pQuad);
		}
		pGFXObject->setCentre(Vector3f(size2,0.0f,size2+z));
		pGFXObject->setMaterial(*(ppMaterials+3));
		pGFXObject->setShape(pQuad);
		m_vpQuads.push_back(pGFXObject);


		//----------------------------------------------------------------------------------------------
		//back
		//----------------------------------------------------------------------------------------------

		pGFXObject=new GFXObject3D();
		pQuad= (Quad*)(MeshManager::get()->hasMesh("BgrQuad4"));
		if (!pQuad){
			pQuad=new Quad();
			pQuad->create(size,size, Vector3f(-1,0,0), Vector3f(0,0,1));
			MeshManager::get()->addMesh(pQuad);
		}
		pGFXObject->setCentre(Vector3f(0.0f,-size2,size2+z));
		pGFXObject->setMaterial(*(ppMaterials+4));
		pGFXObject->setShape(pQuad);
		m_vpQuads.push_back(pGFXObject);


		//----------------------------------------------------------------------------------------------
		//top
		//----------------------------------------------------------------------------------------------

		pGFXObject=new GFXObject3D();
		pQuad= (Quad*)(MeshManager::get()->hasMesh("BgrQuad5"));
		if (!pQuad){
			pQuad=new Quad();
			pQuad->create(size,size, Vector3f(1,0,0), Vector3f(0,-1,0));
			MeshManager::get()->addMesh(pQuad);
		}
		pGFXObject->setCentre(Vector3f(0.0f,0.0f,size+z));
		pGFXObject->setMaterial(*(ppMaterials+5));
		pGFXObject->setShape(pQuad);
		m_vpQuads.push_back(pGFXObject);

	}
#endif
}

void Scene3D::addGFXObject(GFXObject3D *pGFXObject){
	m_vpGFXObjects.push_back(pGFXObject);
}

void Scene3D::initializeForRendering(){
	int width, height;

	m_initializer.initializeForRendering(&width, &height, LightManager::get()->hasLights());
	 LightManager::get()->initLightsForRendering();

	m_camera.setAspect(width,height);

	m_camera.applyProjection();
	m_camera.applyViewport();

	//the active camera and the static one are the same at startup
	m_activeCamera.setAspect(width,height);
	m_secondCamera.setAspect(width,height);

	m_secondCamera.moveForward(4);
	
	m_switchCamera=0;
	
	
}

#endif