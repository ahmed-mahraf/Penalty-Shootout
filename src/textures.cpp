/*!
\file textures.cpp
*/

#include "textures.h"

//! Function to create a pitch texture
Textures::Textures()
{
	pitchTexture.loadFromFile(".\\assets\\textures\\Pitch.PNG"); // Loads up the texture of the pitch
	m_bodyShape.setOrigin(m_bodyShape.getSize().x / 2.0f, m_bodyShape.getSize().y / 2.0f); // Sets the center point of the object using half extents
	m_bodyShape.setPosition(-4.f, -3.f); // Sets the body position
	m_bodyShape.setSize(sf::Vector2f(8.0f, 6.0f));  // Sets the body size
	m_bodyShape.setTexture(&pitchTexture); // References the texture using a pointer
}
//! Function to update the body
/*!
\param fTimeElapsed a float - check the time elapsed.
*/
void Textures::update(float fTimeElapsed)
{
	
}

//! Function to draw the texture
/*!
\param target a RenderTarget - draw 2D entities.
\param states a RenderStates - transform 2d entities.
*/
void Textures::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_bodyShape); // Draw the textured vector.
}
