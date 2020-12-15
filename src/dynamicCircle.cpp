/*!
\file dynamicCircle.cpp
*/

#include "dynamicCircle.h"

//! Function to create a dynamic circle
/*!
\param world a b2World class - the world vector.
\param position a Vector2f - the position of the circle.
\param radius a const float - the radius of the circle.
\param orientation a const float - the orientation of the circle.
\param color a Color - the color of the circle.
*/
DynamicCircle::DynamicCircle(b2World * world, const sf::Vector2f& position, const float radius, const float orientation, sf::Color)
{
	// Instantiate a body definition
	b2BodyDef l_bodyDef;
	b2CircleShape l_shape;
	b2FixtureDef l_fixtureDef;

	l_bodyDef.type = b2_dynamicBody; // Set body definition as Dynamic Body

	// Set the body position & angle
	l_bodyDef.position.Set(position.x, position.y);
	l_bodyDef.angle = orientation * DEG2RAD;

	m_body = world->CreateBody(&l_bodyDef); // Attach the bodyDef into the world

	l_shape.m_radius = radius; // Set the shape radius

	// Initialise the data fo the fixture definition
	l_fixtureDef.density = mk_fDensity;
	l_fixtureDef.friction = mk_fFriction;
	l_fixtureDef.restitution = mk_fRestitution;

	l_fixtureDef.shape = &l_shape; // Attach the fixture definition of the shape into the shape
	
	m_body->CreateFixture(&l_fixtureDef); // Create the fixtureDef into the Body

	// Set the damping data
	m_body->SetLinearDamping(0.2f);
	m_body->SetAngularDamping(0.2f);

	// Set the transformations as their passed values
	setPosition(position);
	setRadius(radius);
	setOrigin(radius, radius);
	setRotation(orientation);
}

void DynamicCircle::update()
{
	// Check whether the circle has stopped (simualated ground friction)
	m_stopped = m_body->GetLinearVelocity().Length() < 0.1f;

	//If stopped trim any remaining velocity
	if (m_stopped)
	{
		m_body->SetLinearVelocity(b2Vec2(0.f, 0.f));
		m_body->SetAngularVelocity(0.0f);
	}

	// Update the circle values
	b2Vec2 pos = m_body->GetPosition();
	setPosition(pos.x, pos.y);
	float angle = m_body->GetAngle()* RAD2DEG;
	setRotation(angle);
}

//! Function to draw the dynamic circle
/*!
\param target a RenderTarget - draw 2D entities.
\param states a RenderStates - transform 2d entities.
*/
void DynamicCircle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw((sf::CircleShape)*this); // Draw the Circle Shape

	// Draw the circle line
	sf::RectangleShape line(sf::Vector2f(getRadius(), 0.01f));
	line.setPosition(getPosition());
	line.setOrigin(0.f, 0.005f);
	line.rotate(getRotation());
	target.draw(line);
}

//! Function to apply impulse to the circle
/*!
\param impulse a b2Vec2 - apply impulse.
*/
void DynamicCircle::applyImpulse(b2Vec2 impulse)
{
	m_body->ApplyLinearImpulseToCenter(impulse, true); // Attaches & returns the impulse value
}

//! Function to add acceleration to the circle
/*!
\param impulse a b2Vec2 - apply impulse.
*/
void DynamicCircle::accel(b2Vec2 accel)
{

}

//! Function to reset the position of the circle
/*!
\param startingPosition a b2Vec2 - detects the starting position.
\param startingAngle a float - detects the starting angle.
*/
void DynamicCircle::posReset(b2Vec2 startingPosition, float startingAngle)
{
	m_body->SetTransform(startingPosition, startingAngle); // Set transformation to the starting position of the circle
}

//! Return the result if ball is stopped
bool DynamicCircle::isStopped() const
{
	return m_stopped; // return the value that it stopped.
}


