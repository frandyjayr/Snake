#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "ResourceHolder.hpp"
#include "Snake.hpp"


class ScoreBoard
{
	public:
								ScoreBoard(sf::RenderWindow& window, ResourceHolder& resourceHolder);
		void					updateScore(std::unique_ptr<Snake>& snake);
		void					renderScore();

	private:
		void					setTextScore();

	private:
		int						scoreNumber;
		sf::RenderWindow&		mWindow;
		sf::Text				counter;
		sf::Text				scoreText;



};
#endif