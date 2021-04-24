#ifdef _3D

#include "Effect3DLoader.h"
#include "ParticleSystemLoader.h"

#include "../GFXEffect3D.h"
#include "../LaserEffect3D.h"
#include "../ExplosionEffect3D.h"
#include "../FireJetEffect3D.h"
#include "Icon3DLoader.h"
#include "foundation/PSPHeap.h"

EffectIF* Effect3DLoader::load(const ConfigItem& item) const{
	string type;
	
	if (item.hasString("type")){
		type=item.getString("type");
	}

	if (!type.compare("laser")){
		LaserEffect3D* pEffect=new LaserEffect3D();

		if (item.hasFloat("duration")){
			pEffect->setDuration(item.getFloat("duration"));
		}
		

		Icon3DLoader iconLoader;
		Icon3D* pIcon=iconLoader.load(item);
		if (item.hasFloat("iconWidth2")){
			pEffect->setWidth2(item.getFloat("iconWidth2"));
			pIcon->setWidth2(item.getFloat("iconWidth2"));
		}
		if (item.hasFloat("iconHeight2")){
			pEffect->setHeight2(item.getFloat("iconHeight2"));
			pIcon->setHeight2(item.getFloat("iconHeight2"));
		}

		pEffect->addIcon(pIcon);

		Icon3D* pIcon1=iconLoader.load(item,1);
		if (pIcon1) pEffect->addIcon(pIcon1);

		Icon3D* pIcon2=iconLoader.load(item,2);
		if (pIcon2) pEffect->addIcon(pIcon2);


		return (EffectIF*)pEffect;

	}else if (!type.compare("explosion")){
		ExplosionEffect3D* pEffect=new ExplosionEffect3D();

		if (item.hasFloat("duration")){
			pEffect->setDuration(item.getFloat("duration"));
		}
		

		Icon3DLoader iconLoader;
		Icon3D* pIcon=iconLoader.load(item);
		if (item.hasFloat("iconWidth2")){
			pEffect->setWidth2(item.getFloat("iconWidth2"));
			pIcon->setWidth2(item.getFloat("iconWidth2"));
		}
		if (item.hasFloat("iconHeight2")){
			pEffect->setHeight2(item.getFloat("iconHeight2"));
			pIcon->setHeight2(item.getFloat("iconHeight2"));
		}

		pEffect->addIcon(pIcon);

		//Icon3D* pIcon1=iconLoader.load(item,1);
		//if (pIcon1) pEffect->addIcon(pIcon1);

		//Icon3D* pIcon2=iconLoader.load(item,2);
		//if (pIcon2) pEffect->addIcon(pIcon2);


		return (EffectIF*)pEffect;

	}else if (!type.compare("fireJet")){
		FireJetEffect3D* pEffect=new FireJetEffect3D();
		
		if (item.hasFloat("duration")){
			pEffect->setDuration(item.getFloat("duration"));
		}

		if (item.hasFloat("offset")){
			pEffect->setOffset(item.getFloat("offset"));
		}

		if(item.hasString("particleSystem")){
			ParticleSystemLoader particleLoader;
			pEffect->setParticleSystem(particleLoader.load(item));
		}
		
		
		return (EffectIF*)pEffect;
	}else{
		GFXEffect3D* pEffect=new GFXEffect3D();
		
		if (item.hasFloat("duration")){
			pEffect->setDuration(item.getFloat("duration"));
		}

		if (item.hasFloat("offset")){
			pEffect->setOffset(item.getFloat("offset"));
		}

		if(item.hasString("particleSystem")){
			ParticleSystemLoader particleLoader;
			pEffect->setParticleSystem(particleLoader.load(item));
		}
		
		
		return (EffectIF*)pEffect;
	}
	return NULL;
}

#endif