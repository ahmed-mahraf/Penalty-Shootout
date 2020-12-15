#pragma once

/*!
\file dynamicCircle.h
*/

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "physicsData.h"

/*! 
\class DynamicCircle
\brief A simple circle which can move, rotate and collide with stuff
*/

class DynamicCircle : public sf::CircleShape, public PhysicsData
{
private:
	bool m_stopped = false;
public:
	DynamicCircle() {}; //!< Default constructor
	DynamicCircle(b2World * world, const sf::Vector2f& position, const float radius, const float orientation, sf::Color); //!< Complete contructor
	void update(); //!< Update rendering infomation 
	void draw(sf::RenderTarget &target, sf::RenderStates states) const; //!< Overridden drawing methos to include line to allow users to see oreintation of the ball
	void applyImpulse(b2Vec2 impulse); //!< Apply impulse to the body
	void accel(b2Vec2 acc);//!< Apply force to the body
	void posReset(b2Vec2 startingPosition, float startingAngle); //!< Reset position of the body
	bool isStopped() const; //!< Has the circle stopped moving
};
