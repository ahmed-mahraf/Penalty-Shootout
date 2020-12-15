/*!
\file game.cpp
*/

#include "game.h"
#include "stdlib.h"

//! Function to construct the game.
Game::Game()
{
	// Set the camera viewpoint
	m_view.setCenter(0.f, 0.f);
	m_view.setSize(m_worldSize);

	m_pWorld = new b2World(mk_gravity); // Add gravity to world

	m_debugDraw.setWorld(m_pWorld); // draw world for debugging
	
	// Load sound from files
	directionBuffer.loadFromFile(".\\assets\\audio\\Direction.WAV");
	kickBuffer.loadFromFile(".\\assets\\audio\\Kick.WAV");
	
	// Set sound from files 
	directionSound.setBuffer(directionBuffer);
	kickSound.setBuffer(kickBuffer);

	// Make the Pitch
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(3.0f, -2.f), sf::Vector2f(2.0f, 0.1f), 0.f, sf::Color::White)); // Top of the StaticBlock (Right Box)
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(-3.0f, -2.f), sf::Vector2f(2.0f, 0.1f), 0.f, sf::Color::White)); // Top of the StaticBlock (Left Box)
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(0.f, 2.f), sf::Vector2f(8.0f, 0.1f), 0.f, sf::Color::White)); // Down of the StaticBlock
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(-4.f, 0.0f), sf::Vector2f(4.0f, 0.1f), 90.f, sf::Color::White)); // Left of the StaticBlock
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(4.f, 0.0f), sf::Vector2f(4.0f, 0.1f), 90.f, sf::Color::White)); // Right of the StaticBlock

	// Make the Net
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(0.0f, -3.f), sf::Vector2f(4.2f, 0.2f), 0.f, sf::Color::White)); // Left side of the Net (Right Box)
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(-2.0f, -2.45f), sf::Vector2f(1.0f, 0.2f), 90.f, sf::Color::White)); // Top of the Net (Left Box)
	m_staticBlocks.push_back(StaticBlock(m_pWorld, sf::Vector2f(2.f, -2.45f), sf::Vector2f(1.0f, 0.2f), 90.f, sf::Color::White)); // Right side of the StaticBlock

	// Make the Football
	m_playerDirection = m_fStartingDirection;
	m_ballTexture.loadFromFile(".\\assets\\textures\\Football.PNG");
	m_ball = DynamicCircle(m_pWorld, sf::Vector2f(0.f, 0.f), 0.15f, m_playerDirection, sf::Color::White);
	m_ball.setTexture(&m_ballTexture);
	m_ray = Ray(m_pWorld, 20.f, sf::Color::Magenta);

	// Make the Goalkeeper
	m_GKTexture.loadFromFile(".\\assets\\textures\\GK.PNG");
	m_GK = KinematicBlock(m_pWorld, sf::Vector2f(0.f, -1.5f), sf::Vector2f(0.3f, 0.3f), 0.f, sf::Color::White);
	m_GK.setTexture(&m_GKTexture);

	// Make the Goal Sensor
	m_goal = GoalSensor(m_pWorld, sf::Vector2f(0.0f, -2.19f), sf::Vector2f(4.f, 0.25f), 0.f);

	// Set all the Userdatas
	for (StaticBlock& block : m_staticBlocks) block.setUserData(new std::pair<std::string, void *>(typeid(decltype(block)).name(), &block)); // Set Userdata of ball
	m_ball.setUserData(new std::pair<std::string, void *>(typeid(decltype(m_ball)).name(), &m_ball)); // Set Userdata of ball 
	m_GK.setUserData(new std::pair<std::string, void *>(typeid(decltype(m_GK)).name(), &m_GK)); // Set Userdata of GK 
	m_goal.setUserData(new std::pair<std::string, void *>(typeid(decltype(m_goal)).name(), &m_goal));

	m_pWorld->SetContactListener(&m_listener); // Listener is declared


}

