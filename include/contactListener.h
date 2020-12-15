#pragma once

/*!
\file contactListener.h
*/

#include <Box2D\Box2D.h>
#include <SFML/Audio.hpp>

#include "dynamicCircle.h"
#include "staticBlock.h"
#include "kinematicBlock.h"
#include "staticSensor.h"
#include "goalSensor.h"

/*! \class ContactListener
\brief A listener which listens for contacts between balls, blocks and sensors.
*/

class ContactListener : public b2ContactListener
{
private:
	b2Body * collisionBallBody; //!< Get the body when collision happens
public:
	ContactListener() {}; //!< Default constructor
	int iPlayerPoints = 0; //!< Player points
	int iCPUPoints = 0; //!< CPU points

	sf::SoundBuffer hitBuffer; //!< Hit sound buffer
	sf::SoundBuffer missBuffer; //!< Miss sound buffer
	sf::Sound hitSound; //!< Hit sound 
	sf::Sound missSound; //!< Miss sound


	void BeginContact(b2Contact* contact); //!< Called when two fixtures begin to touch
	void EndContact(b2Contact* contact); //!< Called when two fixtures cease to 
	void clearBallBody(); //!< Called when collision happens with ball
	int getPlayerScore(); //!< Called when collision happens with ball and sensor
	int getCPUScore(); //!< Called when collision happens with ball and block
	b2Body* getBallBody(); //!< Get the body
};
