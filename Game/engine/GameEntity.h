#pragma once

#include <map>

#include "engine/RigidBody.h"
#include "graphics/GFXObject.h"

// for networking message passing
#include "Network/NetworkMessage.h"

//--------------------------------------------------------------------------------
class GameEntity : public RigidBody
{
public:
	// Ctor
	GameEntity();
	
	// Dtor
	virtual ~GameEntity() {}

	// Requests to destroy the entity
	void destroy();
	
	// Called when the entity should be updated
	virtual void onUpdate(float time) {}
	
	// Called when the entity should be rendered
	virtual void Render();

	// Get and set type
	unsigned int getEntityType() { return m_entityType; }
	void setEntityType(unsigned int t) { m_entityType = t; }
	
	// Tags management
	int setTag(int tagID);
	int queryTag(int tagID);
	int removeTag(int tagID);

	// Sets the graphcis object
	void setGFXObject(GFXObject *gfx) { m_gfx = gfx; };

	// For networking message passing
	void packMessage(EntityMessage &message);
	void unpackMessage(const EntityMessage &message);

	// flag update status for network update
	bool isUpdated() const { return m_isUpdated; }
	bool notUpdated() const { return (m_isUpdated == false); }
	void flagUpdate() { m_isUpdated = true; }
	void clearUpdateFlag() { m_isUpdated = false; }

private:
	// TAGS
	std::map<int, int> m_tags;
	
	// Graphics item
	GFXObject* m_gfx;

	// entityType
	unsigned int m_entityType;

	// check data updated from network
	bool m_isUpdated;

};
