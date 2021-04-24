#pragma once

#include "foundation/Vector2f.h"
#include "../../game/engine/RigidBody.h"

//--------------------------------------------------------------------------------
/**
	Generic interface for a graphics effect.
*/
class EffectIF
{
public:
	// Ctor
	EffectIF();

	// Dtor
	virtual ~EffectIF() { }

	// Renders the effect
	virtual void Start() { }

	// Renders the effect
	virtual void Render() { }

	// Updates the effect
	virtual void Update() { }

	//when the ship is killed, but the effect still needs time to terminate
	virtual void Kill() { }

	// Position and rotation getters and setters
	void SetPosition(const Vector2f &p) { m_position = p; }
	void SetRotation(float r) { m_rotation = r; }
	void SetVelocity(const Vector2f& velocity){ m_velocity=velocity; }

	void setTrace(const RigidBody* pBody){ m_pBody=const_cast<RigidBody*>(pBody); }
	
	Vector2f getPosition () const { return m_position; }
	Vector2f getVelocity() const { return m_velocity; }
	float getRotation () const { return m_rotation; }

	// Tells weather the effect is over
	bool isFinished() { return m_isFinished; }

//protected:
	// Sets the finished flag to true
	void terminate() { m_isFinished = true; }

protected:
	Vector2f m_velocity;
	RigidBody* m_pBody;		//body to trace

private:	
	// Positioning
	Vector2f m_position;
	

	float m_rotation;
	
	// Flag indicating whether the effect has finished
	bool m_isFinished;
};