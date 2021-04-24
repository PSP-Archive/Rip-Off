#include "engine/GameEntity.h"
#include "engine/Game.h"

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"

//--------------------------------------------------------------------------------
GameEntity::GameEntity() :
	m_gfx(NULL),
	m_entityType(0),
	m_isUpdated(false)
{

}

//--------------------------------------------------------------------------------
int GameEntity::setTag(int tagID)
{
	return ++m_tags[tagID];
}

//--------------------------------------------------------------------------------
int GameEntity::queryTag(int tagID)
{
	return m_tags[tagID];
}

//--------------------------------------------------------------------------------
int GameEntity::removeTag(int tagID)
{
	return --m_tags[tagID];
}

//--------------------------------------------------------------------------------
void GameEntity::Render()
{
	if(m_gfx)
	{
		m_gfx->render(m_position, m_rotation.getDegrees());
	}
}

//--------------------------------------------------------------------------------
void GameEntity::destroy()
{
	GameEngine::get()->registerDestruction(this);
}

//--------------------------------------------------------------------------------
void GameEntity::packMessage(EntityMessage &message)
{
	message.id = (short)m_id;
	message.entityType = (char)m_entityType;
	message.isAlive = m_alive;
	message.position = m_position;
	message.orientation = m_orientation;
	message.rotation = m_rotation.getDegrees();
	message.velocity = m_velocity;
	//message.totalForce = m_totalForce;
}

//--------------------------------------------------------------------------------
void GameEntity::unpackMessage(const EntityMessage &message)
{
	m_id = (int)message.id;
	m_entityType = (unsigned int)message.entityType;
	m_alive = message.isAlive;
	m_position = message.position;
	m_orientation = message.orientation;
	m_rotation.setDegrees(message.rotation);
	m_velocity = message.velocity;
	//m_totalForce = message.totalForce;

	
}

	

