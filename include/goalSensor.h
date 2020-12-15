#pragma once

/*!
\file goalSensor.h
*/

#include "staticSensor.h"

/*! 
\class GoalSensor
\brief A simple block which can collide with circles
*/

class GoalSensor : public StaticSensor
{
private:

public:
	GoalSensor() {}; //!< Default constructor
	GoalSensor(b2World * world, sf::Vector2f position, sf::Vector2f size, float orientation); //!< Creating goal sensor
	void onAction(b2Body * other); //!< Thing the sensor does when hit
	void offAction(b2Body * other); //!< Thing the sensor does when hit stops
};