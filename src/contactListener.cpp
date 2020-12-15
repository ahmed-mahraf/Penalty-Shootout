/*!
\file contactListener.cpp
*/

#include "contactListener.h"

//! Function to check collision on contact
/*!
\param contact a b2Contact - the contact class.
*/
void ContactListener::BeginContact(b2Contact * contact)
{
	// Load sound from files
	hitBuffer.loadFromFile(".\\assets\\audio\\Hit.WAV");
	missBuffer.loadFromFile(".\\assets\\audio\\Miss.WAV");

	// Set the sound source
	hitSound.setBuffer(hitBuffer);
	missSound.setBuffer(missBuffer);

	// Get the contact data from collision body
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	// Return value if collision is there
	bool isSensorA = contact->GetFixtureA()->IsSensor();
	bool isSensorB = contact->GetFixtureB()->IsSensor();

	// Get user data set as pairs
	std::pair<std::string, void *> dataA = *(std::pair<std::string, void *>*) bodyA->GetUserData();
	std::pair<std::string, void *> dataB = *(std::pair<std::string, void *>*) bodyB->GetUserData();

	// If sensor and ball collides play sound and increase player score
	if (typeid(GoalSensor).name() == dataA.first)
	{
		if (typeid(DynamicCircle).name() == dataB.first)
		{
			DynamicCircle * ball = static_cast<DynamicCircle*>(dataB.second);
			if (ball != nullptr)
			{
				collisionBallBody = bodyB;
				hitSound.play();
				iPlayerPoints++;
			}
		}
	}

	// If ball and sensor collides play sound and increase player score
	if (typeid(GoalSensor).name() == dataB.first)
	{
		if (typeid(DynamicCircle).name() == dataA.first)
		{
			DynamicCircle * ball = static_cast<DynamicCircle*>(dataA.second);
			if (ball != nullptr) 
			{ 
				collisionBallBody = bodyA;
				hitSound.play();
				iPlayerPoints++;
			}
		}
	}

	// If block and ball collides play sound and increase CPU score
	if (typeid(KinematicBlock).name() == dataA.first)
	{
		if (typeid(DynamicCircle).name() == dataB.first)
		{
			DynamicCircle * ball = static_cast<DynamicCircle*>(dataB.second);
			if (ball != nullptr) 
			{ 
				collisionBallBody = bodyB;
				missSound.play();
				iCPUPoints++;
			}
		}
	}

	// If ball and block collides play sound and increase CPU score
	if (typeid(KinematicBlock).name() == dataB.first)
	{
		if (typeid(DynamicCircle).name() == dataA.first)
		{
			DynamicCircle * ball = static_cast<DynamicCircle*>(dataA.second);
			if (ball != nullptr) 
			{ 
				collisionBallBody = bodyA;
				missSound.play();
				iCPUPoints++;
			}
		}
	}
}

//! Function to check collision on end contact
/*!
\param contact a b2Contact - the contact class.
*/
void ContactListener::EndContact(b2Contact * contact)
{
	// Get the contact data from collision body
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();

	// Return value if collision is there
	bool isSensorA = contact->GetFixtureA()->IsSensor();
	bool isSensorB = contact->GetFixtureB()->IsSensor();
}

//! Function to clear ball body
void ContactListener::clearBallBody()
{
	collisionBallBody = nullptr; // value is null pointer
}

//! Function to get player score
int ContactListener::getPlayerScore()
{
	return iPlayerPoints; // return value of player points
}

//! Function to get CPU score
int ContactListener::getCPUScore()
{
	return iCPUPoints; // return value of CPU points
}

//! Function to get ball body
b2Body * ContactListener::getBallBody()
{
	return collisionBallBody; // return collision data on ball body
}
