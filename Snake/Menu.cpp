#include "Menu.hpp"

/*****************************************************************************************************************
 *										Constructor   															 *
 *****************************************************************************************************************
 * Input: sf::RenderWindow																						 *
 * Output: None																									 *
 * Description: The constructor initializes the window variable. It also loads all textures, soundBuffers, and   *
 * any background music. Once initialized, it sets the textures, soundBuffers, and music for the game. Finally,  *
 * it sets up the bools for the menu.																			 *
 ****************************************************************************************************************/
Menu::Menu(sf::RenderWindow& window) : window(window)
{
	loadTextures();
	loadSoundBuffers();
	setTextures();
	setSoundBuffers();
	setMusic();
	inMenu = true;
	hasNotHoveredButton = true;
	state = MenuState::ID::Neutral;
}

/*****************************************************************************************************************
 *										inGameMenu()  															 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indicating if the player is still in the Menu screen											 *
 * Description: The bool-returning function will return true if the player is inside the menu gamestate, else    *
 * return false;																								 *
 ****************************************************************************************************************/
bool Menu::inGameMenu()
{
	return inMenu;
}

void Menu::update()
{

}

/*****************************************************************************************************************
 *										processEvents()  													     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function is used to process any user events that occur within the menu gamestate. This would *
 * incude whether a button is clicked or if the window is closed. The function also processes the mouse position *
 * and checks if it should render larger image buttons for the buttons that the mouse is hovering over.          *
 ****************************************************************************************************************/
void Menu::processEvents()
{
	// Update background image if mouse is hovering play or exit button
	handleMousePosition();

	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::MouseButtonPressed:
			{
				handlePlayerInput(event.mouseButton.button, true);
				break;
			}
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
		}
	}
}

/*****************************************************************************************************************
 *										handlePlayerInput()  													 *
 *****************************************************************************************************************
 * Input: sf::Mouse::Button, bool																				 *
 * Output: None																									 *
 * Description: This function handles any player input within the menu gamestate. To be exact, it checks if the  *
 * users left clicks on the area insdie the play or exit button. If so, it responds accordingly.                 *
 ****************************************************************************************************************/
void Menu::handlePlayerInput(sf::Mouse::Button button, bool isPressed)
{
	if (button == sf::Mouse::Left && insidePlayButton())
	{
		// Setting the bool to false will remove the player out of the menu gamestate and into the actual game gamestate
		inMenu = false;
	}
	if (button == sf::Mouse::Left && insideExitButton())
	{
		window.close();
	}
}

/*****************************************************************************************************************
 *										renderMenu()  															 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function renders the menu images. The images are spread into 3 different types: neutral,     *
 * play, and exit. The neutral screen displays the regular game screen. The play and exit screen display screens *
 * in which their respective buttons appear larger than normal, rendering an interactive button to the screen    *
 ****************************************************************************************************************/
void Menu::renderMenu()
{
	while (window.isOpen() && inGameMenu())
	{
		window.clear();
		processEvents();
		update();
		// The three menu states create an interactive menu
		if (state == MenuState::ID::Neutral)
		{
			window.draw(menuNeutral);
		}
		else if (state == MenuState::ID::Play)
		{
			window.draw(menuPlay);
		}
		else if (state == MenuState::ID::Exit)
		{
			window.draw(menuExit);
		}
		window.display();
	}
	window.clear();
}

/*****************************************************************************************************************
 *										run()		  															 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																								     *
 * Description: Virtual function that runs the menu gamestate, rendering the images, playing the music, and      *
 * stopping the music once the gamestate has ended																 *
 ****************************************************************************************************************/
void Menu::run()
{
	menuMusic.play();
	renderMenu();
	menuMusic.stop();
}

/*****************************************************************************************************************
 *										loadSoundBuffers()  													 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function loads the game's sound buffers into the menu's resourceHolder instance for later    *
 * use.																											 *
 ****************************************************************************************************************/
void Menu::loadSoundBuffers()
{
	menuResourceHolder.loadSoundBuffers(SoundBuffers::ID::Hover, "Media/SoundBuffers/Hover.wav");
}

