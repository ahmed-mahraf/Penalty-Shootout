#pragma once

/*!
\file kinematicBlock.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "physicsData.h"
#include <stdlib.h>

/*! \class kinematicBlock
\brief A simple block which can move only left to right but can collide with stuff
*/

class KinematicBlock : public sf::RectangleShape, public PhysicsData
{
public:
	KinematicBlock() {}; //!< Default constructor
	KinematicBlock(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, const float& orientation, sf::Color); //!< Complete contructor
	void update(); //!< update function
	void posDecision(); //!< Random value to move block
};