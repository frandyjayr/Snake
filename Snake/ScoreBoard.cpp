#include "ScoreBoard.hpp"

/*****************************************************************************************************************
 *										Constructor   															 *
 *****************************************************************************************************************
 * Input: sf::RenderWindow, ResourceHolder 																		 *
 * Output: None																									 *
 * Description: The constructor of the score board initializes the render window and the resourceholder, both    *
 * passed as reference. This is because the window and the resourceHolder are defined in the game class where    *
 * all resources are pre-loaded. Therefore, it would be unnecessary to copy all of the resources into this class *
 * The constructor uses the resouceHolder to initialize the font of the scoreBoard. Also, the starting value of  *
 * the score is set to 0.
 ****************************************************************************************************************/
ScoreBoard::ScoreBoard(sf::RenderWindow& window, ResourceHolder& resourceHolder) : mWindow(window)
{
	scoreNumber = 0;
	scoreText.setFont(resourceHolder.getFont(Fonts::ID::Bauhaus));
	scoreText.setString("SCORE: ");
	counter.setFont(resourceHolder.getFont(Fonts::ID::Bauhaus));
	counter.setString(std::to_string(scoreNumber));
	counter.setPosition(sf::Vector2f(100, 0));
}

/*****************************************************************************************************************
 *										updateScore()  															 *
 *****************************************************************************************************************
 * Input: unique_ptr<Snake>																						 *
 * Output: None																									 *
 * Description: The following function updates the score of the game by taking the length of the snake and       *
 * subtracting the STARTING_LENGTH. The purpose of subtracting the starting length is to ensure that the player  *
 * starts at 0 points. If not, the score will start at whatever starting length the snake is at. This is because *
 * the score uses the snake's length to keep track of the score. This makes any snake addition easier, but mroe  *
 * importantly, makes resetting the score easier.																 *
 ****************************************************************************************************************/
void ScoreBoard::updateScore(std::unique_ptr<Snake>& snake)
{
	scoreNumber = snake->getLength() - STARTING_LENGTH;
	setTextScore();
}

/*****************************************************************************************************************
 *										renderScore()  															 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The following renders the score to the screen. The user is responsible for using this function   *
 * within a game/render loop in order to constantly render the score to the screen.								 *
 ****************************************************************************************************************/
void ScoreBoard::renderScore()
{
	mWindow.draw(scoreText);
	mWindow.draw(counter);
}

/*****************************************************************************************************************
 *										Constructor   															 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The following translates the int value of the score into a text value that can be later rendered *
 * to the screen by using the renderScore() function.															 *
 ****************************************************************************************************************/
void ScoreBoard::setTextScore()
{
	std::string text = std::to_string(scoreNumber);
	counter.setString(text);
}
