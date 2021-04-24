#ifdef _3D

#pragma once

#include "../../foundation/Singleton.h"
#include "Letter3D.h"
#include "../../foundation/PSPHeap.h"
#include <map>


class ConfigItem;

class BaseSymbols{

public:

	BaseSymbols();

	//call it to initialize the singleton; the constructor of the class
	//will parse a file; must be called from game loader
	void init();

	void printChar(const char c, float scale) const;

private:
	//std::map<char,Letter3D> m_letters;
	Letter3D m_letters[41];

private:
	//the char must be a lower case letter or one of ' ', ':', '!'
	int _getIndex(char c) const;
	void addLetter(char c, const ConfigItem& item, Material* pMat);

};


//inline void BaseSymbols::printChar(const char c, float scale) const{
//	map<char,Letter3D>::const_iterator it=m_letters.find(c);
//	if (it==m_letters.end()) it=m_letters.find('a');
//	//map<char,Letter3D>::const_iterator	it=m_letters.find('r');
//	//map<char,Letter3D>::const_iterator	it=m_letters.find('p');
//	
//	it->second.setScale(scale);
//	it->second.render();
//}


typedef Singleton<BaseSymbols> Symbols;

#endif