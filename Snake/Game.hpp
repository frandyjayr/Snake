#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "Food.hpp"
#include "GameState.hpp"
#include "Menu.hpp"
#include "ScoreBoard.hpp"
#include "Snake.hpp"
#include "ResourceHolder.hpp"

class Game : public GameState
{
	public:
											Game(sf::RenderWindow& window);
		void								run();

	private:
		void								processEvents();
		void								update(sf::Time deltaTime);
		void								render();
		void								handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
		void								loadTextures();
		void								loadSoundBuffers();
		void								loadFonts();
		void								setBackgroundTile();
		void								renderBackground();
		

	private:
		sf::Sprite							mBackgroundTile;
		sf::RenderWindow&					mWindow;
		ResourceHolder						gameResourceHolder;
		std::unique_ptr<Snake>				mSnake;
		std::unique_ptr<Food>				mFood;
		std::unique_ptr<Menu>				mMenu;
		std::unique_ptr<ScoreBoard>			mScoreBoard;

};
#endif
