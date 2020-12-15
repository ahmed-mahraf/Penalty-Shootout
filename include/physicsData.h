#pragma once

/*!
\file physicsData.h
*/

#include <Box2D/Box2D.h>

#define DEG2RAD 0.017453f
#define RAD2DEG 57.29577f

/*!
\class PhysicsData
\brief A simple class with common attributes and a few const values used in a few places.
*/

class PhysicsData {
protected:
	b2Body * m_body = nullptr; //!< Box2D body, no need to delete this as BOX2D will look after it
	float mk_fDensity = 1.7f; //!< Density of the material - used to give mass
	float mk_fFriction = 0.1f; //!< Friction - I guess this is only friction from movement, not when static
	float mk_fRestitution = 0.2f; //!< Restitution - bouncy-ness of stuff
public: 
	PhysicsData() {};
	void setUserData(void* data) { m_body->SetUserData(data); }; //!< Set the userdata of the body
};
