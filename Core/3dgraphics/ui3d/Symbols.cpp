#ifdef _3D

#include "Symbols.h"

#include "foundation/ConfigItem.h"
#include "foundation/ConfigData.h"
#include "foundation/ConfigDataLoader.h"
#include "../managers/MaterialManager.h"


BaseSymbols::BaseSymbols(){
	ConfigDataLoader dataLoader;
	ConfigData data;
	bool b=dataLoader.load("host0:assets/3d/3DText.txt", data);
	assert(b);
	b=dataLoader.load("host0:assets/3d/3DText1.txt", data);
	assert(b);
	b=dataLoader.load("host0:assets/3d/3DText2.txt", data);
	assert(b);
	
	ConfigData::ItemHandle handle;


	handle = data.getItemHandle("MATERIAL");
	assert(handle!=ConfigData::INVALID_HANDLE);

	Material *pMat;

	ConfigItem item = *(data.getItem(handle));
	if (item.hasString("materialName")){
		pMat=MaterialManager::get()->hasMaterial(item.getString("materialName"));
	}else pMat=MaterialManager::get()->hasMaterial("fontMaterial");
	
	//-------------------------------------------------

	//letters
	ConfigItem item1;
	for (char c='A'; c<='Z'; c++){
		string str=" ";
		str[0]=c;
		handle = data.getItemHandle(str);
		assert(handle!=ConfigData::INVALID_HANDLE);

		item1 = *(data.getItem(handle));
		
		addLetter(tolower(c), item1, pMat);
		item1.clear();
	}

	//digits
	string str;
	char num[3];
	for (int i=0;i<10;i++){
		str="D";
		itoa(i,num,10);
		str.append(num);

		handle = data.getItemHandle(str);
		assert(handle!=ConfigData::INVALID_HANDLE);

		item1 = *(data.getItem(handle));

		addLetter(str[1], item1, pMat);
		item1.clear();
	}

	//other symbols

	//space

	handle = data.getItemHandle("SPACE");
	assert(handle!=ConfigData::INVALID_HANDLE);
	item1 = *(data.getItem(handle));
	addLetter(' ', item1, pMat);

	//-------------------------------------------
	handle = data.getItemHandle("EXCLAMATION");
	assert(handle!=ConfigData::INVALID_HANDLE);
	item1 = *(data.getItem(handle));
	addLetter('!', item1, pMat);
	item1.clear();

	//-------------------------------------------
	handle = data.getItemHandle("COLUMN");
	assert(handle!=ConfigData::INVALID_HANDLE);
	item1 = *(data.getItem(handle));
	addLetter(':', item1, pMat);
	item1.clear();

	//------------------------------------------
	handle = data.getItemHandle("O");
	assert(handle!=ConfigData::INVALID_HANDLE);
	item1 = *(data.getItem(handle));
	addLetter('*', item1, pMat);
	
	
}


void BaseSymbols::init(){}

int BaseSymbols::_getIndex(char c) const{
	int i=-1;
	if (c>96 && c<123) i=c-97;
	else if (c==32) i=26;		//space
	else if (c==33) i=27;		//exclamation
	else if (c==58) i=28;		//column
	else if (c>47 && c<=57) i=29+c-47;  //digits
	else if (c==42) i=40;
	return i;
}

void BaseSymbols::addLetter(char c, const ConfigItem& item, Material* pMat){
	//Letter3D letter;
	int i=_getIndex(c);
	if (i<0) return;	//wrong index

	if (c=='*'){
		m_letters[i].setWidth(0.01f);
		m_letters[i].setHeight(0.01f);
	}else{
		if (item.hasFloat("width")){
			m_letters[i].setWidth(0.7f*item.getFloat("width"));
		}
		if (item.hasFloat("height")){
			m_letters[i].setHeight(0.7f*item.getFloat("height"));
		}
	}

	m_letters[i].create();

	m_letters[i].setMaterial(pMat);

	float texCoords[8];
	memset(texCoords,0,8*sizeof(float));

	for (int i=0;i<8;i++){
		char num[3];
		itoa(i,num,10);
		//_itoa_s(i,num,3,10);
		string str("texCoords");
		str.append(num);

		if (item.hasFloat(str)){
			texCoords[i]=item.getFloat(str);
		}
	}

	float aux1, aux2;
	aux1=texCoords[0];
	aux2=1-0.75f*texCoords[1];

	texCoords[0]=texCoords[6];
	texCoords[1]=1-0.75f*texCoords[7];
	texCoords[6]=texCoords[2];
	texCoords[7]=1-0.75f*texCoords[3];
	texCoords[2]=aux1;
	texCoords[3]=aux2;
	texCoords[5]=1-0.75f*texCoords[5];
	m_letters[i].setTexCoords(texCoords);

}


void BaseSymbols::printChar(const char c, float scale) const{

	int i=_getIndex(c);
	if (i<0) return;
	m_letters[i].setScale(scale);
	m_letters[i].render();

	
}


#endif