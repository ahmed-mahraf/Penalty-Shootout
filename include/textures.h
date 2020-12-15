#pragma once

/*!
\file textures.h
*/

#include <SFML/Graphics.hpp>

/*!
\class Textures
\brief A simple block which can not move or rotate and does not coliide with circles
*/

class Textures : public sf::Drawable
{
private:

public:
	Textures();

	sf::RectangleShape m_bodyShape; //!< Declares the shape.
	sf::Texture pitchTexture; //!< Declares the texture of pitch.

	void update(float fTimeElapsed); //!< Adds an update function. 
	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Draws the texture into the game.
};