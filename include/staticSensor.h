#pragma once

/*!
\file staticSensor.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "physicsData.h"

/*! 
\class StaticSensor
\brief A simple block which can not move or rotate and does not coliide with circles
*/

class StaticSensor : public sf::RectangleShape, public PhysicsData
{
public:
	StaticSensor(); //!< Complete constructor
	void initRectangle(b2World * world, sf::Vector2f position, sf::Vector2f size, float orientation); //!< Creating a rectangle sensor
	void initCircle(b2World * world, sf::Vector2f position, float radius); //!< Creating a circle sensor
	virtual void onAction(b2Body * other) = 0; //!< Thing the sensor does when hit
	virtual void offAction(b2Body * other) = 0; //!< Thing the sensor does when hit stops
};