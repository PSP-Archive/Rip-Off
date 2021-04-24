#pragma once
#include "../ui/IconIF.h"
#include <string>
using namespace std;

class VectorIcon: public IconIF{
public:
	VectorIcon(const string& filename);
	void renderGeometry() const;
};

inline void VectorIcon::renderGeometry() const{
}