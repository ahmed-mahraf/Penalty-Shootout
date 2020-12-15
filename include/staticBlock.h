#pragma once

/*!
\file staticBlock.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "physicsData.h"

/*! \class staticBlock
\brief A simple block which can not move or rotate but can collide with stuff
*/

class StaticBlock : public sf::RectangleShape, public PhysicsData
{
public:
	StaticBlock() {}; //!< Default constructor
	StaticBlock(b2World * world, const sf::Vector2f& position, const sf::Vector2f& size, const float& orientation, sf::Color); //!< Complete contructor
};