#pragma once
#ifdef _3D

#include "foundation/Singleton.h"
//#include "foundation/Array.h"
#include <vector>
using namespace std;

#include "../Material.h"


//this class will hold references to all the allocated materials from the game.
//
//USAGE:
//	at loading time: every time a material needs to be created,
//		check if it is already in the array with hasMaterial(name).
//		If there is another material with the same name, the loader
//		must take the reference to the existing material, and not create it again.
//			pMat=hasMaterial("matName");
//			if (!pMat){
//				pMat=new Material();
//			}
//
//	at deletion time:
// this class is responsable with materials destruction.
// the objects that have a reference to a material won't delete it, as it might be shared


class BaseMaterialManager{
private:
	vector<Material*> m_vpMaterials;
	//Array<Material*> m_vpMaterials;
public:
	~BaseMaterialManager();
	//returns the address of the material with name "name", or NULL if the material does not
	//exist in the array
	Material* hasMaterial(const string& name) const;
	void addMaterial(Material* pMaterial);

	void clear();
};


typedef Singleton<BaseMaterialManager> MaterialManager;

#endif