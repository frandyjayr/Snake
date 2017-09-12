#ifndef FOOD_HPP
#define FOOD_HPP

#include <SFML/Graphics.hpp>

#include <stdlib.h>
#include <time.h>

#include "ResourceHolder.hpp"


class Food
{
	public:
								Food(sf::RenderWindow& window, ResourceHolder& textureHolder);
		sf::Vector2f			getFoodLocation();
		void					generateNewFood();
		void					renderFood();

	private:
		sf::Vector2f			randomizeLocation();
		void					setFoodLocation();

	private:
		sf::Sprite			    food;
		sf::Vector2f			foodLocation;
		sf::RenderWindow&		window;
		sf::Sound				biteSound;
};
#endif