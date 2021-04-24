#pragma once

#ifdef _3D

#include <string>

enum TexFilter{
	LINEAR=0,
	NEAREST=1,
	LINEAR_MIPMAP_LINEAR=2,
	LINEAR_MIPMAP_NEAREST=3,
	NEAREST_MIPMAP_LINEAR=4,
	NEAREST_MIPMAP_NEAREST=5
};

enum TexType{
	TEXTURE_2D=0,
	TEXTURE_3D=1
};

class TextureIF{
protected:
	unsigned int m_texId;
	std::string m_name;
	TexType m_type;		//2D or 3D
	int m_blendOn;
private:
	//block the copy constructor and the assignment operator
	TextureIF(const TextureIF&){}
	TextureIF& operator = (const TextureIF&){ return *this; }

public:
	TextureIF();
	virtual ~TextureIF(){}

	virtual bool create(const std::string& filename, TexFilter filter=LINEAR_MIPMAP_LINEAR)=0;
	void setBlendOn(int blendOn);

	virtual void enable() const=0;
	virtual void disable() const=0;

	virtual void apply() const=0;
	virtual void dismiss() const=0;

	bool hasName(const std::string& name) const;
};

#endif