/*!
\file HUD.cpp
*/

#include "HUD.h" 

/*! \class Ray
\brief A class where the HUD is created
*/

//! Function to create the HUD
HUD::HUD()
{
	m_HUDFont.loadFromFile(".\\assets\\fonts\\8bit.TTF"); // Load the font

	// Set values for Player HUD
	HUD_PlayerPoints.setFont(m_HUDFont); 
	HUD_PlayerPoints.setCharacterSize(50); 
	HUD_PlayerPoints.setPosition(-3.5f, -2.675f); 
	HUD_PlayerPoints.setScale(0.005f, 0.005f);
	HUD_PlayerPoints.setFillColor(sf::Color::White);

	// Set values for CPU HUD
	HUD_CPUPoints.setFont(m_HUDFont);
	HUD_CPUPoints.setCharacterSize(50);
	HUD_CPUPoints.setPosition(2.75f, -2.675f);
	HUD_CPUPoints.setScale(0.005f, 0.005f);
	HUD_CPUPoints.setFillColor(sf::Color::White);

	// Set values for Textbox HUD
	HUD_Text.setFont(m_HUDFont);
	HUD_Text.setCharacterSize(50);
	HUD_Text.setPosition(0.f, 0.f); 
	HUD_Text.setScale(0.005f, 0.005f);
	HUD_Text.setFillColor(sf::Color::White);
	HUD_Text.setString("");
}

//! Function to draw the dynamic circle
/*!
\param target a RenderTarget - draw 2D entities.
\param states a RenderStates - transform 2d entities.
*/
void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// Draw the HUD into GAME_CPP
	target.draw(HUD_PlayerPoints);
	target.draw(HUD_CPUPoints);
	target.draw(HUD_Text);
}