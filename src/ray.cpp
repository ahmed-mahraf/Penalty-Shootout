/*!
\file ray.cpp
*/

#include "ray.h"

//! Function to create a ray cast
/*!
\param world a b2World class - the world vector.
\param maxLength a float - the maxLength of the ray.
\param colour a Color - the color of the circle.
*/
Ray::Ray(b2World * world, float maxLength, sf::Color colour)
{
	m_pWorld = world;

	m_direction = 0.f;
	m_maxLength = maxLength;

	m_line.resize(2);
	m_line.setPrimitiveType(sf::Lines);
	m_line[0].color = colour;
	m_line[1].color = colour;
}

//! Function to draw the ray cast
/*!
\param target a RenderTarget - draw 2D entities.
\param states a RenderStates - transform 2d entities.
*/
void Ray::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_line); // Draw the line
}

//! Function to cast the ray
/*!
\param start a Vector2f - get start position.
*/
void Ray::cast(sf::Vector2f start)
{
	// Calculate ray from start in direction with max length
	b2Vec2 p1 = b2Vec2(start.x, start.y);
	b2Vec2 p2 = p1 + m_maxLength * b2Vec2(cosf(m_direction), sinf(m_direction));

	// Cast ray
	b2RayCastInput input;
	input.p1 = p1;
	input.p2 = p2;
	input.maxFraction = 1; // t = 1

	// Check every fixture of every body to find closest
	float closestFraction = input.maxFraction;
	b2Vec2 intersectionNormal(0, 0); // useful if you want to cast additional reflected rays
	for (b2Body* body = m_pWorld->GetBodyList(); body; body = body->GetNext()) {
		for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
			b2RayCastOutput output;
			if (!fixture->RayCast(&output, input, 1))
			{// something went wrong
			}
			//else if (output.fraction < closestFraction) // Use this line if you want the ray to hit sensors
			else if (output.fraction < closestFraction && !fixture->IsSensor())
			{
				closestFraction = output.fraction;
				intersectionNormal = output.normal;
			}
		}
	}

	// Parametric line calculation
	b2Vec2 intersectionPoint = p1 + closestFraction * (p2 - p1);

	// Set render points
	m_line[0].position = start;
	m_line[1].position = sf::Vector2f(intersectionPoint.x, intersectionPoint.y);
}

//! Function to set direction of ray cast
/*!
\param direction a float - get direction of ray.
*/
void Ray::setDirection(float direction)
{
	m_direction = direction;
}
