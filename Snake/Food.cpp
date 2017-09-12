#include "Food.hpp"

/*****************************************************************************************************************
 *										Constructor   															 *
 *****************************************************************************************************************
 * Input: Instance of a RenderWindow and ResourceHolder															 *
 * Output: None																									 *
 * Description: The constructor initializes the window, food sprite's texture, and biteSound's sound buffer.     *
 * It also sets up the first food location by generating its location on the game board and settings its position*
 * It is the respoinsibility of the programmer to pass a RenderWindow and ResourceHolder instance.               *
 ****************************************************************************************************************/

Food::Food(sf::RenderWindow& window, ResourceHolder& resourceHolder) : window(window), food(resourceHolder.getTextures(Textures::ID::Veggies)),
biteSound(resourceHolder.getSoundBuffers(SoundBuffers::ID::Munch))
{
	foodLocation = randomizeLocation();
	// The TileSet the food is located on are based on these coordinates
	food.setTextureRect(sf::IntRect(2 * 32, 0 * 32, 32, 32));
	food.setPosition(foodLocation);
}

/*****************************************************************************************************************
 *										randomizeLocation()														 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: sf::Vector2f																							 *
 * Description: The purpose of this function is to generate the exact x and y location for the next apple in     *
 * game. It uses the rand() function to generate a random number from 0 to the window size of and x and y. The	 *
 * coordinates generated will adapt to the window size, therefore will adjust accordingly if the user wishes to  *
 * change window heights or widths.																				 *
 ****************************************************************************************************************/
sf::Vector2f Food::randomizeLocation()
{
	sf::Vector2f randomLocation;

	/* Get random locations for both x and y for the food's next location. It relies on
	   the game's window dimensions, therefore is adaptable to any window size. */
	randomLocation.x = (rand() % window.getSize().x) / 32;
	randomLocation.y = (rand() % window.getSize().y) / 32;
	randomLocation.x = (int)randomLocation.x * 32;
	randomLocation.y = (int)randomLocation.y * 32;
	
	return randomLocation;
}

/*****************************************************************************************************************
 *										renderFood()															 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The purpose of this function is to render the next apple onto the game screen. This function     *
 * utilizes the private function setFoodLocaiton() to first set the new apple's in the case that the location    *
 * was altered. It then uses the RenderWindow passed as reference to render the image to the screen. It is the   *
 * responsibility of the user to call this function in a loop in order to constantly render the image onto the   *
 * window and to ensure the most recent foodLocation set is being rendered.								         *
 ****************************************************************************************************************/

void Food::renderFood()
{
	setFoodLocation();
	window.draw(food);
}

/*****************************************************************************************************************
 *										generateNewFood()														 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The purpose of this function is set new x and y coordinates for the apple within the game. The   *
 * user need not worry about rendering the new location so long as the renderFood() function is constantly being *
 * called within some type of game/render loop. In order to use this function to its full capacity, it should be *
 * used in conjunction with the Snake's bool-returning class function "collidesWithFood". The function also      *
 * plays a "bite" noise whenever it is called to give a more immersive addition to the game.                     *
 ****************************************************************************************************************/
void Food::generateNewFood()
{
	foodLocation = randomizeLocation();
	biteSound.play();
}

/*****************************************************************************************************************
 *										setFoodLocation()  													     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Generic private setter function to set the next food location									 *
 ****************************************************************************************************************/
void Food::setFoodLocation()
{
	food.setPosition(foodLocation);
}

/*****************************************************************************************************************
 *										getFoodLocation()														 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: sf::Vector2f of the food's current location															 *
 * Description: Generic private getter function that returns the food's current location.						 *
 ****************************************************************************************************************/
sf::Vector2f Food::getFoodLocation()
{
	return food.getPosition();
}