/*****************************************************************************************************************
 *										loadTextures()  														 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function loads the game's textures into the menu's resourceHolder instance for later         *
 * use.																											 *
 ****************************************************************************************************************/
void Menu::loadTextures()
{
	menuResourceHolder.loadTextures(Textures::ID::MenuNeutral, "Media/Textures/Menu/LoadScreenNeutral.png");
	menuResourceHolder.loadTextures(Textures::ID::MenuPlay, "Media/Textures/Menu/LoadScreenPlay.png");
	menuResourceHolder.loadTextures(Textures::ID::MenuExit, "Media/Textures/Menu/LoadScreenExit.png");
}

/*****************************************************************************************************************
 *										loadTextures()  														 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function loads the game's textures into the menu's resourceHolder instance for later         *
 * use.																											 *
 ****************************************************************************************************************/
void Menu::setTextures()
{
	menuNeutral.setTexture(menuResourceHolder.getTextures(Textures::ID::MenuNeutral));
	menuPlay.setTexture(menuResourceHolder.getTextures(Textures::ID::MenuPlay));
	menuExit.setTexture(menuResourceHolder.getTextures(Textures::ID::MenuExit));
}

/*****************************************************************************************************************
 *										setSoundBuffers()  														 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function sets the sound buffer for the game. The soundBuffer for the menu include the hover  *
 * sound that occurs in the menu when the player hovers their mouse over the play or exit buttons                *
 ****************************************************************************************************************/
void Menu::setSoundBuffers()
{
	hoverSound.setBuffer(menuResourceHolder.getSoundBuffers(SoundBuffers::ID::Hover));
}

/*****************************************************************************************************************
 *										setMusic()  														     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function sets the background for the game menu.                                              *
 ****************************************************************************************************************/
void Menu::setMusic()
{
	menuMusic.openFromFile("Media/SoundBuffers/MenuBackgroundSong.ogg");
	menuMusic.setVolume(MUSIC_VOLUME);
}

/*****************************************************************************************************************
 *										handleMousePosition() 												     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function tracks the mouses position and responds accordingly if the mouse is on the play     *
 * or exit buttons. If on the play button or exit button, the image shifts to make the buttons look interactive  *
 * and also play sound effects.																					 *
 ****************************************************************************************************************/
void Menu::handleMousePosition()
{
	sf::Vector2i position = mouse.getPosition();

	if (insidePlayButton())
	{
		// Play MenuState renders a larger play button to make it look/feel interactive
		state = MenuState::ID::Play;
		if (hasNotHoveredButton)
		{
			hoverSound.play();
			hasNotHoveredButton = false;
		}
	}
	else if (insideExitButton())
	{
		//  Exit MenuState renders a larger exit button to make it look/feel interactive
		state = MenuState::ID::Exit;
		if (hasNotHoveredButton)
		{
			hoverSound.play();
			hasNotHoveredButton = false;
		}
	}
	else
	{
		state = MenuState::ID::Neutral;
		hasNotHoveredButton = true;
	}
}

/*****************************************************************************************************************
 *										insidePlayButton()	 												     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool returning if the mouse is within the play button												 *
 * Description: The function tracks if the mouse position is within the play button. If so, it returns true,     *
 * else it will return false																					 *
 ****************************************************************************************************************/
bool Menu::insidePlayButton()
{
	sf::Vector2i position = mouse.getPosition();
	return ((position.x > 738 && position.x < 1132) && (position.y > 555 && position.y < 652));

}

/*****************************************************************************************************************
 *										insideExitButton()	 												     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool returning if the mouse is within the exit button												 *
 * Description: The function tracks if the mouse position is within the exit button. If so, it returns true,     *
 * else it will return false																					 *
 ****************************************************************************************************************/
bool Menu::insideExitButton()
{
	sf::Vector2i position = mouse.getPosition();
	return (((position.x > 740 && position.x < 1146) && (position.y > 716 && position.y < 817)));
}