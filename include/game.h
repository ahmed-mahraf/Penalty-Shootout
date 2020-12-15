#pragma once

/*!
\file game.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "dynamicCircle.h"
#include "staticBlock.h"
#include "staticSensor.h"
#include "kinematicBlock.h"

#include "goalSensor.h"

#include "ray.h"

#include "HUD.h"
#include "textures.h"

#include "contactListener.h"

#include "SFMLDebugDraw.h"

#define DEG2RAD 0.017453f
#define RAD2DEG 57.29577f
#define _USE_MATH_DEFINES

#include <math.h>

/*! \class Game
\brief Holds all information about the game, blocks, balls etc and allows updating and rendering.
*/

class Game : public sf::Drawable {
private:
	sf::View m_view; //!< The view maps from physical co-ordinates to rendering co-ordinates
	sf::Vector2f m_worldSize = sf::Vector2f(8.f, 6.f); //!< Size of the physical worlds is 8 X 6 metres

	b2World* m_pWorld = nullptr; //!< Pointer to the Box2D world.  Using pointers as BOX2D has it's own memory management
	const int mk_iVelIterations = 7; //!< On each update there will be 7 velocity iterations in the physics engine
	const int mk_iPosIterations = 5; //!< On each update there will be 5 position iterations on each update
	const b2Vec2 mk_gravity = b2Vec2(0.f, 0.f); //!< Standard earth gravity will be used (negate the value ofcourse!)

	std::vector<StaticBlock> m_staticBlocks; //!< A collection of fixed blocks.
	DynamicCircle m_ball; //!< A moving balls
	KinematicBlock m_GK;

	Ray m_ray; //!< A ray in the direction of the ball
	float m_playerDirection; //!< Angle heading to fire the ball in radians

	GoalSensor m_goal; //!< Sensor for detecting a goal

	float m_fStartingDirection = -1.5725f; //!< The starting direction of the ball.
	float m_fTurningPoint = 0.65f; //!<  The turning point of the ball.
	sf::Vector2f m_startPositionBall = sf::Vector2f(0.f, 0.f); //!< The start position of the ball.

	Textures m_pitchTexture; //!< Image for the pitch
	sf::Texture m_ballTexture; //!< Image for the ball
	sf::Texture m_GKTexture; //!< Image for the ball

	sf::SoundBuffer directionBuffer; //!< Direction Buffer is called
	sf::SoundBuffer kickBuffer; //!< Kick Buffer is called
	sf::Sound directionSound; //!< Direction sound is declared
	sf::Sound kickSound; //!< Kick sound is declared

	HUD m_HUD; //!< Sets the HUD class as a Function.
	ContactListener m_listener; //!< Contact listener for collisions
	bool m_debug = false; //!< Toggle for debug drawing
	SFMLDebugDraw m_debugDraw; //!< Box2D debug drawing
	bool m_started = false;//!< Toggle to stop sticky spacebar
public:
	Game(); //!< Constructor which sets up the game
	~Game(); //!< Destructor which cleans all the pointer memory up
	void update(float timestep); //!< Update the game with give timestep
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Draw the game to the render context
	void toggleDebug(); //!< Toggle for debug drawing
	void processKeyPress(sf::Keyboard::Key code); //!< Process user key press
	void resetBall(); //!< Declared to reset ball
	bool finishGame(); //!< Declared to finish the game
};