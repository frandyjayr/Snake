#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector>
#include <deque>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Food.hpp"
#include "ResourceHolder.hpp"

#define BODY_DIMENSIONS 32
#define SPEED_RATE 0.3
#define SPEED_BOOST 0.2
#define STARTING_DIRECTION Right
#define STARTING_LENGTH 3
#define STARTING_SPEED 1

struct SnakeNode
{
	sf::Sprite body;
	sf::Vector2f location;
};

namespace BodyType
{
	enum Type { Head, Torso };
}

enum Direction { Down, Left, Right, Up };

class Snake
{
	public:
											Snake(sf::RenderWindow& window, ResourceHolder& textureHolder);
		void								renderSnake();
		void								moveForward(sf::Time deltaTime);
		void								changeDirection(Direction direction);
		bool								collidesWithFood(std::unique_ptr<Food>& food);
		int									getLength();

	private:
		int									length;
		double								speed;
		std::deque<SnakeNode>				snakeBody;
		Direction							directionFacing;
		sf::RenderWindow&					window;
		sf::Time							time;
		sf::Sprite							torso;
		sf::Sprite							head;
		sf::Sound							deathSound;

	private:
		void								initializeDeque();
		struct SnakeNode					initializeSnakeBody(sf::Vector2f location, BodyType::Type type);
		sf::Vector2f						getOffset(sf::Vector2f position);
		void								increaseSpeed();
		void								increaseSize();
		void								resetGame();
		void								resetSize();
		void								resetSpeed();
		bool								collidesWithSelf();
		bool								collidesWithWall();
};
#endif