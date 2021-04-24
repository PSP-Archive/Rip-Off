#pragma once
#include "../../ui/IconIF.h"

#include <string>
using namespace std;

class UIIcon3D:public IconIF
{
public:
	UIIcon3D(const string& filename);
	void renderGeometry() const;
};

inline void UIIcon3D::renderGeometry() const{
}
