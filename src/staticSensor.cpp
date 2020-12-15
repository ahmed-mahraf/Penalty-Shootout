/*!
\file staticSensor.cpp
*/

#include "staticSensor.h"

StaticSensor::StaticSensor()
{

}

//! Function to create a rectangle
/*!
\param world a b2World class - the world vector.
\param position a Vector2f - the position of the rectangle.
\param size a float - the size of the rectangle.
\param orientation a float - the orientation of the rectangle.
*/
void StaticSensor::initRectangle(b2World * world, sf::Vector2f position, sf::Vector2f size, float orientation)
{
	// Instantiate a body definition
	b2BodyDef l_bodyDef; 
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;

	// Set the body position & angle
	l_bodyDef.position.Set(position.x, position.y); 
	l_bodyDef.angle = orientation * DEG2RAD; 
	
	m_body = world->CreateBody(&l_bodyDef); // Attach the bodyDef into the world

	// Set the box shape & radius
	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;

	// Initialise the data fo the fixture definition
	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;

	l_fixtureDef.shape = &l_shape; // Attach the fixture definition of the shape into the shape

	l_fixtureDef.isSensor = true; // Make it a sensor

	m_body->CreateFixture(&l_fixtureDef); // Create the fixtureDef into the Body

	// Set the transformations as their passed values
	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(orientation); 
}

//! Function to create a circle
/*!
\param world a b2World class - the world vector.
\param position a Vector2f - the position of the circle.
\param radius a float - the radius of the circle.
*/
void StaticSensor::initCircle(b2World * world, sf::Vector2f position, float radius)
{
	// Instantiate a body definition
	b2BodyDef l_bodyDef; 
	b2CircleShape l_shape; 
	b2FixtureDef l_fixtureDef; 

	l_bodyDef.position.Set(position.x, position.y); // Set the body position

	m_body = world->CreateBody(&l_bodyDef); // Attach the bodyDef into the world

	l_shape.m_radius = radius; // Set the shape radius

	// Initialise the data fo the Fixture Definition
	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution; 

	l_fixtureDef.shape = &l_shape; // Attach the fixture definition of the shape into the shape

	l_fixtureDef.isSensor = true; // Make it a sensor

	m_body->CreateFixture(&l_fixtureDef); // Create the fixtureDef into the Body

	// Set the transformations as their passed values
	setPosition(position); 
	setSize(sf::Vector2f(radius * 2.0f, radius * 2.0f));
	setOrigin(getSize() * 0.5f);
}
