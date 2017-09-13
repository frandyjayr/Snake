#include "Game.hpp"

/*****************************************************************************************************************
 *										Constructor   															 *
 *****************************************************************************************************************
 * Input: sf::RenderWindow																						 *
 * Output: None																									 *
 * Description: The constructor of the game class initializes the render window. It then loads all textures      *
 * soundBuffers, and fonts. It then sets the background of the game and finally initializes instances of the     *
 * Snake, Food, and ScoreBoard classes.																			 *
 ****************************************************************************************************************/
Game::Game(sf::RenderWindow& window) : mWindow(window)
{
	loadTextures();
	loadSoundBuffers();
	loadFonts();
	setBackgroundTile();
	mSnake = std::unique_ptr<Snake>(new Snake(mWindow, gameResourceHolder));
	mFood = std::unique_ptr<Food>(new Food(mWindow, gameResourceHolder));
	mScoreBoard = std::unique_ptr<ScoreBoard>(new ScoreBoard(mWindow, gameResourceHolder));
}

/*****************************************************************************************************************
 *										run()   															     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The following function is used to manage/render all components of the game function while also   *
 * processing any player events and updating any necessary variables within the game. The function encapsualtes  *
 * all of the data of the snake game which include the snake, food, the game board, and any collisions that may  *
 * occur within the game. It also updates the score of the game. The user need not worry about the details of    *
 * game and only need to call the run function to play the entire game gameState.								 *
 ****************************************************************************************************************/
void Game::run()
{
	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;
	
	while (mWindow.isOpen())
	{
		deltaTime = clock.restart();
		processEvents();
		update(deltaTime);
		render();
	}
}

/*****************************************************************************************************************
 *										processEvents()  													     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function is used to process any user events that occur within the menu gamestate. This would *
 * incude whether a button is clicked or if the window is closed. The function specifically processes if the     *
 * user clicks 'W', 'A', 'S', and 'D', changing the direction the snake faces to Up, Left, Down, and Right,      *
 * respectively.																								 *
 ****************************************************************************************************************/
void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		// Check for any key presses and processes if they are relevant keys
		switch (event.type)
		{
			case sf::Event::KeyPressed:
			{
				handlePlayerInput(event.key.code, true);
				break;
			}
			case sf::Event::Closed:
			{
				mWindow.close();
				break;
			}
		}
	}
}

/*****************************************************************************************************************
 *										update()		 													     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The following function is a general update function that updates any classes within the game     *
 * as necessary. In this case, the Snake class is updated every iteration to ensure that it moves the board      *
 * at a given rate per iteration. Also, the snake is checked every iteration to see if it collides with a food   *
 * object. Finally, the score is updated every iteration if necessary if the length of the snake increases or    *
 * decreases																									 *
 ****************************************************************************************************************/
void Game::update(sf::Time deltaTime)
{
	mSnake->moveForward(deltaTime);
	mSnake->collidesWithFood(mFood);
	mScoreBoard->updateScore(mSnake);
}

/*****************************************************************************************************************
 *										render()		 													     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The following function renders all sprites and backgrounds to the screen. The render function    *
 * ensures that the background, snake, food, and scoreboard are rendered per iteration. Before rendering all     *
 * classes, it clears the entire screen to ensure no overlap occurs between images								 *
 ****************************************************************************************************************/
void Game::render()
{
	mWindow.clear();
	renderBackground();
	mScoreBoard->renderScore();
	mSnake->renderSnake();
	mFood->renderFood();
	mWindow.display();
}

/*****************************************************************************************************************
 *										handlePlayerInput() 													 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The following function handles any keyboard input from the user. If 'W', 'S', 'A', or 'D' are    *
 * pressed, their directions are changed accordingly.															 *
 ****************************************************************************************************************/
void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{

	// change the direction the snake if facing
	if (key == sf::Keyboard::W)
	{
		mSnake->changeDirection(Up);
	}
	if (key == sf::Keyboard::S)
	{
		mSnake->changeDirection(Down);
	}
	if (key == sf::Keyboard::A)
	{
		mSnake->changeDirection(Left);
	}
	if (key == sf::Keyboard::D)
	{
		mSnake->changeDirection(Right);
	}

	
}

/*****************************************************************************************************************
 *										loadTextures()  														 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function loads the game's textures into the game's resourceHolder instance for later         *
 * use.																											 *
 ****************************************************************************************************************/
void Game::loadTextures()
{
	gameResourceHolder.loadTextures(Textures::ID::TileSet, "Media/Textures/Textures.png");
	gameResourceHolder.loadTextures(Textures::ID::Background, "Media/Textures/SnakeBoard.png");
	gameResourceHolder.loadTextures(Textures::ID::Head, "Media/Textures/SnakeHead.png");
	gameResourceHolder.loadTextures(Textures::ID::Torso, "Media/Textures/SnakeTorso.png");
	gameResourceHolder.loadTextures(Textures::ID::Veggies, "Media/Textures/Vegies.png");
}

/*****************************************************************************************************************
 *										loadSoundBuffers()  													 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function loads the game's sound buffers into the game's resourceHolder instance for later    *
 * use.																											 *
 ****************************************************************************************************************/
void Game::loadSoundBuffers()
{
	gameResourceHolder.loadSoundBuffers(SoundBuffers::ID::Munch, "Media/SoundBuffers/Munch.wav");
	gameResourceHolder.loadSoundBuffers(SoundBuffers::ID::Death, "Media/SoundBuffers/Lose.wav");
}

/*****************************************************************************************************************
 *										loadFonts													     		 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function loads the game's fonts into the menu's resourceHolder instance for later use	     *
 ****************************************************************************************************************/
void Game::loadFonts()
{
	gameResourceHolder.loadFonts(Fonts::ID::Bauhaus, "Media/Fonts/Bauhaus93.ttf");
}

/*****************************************************************************************************************
 *										setBackgroundTile()														 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function sets the bakcground tile texture used for the game board. This background tile      *
 * is a png image created specifically in a tile format where each tile is 32 x 32 pixels.						 *
 ****************************************************************************************************************/
void Game::setBackgroundTile()
{
	mBackgroundTile.setTexture(gameResourceHolder.getTextures(Textures::ID::Background));
}

/*****************************************************************************************************************
 *										renderBackground()													     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The function renders the background image to the screen. This function must be called within     *
 * some type of game/render loop in order to render the background continuously to the screen.				     *
 ****************************************************************************************************************/
void Game::renderBackground()
{
	mWindow.draw(mBackgroundTile);
}


