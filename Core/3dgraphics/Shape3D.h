#pragma once

#ifdef _3D

#include <string>
using namespace std;

class Shape3D{
protected:
	string m_name;			//gfx object name or model path, used by the mesh manager to avoi duplication

public:
	virtual ~Shape3D(){};

	virtual void renderGeometry() const=0;

	void setName(const string& meshName);
	bool hasName(const string& meshName) const;
	//const string& getName() const;
};

#endif