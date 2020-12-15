/**
@file main.cpp
@brief Contains the entry point for the application
*/


/*! \mainpage 2D Simulation - Penalty Shootout
 *
 * design, build and test a 2D sports simulation which is viewed from the top
 * down.
 * 
 * REFERENCES
 *
 *
 * Textures:
 * Pitch - https://pngtree.com/back/down?id=ODg5MTU=&type=1
 * Football - http://pngimg.com/imgs/sport/football/
 * GK - https://pngtree.com/so/goalkeeper
 * 
 * Sound:
 * Kicking The Ball https://freesound.org/people/ProjectsU012/sounds/361005/
 * Move Left and Right - https://freesound.org/people/ProjectsU012/sounds/341657/
 * Keeper Save - https://freesound.org/people/ProjectsU012/sounds/333785/
 * Player Shoots - https://freesound.org/people/ProjectsU012/sounds/360990/
 *
 * Font: https://www.dafont.com/minecraft.font
 * 
 *
 */

#include <Box2D/Box2D.h>

#include <SFML/Graphics.hpp>

#include "game.h"

int main() /** Entry point for the application */
{
	sf::RenderWindow window(sf::VideoMode(1024, 800), "CW Starter"); // Open main window
	Game game;

	float fFrameTime = 1.f / 60.f;

	// Start a clock to provide time for the physics
	sf::Clock clock;

	// Run a game loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// window closed button pressed
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				game.processKeyPress(event.key.code);
			}
		}

		// Find out how much time has elapsed

		float m_fElapsedTime = clock.getElapsedTime().asSeconds();
		// If a frame has past the update the physics
		if (m_fElapsedTime > fFrameTime)
		{
			game.update(m_fElapsedTime);

			if (game.finishGame()) // If 10 points is reached, game is over.
			{
				system("pause");
				return true;
			}
			clock.restart();
		}

		window.clear(sf::Color::Green);
		window.draw(game);
		window.display();
	}
}