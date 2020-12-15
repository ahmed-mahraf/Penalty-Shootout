/*!
\file goalSensor.cpp
*/

#include "goalSensor.h"

//! Function to create a goal sensor
/*!
\param world a b2World class - the world vector.
\param position a Vector2f - the position of the rectangle.
\param size a Vector2f - the size of the rectangle.
\param orientation a float - the orientation of the rectangle.
*/
GoalSensor::GoalSensor(b2World * world, sf::Vector2f position, sf::Vector2f size, float orientation)
{
	initRectangle(world, position, size, orientation); // Set goal sensor attributes
	setFillColor(sf::Color::Yellow); // Set goal sensor color
}

//! Function to detect if sensor got hit
/*!
\param other a b2Body - check if body is hit.
*/
void GoalSensor::onAction(b2Body * other)
{
	
}

//! Function to detect if sensor hit stops
/*!
\param other a b2Body - check if body stopped.
*/
void GoalSensor::offAction(b2Body * other)
{

}

