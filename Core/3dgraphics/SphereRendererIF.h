#pragma once

#ifdef _3D

class SphereRendererIF{
public:
	virtual ~SphereRendererIF(){}

	virtual void drawCore(unsigned int stacks, unsigned int slices) const=0;
};

#endif