#include "engine/RigidBody.h"
#include "engine/Game.h"

int RigidBody::count = 0;

// Always place as last include and only in cpp files!!
#include "foundation/Debug.h"
#include "graphics/EffectIF.h"

//--------------------------------------------------------------------------------
RigidBody::RigidBody(void) :
	m_mass(1.0f),
	m_position(0.0f, 0.0f),
	m_velocity(0.0f, 0.0f),
	m_drag(0.0f),
	m_maxSpeed(1000.0f),
	m_alive(true),
	m_totalForce(0.0f, 0.0f),
	m_group(0),
	m_pEffect(0)
{
	// Set the id
	m_id = count++;
	m_orientation[0] = (float)cos(m_rotation.getRadians());
	m_orientation[1] = (float)sin(m_rotation.getRadians());
}

//--------------------------------------------------------------------------------
void RigidBody::setRotation(float rotation)
{ 
	m_rotation.setDegrees(rotation);
	
	m_orientation[0] = (float)cos(m_rotation.getRadians());
	m_orientation[1] = (float)sin(m_rotation.getRadians());
}

//--------------------------------------------------------------------------------

bool RigidBody::hasCollided(const RigidBody *body) {
	if(!m_alive || !body->m_alive)
		return false;

	//prevent collision detection on self
	if(m_id == body->m_id)
		return false;

	float a = fabs(m_position.x - body->m_position.x);
	float b = fabs(m_position.y - body->m_position.y);

	float distance = sqrt(a*a + b*b);

	if(distance < (m_radius + body->m_radius))
	{
		//printf("distance %f rad1 %f rad2 %f\n", distance, m_radius, body->m_radius);
		return true;
	}

	return false;
}

//--------------------------------------------------------------------------------
void 
RigidBody::applyForce(const Vector2f& force)
{
	if(!m_alive)
		return;

	m_totalForce += force;
}

//--------------------------------------------------------------------------------
void 
RigidBody::move(const float stepSize)
{
	if(!m_alive)
		return;

	// Calculate new velocity
	Vector2f acceleration = m_totalForce / m_mass;
	m_velocity += acceleration * stepSize;
	
	// Apply drag only if no force is acting.
	if(m_totalForce.Length() < EPSILON)
	{
		// Apply the drag and check if the drag is enough to stop the body
		if(m_drag > m_velocity.Length())
		{
			m_velocity.Zero();
		}
		else
		{
			float newSpeed = m_velocity.Length() - m_drag * stepSize;
			m_velocity.Normalise();
			m_velocity *= newSpeed;
		}
	}

	// Check if the velocity is greater than the max velocity
	if(m_velocity.Length() > m_maxSpeed)
	{
		m_velocity.Normalise();
		m_velocity *= m_maxSpeed;
	}

	// Update the position
	m_position += m_velocity * stepSize;
	
	// Set force and torque to zero for next iteration
	m_totalForce.Zero();
}

void RigidBody::setEffect(EffectIF* pEffect) const{
	//if (m_pEffect || pEffect)
	m_pEffect=pEffect;
}