//! Function to destruct the game.
Game::~Game()
{
	delete m_pWorld;
	m_pWorld = nullptr;
}

//! Function to update game
/*!
\param timestep a float - the time elapsed.
*/
void Game::update(float timestep)
{
	// Update the world
	m_pWorld->Step(timestep, mk_iVelIterations, mk_iVelIterations);

	// Update each dyanmic element - effectively update render information
	m_ball.update();
	m_GK.update();

	if (m_ball.isStopped()) {
		m_ray.setDirection(m_playerDirection);
		m_ray.cast(m_ball.getPosition());
	}

	// Update the HUD
	m_HUD.HUD_PlayerPoints.setString("Player: " + std::to_string(m_listener.getPlayerScore())); // Draws the Player Points as a String.
	m_HUD.HUD_CPUPoints.setString("CPU: " + std::to_string(m_listener.getCPUScore())); // Draws the CPU Points as a String.

	// Reset the ball position
	resetBall();

	// Finish game
	finishGame();

	// Delete debug shapes
	if (m_debug) m_debugDraw.clear();
}

//! Function to draw the game
/*!
\param target a RenderTarget - draw 2D entities.
\param states a RenderStates - transform 2d entities.
*/
void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const //! Draws the shapes
{
	// Set the view
	target.setView(m_view);

	// Draw everything
	target.draw(m_pitchTexture);
	target.draw(m_ball);
	if (m_ball.isStopped()) target.draw(m_ray);
	target.draw(m_goal);
	target.draw(m_GK);
	target.draw(m_HUD);
	for (StaticBlock StaticBlock : m_staticBlocks) target.draw(StaticBlock);
	

	// Debug Draw
	if (m_debug) target.draw(m_debugDraw);
}

//! Function to toggle the debugging option
void Game::toggleDebug()
{
	m_debug = !m_debug; // Debug toggle switches
}

//! Function to process what key is being pressed
/*!
\param code a Keyboard::Key - check what key is pressed.
*/
void Game::processKeyPress(sf::Keyboard::Key code)
{
	switch (code)
	{
	case sf::Keyboard::Tab: // Debug button
		toggleDebug();
		break;
	case sf::Keyboard::Space: // Kick button
		if (m_ball.isStopped())
		{
			m_GK.posDecision();
			kickSound.play();
			m_ball.applyImpulse(b2Vec2(0.25f * cosf(m_playerDirection), 0.25f * sinf(m_playerDirection))); // Using Euler integration 
		}
		break;
	case sf::Keyboard::Right: // Ray cast Right button
		if (m_playerDirection < (m_fStartingDirection + m_fTurningPoint))
		{
			directionSound.play();
			m_playerDirection += m_fTurningPoint;
		}
		break;

	case sf::Keyboard::Left: // Ray cast Left button
		if (m_playerDirection > (m_fStartingDirection - m_fTurningPoint))
		{
			directionSound.play();
			m_playerDirection -= m_fTurningPoint;
		}
		break;
	}
}

//! Function to reset the ball
void Game::resetBall()
{
	b2Body* body = m_listener.getBallBody();
	if (body != nullptr)
	{ 
		// Reset attributes of body
		body->SetTransform(b2Vec2(m_startPositionBall.x, m_startPositionBall.y), m_fStartingDirection); 
		body->SetLinearVelocity(b2Vec2(0.f, 0.f));
		body->SetAngularVelocity(0.f);
		m_listener.clearBallBody();
	}
}

//! Function to finish and end the game
bool Game::finishGame()
{
	// If player reaches 10 points player wins
	if (m_listener.iPlayerPoints == 10)
	{
		m_HUD.HUD_Text.setString("Player wins"); // Draws the Player Points as a String.
		std::cout << "Player Wins!" << std::endl;
		return true; 
	}

	// If player reaches 10 points player wins
	else if (m_listener.iCPUPoints == 10)
	{
		m_HUD.HUD_Text.setString("CPU wins"); // Draws the CPU Points as a String.
		std::cout << "CPU Wins!" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

