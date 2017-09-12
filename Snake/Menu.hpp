#ifndef MENU_HPP
#define MENU_HPP

#include "GameState.hpp"
#include "ResourceHolder.hpp"

#define MUSIC_VOLUME 70

namespace MenuState 
{ 
	enum ID { Exit, Neutral, Play };
};

class Menu : public GameState
{
	public:
								Menu(sf::RenderWindow& window);
		bool					inGameMenu();
		void					renderMenu();
		void					run();

	private:
		void					processEvents();
		void					update();
		void					handlePlayerInput(sf::Mouse::Button button, bool isPressed);
		void					handleMousePosition();
		void					loadTextures();
		void					loadSoundBuffers();
		void					setTextures();
		void					setSoundBuffers();
		void					setMusic();
		bool					insidePlayButton();
		bool					insideExitButton();

	private:
		bool					inMenu;
		bool					hasNotHoveredButton;
		sf::Texture				neutral;
		sf::Sprite				menuNeutral;
		sf::Sprite				menuPlay;
		sf::Sprite				menuExit;
		sf::RenderWindow&		window;
		MenuState::ID			state;
		ResourceHolder			menuResourceHolder;
		sf::Mouse				mouse;
		sf::Sound				hoverSound;
		sf::Music				menuMusic;


};
#endif