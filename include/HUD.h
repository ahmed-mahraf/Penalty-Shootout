#pragma once

/*!
\file HUD.h
*/

#include <SFML\Graphics.hpp>

class HUD : public sf::Text 
{
private:
	sf::Font m_HUDFont; //!< Declares the font from SFML Libraries
public:
	HUD();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const; //!< Drawing function - Draws HUD class to Game, Game to main.

	sf::Text HUD_PlayerPoints; //!< Declares Player Points
	sf::Text HUD_CPUPoints; //!< Declares CPU Points
	sf::Text HUD_Text; //!< Declares CPU Points
};
