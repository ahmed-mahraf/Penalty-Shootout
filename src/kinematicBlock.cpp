/*!
\file kinematicBlock.cpp
*/

#include "kinematicBlock.h"

//! Function to create a static block
/*!
\param world a b2World class - the world vector.
\param position a Vector2f - the position of the block.
\param size a const Vector2f - the radius of the block.
\param orientation a const float - the orientation of the block.
\param color a Color - the color of the circle.
*/
KinematicBlock::KinematicBlock(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, const float& orientation, sf::Color color)
{
	// Instantiate a body definition
	b2BodyDef l_bodyDef;
	b2PolygonShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.type = b2_kinematicBody; // Set the body type as Kinematic

	// Set the body position & angle
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = orientation * DEG2RAD;

	m_body = world->CreateBody(&l_bodyDef); // Attach the bodyDef into the world

	// Set the shape box & radius
	l_shape.SetAsBox(size.x * 0.5f, size.y * 0.5f);
	l_shape.m_radius = 0.0f;

	// Initialise the data fo the fixture definition
	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;

	l_fixtureDef.shape = &l_shape; // Attach the fixture definition of the shape into the shape

	m_body->CreateFixture(&l_fixtureDef); // Create the fixtureDef into the Body

	// Set the transformations as their passed values
	setPosition(position);
	setSize(size);
	setOrigin(size * 0.5f);
	setRotation(orientation);
	setFillColor(color);
	setOutlineThickness(0.f);
}

//! Function to update the static block
void KinematicBlock::update()
{
	// Update the circle values
	b2Vec2 pos = m_body->GetPosition();
	setPosition(pos.x, pos.y);
	float angle = m_body->GetAngle()* RAD2DEG;
	setRotation(angle);
}

//! Function to update the static block
void KinematicBlock::posDecision()
{
	// Get a number between 0 - 11
	int iNumber = rand() % 11 + 0;

	// If numbers are 0, 1, 2, 3 go left
	if (iNumber >= 0 && iNumber <= 3) 
	{
		m_body->SetTransform(b2Vec2(-1.25f, -1.5f), 0.f);
	}

	// If numbers are 4, 5, 6, 7 go middle
	else if (iNumber >= 4 && iNumber <= 7)
	{
		m_body->SetTransform(b2Vec2(0.f, -1.5f), 0.f); 
	}

	// If numbers are 8, 9, 10, 11 go right
	else if (iNumber >= 8 && iNumber <= 11)
	{
		m_body->SetTransform(b2Vec2(1.25f, -1.5f), 0.f);
	}
}
