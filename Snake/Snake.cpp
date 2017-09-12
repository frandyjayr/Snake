#include "Snake.hpp"

/*****************************************************************************************************************
 *										Constructor 														     *
 *****************************************************************************************************************
 * Input: Instance of class RenderWindow and ResourceHolder                                                      *
 * Output: None                                                                                                  *
 * Description: The following constructor initializes the window variable and deathSound's soundBuffer           *
 * It also sets the texture of the sprites torso and head, sets the speed and size of the snake to the starting  *
 * values, and initializes the body to be rendered to the screen.												 *
 ****************************************************************************************************************/
Snake::Snake(sf::RenderWindow& window, ResourceHolder& resourceHolder) : window(window), 
 deathSound(resourceHolder.getSoundBuffers(SoundBuffers::ID::Death)), torso(resourceHolder.getTextures(Textures::ID::Torso)),
 head(resourceHolder.getTextures(Textures::ID::Head))
{
	resetSize();
	resetSpeed();

	initializeDeque();
}

/*****************************************************************************************************************
 *										initializeDeque()														 *
 *****************************************************************************************************************
 * Input: None																								     *
 * Output: None																									 *
 * Description:  The purpose of the function is to initialize or reinitialize (depending on when the function is *
 * called) the body of the snake. It uses the dimensions of the board to initialize a snake of length  STARTING_ *
 * LENGTH. The Snake class uses a deque for visual and speed complexity purposes as removing from the back and   *
 * adding from the front are O(1) or constant time operations, improving the performance of the game.            *
 ****************************************************************************************************************/
void Snake::initializeDeque()
{
	/* To initialize the snake, the deque must first be cleared in the case that that snake had a 
	   length greater than 0. This would be the case once the game has started. It then will keep
	   adding to the deque based on the STARTING_LENGTH global variable and set the position to the 
	   center of the window*/
	snakeBody.clear();
	for (int i = 0; i < STARTING_LENGTH; i++)
	{
		snakeBody.push_back(initializeSnakeBody(sf::Vector2f((window.getSize().x / 2) - (BODY_DIMENSIONS * i), window.getSize().y / 2), BodyType::Type::Torso));
	}
}

/*****************************************************************************************************************
 *										initializeSnakeBody() 												     *
 *****************************************************************************************************************
 * Input: sf::Vector2f of the location of the snake segment, the type of body to initialize                      *
 * Output: struct SnakeNode																						 *
 * Description: The following function is used to initialize the location and sprite type for each SnakeNode. It *
 * is mainly used as a helper function to simplify code that is constantly re-used within the program            *
 ****************************************************************************************************************/
struct SnakeNode Snake::initializeSnakeBody(sf::Vector2f location, BodyType::Type type)
{
	struct SnakeNode temp;

	switch (type)
	{
		case (BodyType::Type::Head):
		{
			head.setPosition(location);
			temp.body = head;
			temp.location = location;
		}
		case (BodyType::Type::Torso):
		{
			torso.setPosition(location);
			temp.body = torso;
			temp.location = (location);
		}
	}
	return temp;
}

/*****************************************************************************************************************
 *										collidesWithSelf()													     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: Bool indicating true if snakes self collides or false if not                                          *
 * Description: The following function tracks whether the snake collides with itself. If so, the bool will return*
 * with a bool based on the given scenario. This function is a private function, therefore, the snake class      *
 * itself keeps track of self collision and should not be managed by the user                                    *
 ****************************************************************************************************************/
bool Snake::collidesWithSelf()
{
	// Start the iterator at the second body segment and DO NOT include the head
	std::deque<SnakeNode>::iterator itr = snakeBody.begin() + 1;
	while (itr != snakeBody.end())
	{
		// Check if the head collides with any of it's body parts (not including the head)
		if (snakeBody.begin()->location == itr->location)
		{
			return true;
		}
		itr++;
	}
	return false;
}

/*****************************************************************************************************************
 *										collidesWithWall()														 *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: bool indicating if the snake collides with the wall													 *
 * Description: The following function tracks if the snake collides with the walls of the window and returns a   *
 * boolean based on the case. This is a private function, therefore, the user need not worry about managing or   *
 * calling the function. The snake class itself handles its own wall collisions. This is done by depending on the*
 * game's window size, therefore the code is adapatable to any window size.									     *
 ****************************************************************************************************************/
bool Snake::collidesWithWall()
{
	if ((snakeBody.front().location.x >= window.getSize().x) ||
		(snakeBody.front().location.x < 0) ||
		(snakeBody.front().location.y >= window.getSize().y) ||
		(snakeBody.front().location.y < 0))
	{
		return true;
	}
	return false;
}

/*****************************************************************************************************************
 *										collidesWithFood  													     *
 *****************************************************************************************************************
 * Input: Pointer the an instance of a Food class                                                                *
 * Output: Bool indicating if the snake collides with the food                                                   *
 * Description: The following function is used to check if the snake class collides with a food class on the     *
 * window. The function uses bounded box collision to check if each individual side of the snake collides with   *
 * any side of the food. If so, the sake class will internally increase the size and speed of the snake,         *
 * Therefore, the user need not worry about the details of upgrading the snake every time it collides with food  *
 ****************************************************************************************************************/
bool Snake::collidesWithFood(std::unique_ptr<Food>& food)
{
	bool isColliding = false;

	double foodTop, foodBottom, foodLeft, foodRight;
	double snakeTop, snakeBottom, snakeLeft, snakeRight;

	// Get the side locations of the food and the snake
	foodTop = food->getFoodLocation().y; 
	foodBottom = food->getFoodLocation().y + BODY_DIMENSIONS;
	foodLeft = food->getFoodLocation().x;
	foodRight = food->getFoodLocation().x + BODY_DIMENSIONS;

	snakeTop = snakeBody.front().location.y; 
	snakeBottom = snakeBody.front().location.y + BODY_DIMENSIONS;
	snakeLeft = snakeBody.front().location.x;
	snakeRight = snakeBody.front().location.x + BODY_DIMENSIONS;

	// See if the sides collide
	if (snakeTop > foodTop || snakeBottom < foodBottom || snakeLeft > foodLeft  || snakeRight < foodRight)
	{
	}
	else
	{
		food->generateNewFood();
		increaseSpeed();
		increaseSize();
		isColliding = true;
	}

	return isColliding;
}

/*****************************************************************************************************************
 *										renderSnake()														     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: The following function is used to render the entire snake body to the window. It is the          *
 * responsibility of the user to call this function in a render/game loop in order to continuosly have the snake *
 * render to the screen.																						 *
 ****************************************************************************************************************/
void Snake::renderSnake()
{
	std::deque<SnakeNode>::iterator itr = snakeBody.begin();
	while (itr != snakeBody.end())
	{
		window.draw(itr->body);
		itr++;
	}
}

/*****************************************************************************************************************
 *										moveForward()															 *
 *****************************************************************************************************************
 * Input: sf::Time delta time that repsents the time per iteration                                               *
 * Output: None																									 *
 * Description: The purpose of this function is to move the snake forward in the game. The function checks for   *
 * any self collision or wall collisions, therefore, the user need not worry about the snake colliding into      *
 * anything other than food. The movement of the snake works by removing from the back of the deque and pushing  *
 * that value to the front. Each operation is of O(1), therefore maintains a fast and efficient performance.     *
 * The snake's movement depends heavily on the speed variable that and the global SPEED_RATE                     *
 ****************************************************************************************************************/
void Snake::moveForward(sf::Time deltaTime)
{
	// Save the time and only allow the snake to move once it reaches a specific time
	sf::Clock clock;
	time += deltaTime;
	sf::Vector2f position(0.f, 0.f);

	if (collidesWithSelf() || collidesWithWall())
	{
		resetGame();
	}
	else if (time.asSeconds() > (SPEED_RATE / speed))
	{
		position = getOffset(position);

		/* Determine the next location for the head to travel.
		   Then, pop/save the end of the deque and push it
		   to the front of the deque */
		std::deque<SnakeNode>::iterator itr = snakeBody.begin();
		sf::Vector2f tempLoc = itr->location;
		tempLoc.x += (position.x);
		tempLoc.y += (position.y);

		itr = snakeBody.end() - 1;
		itr->location = tempLoc;
		itr->body = head;
		itr->body.setPosition(itr->location);
		snakeBody.front().body = torso;
		snakeBody.front().body.setPosition(snakeBody.front().location);
		snakeBody.push_front(snakeBody.back());
		snakeBody.pop_back();

		// The clock must be restarted to ensure the snake moves at the same speed
		time = clock.restart();
	}
}

/*****************************************************************************************************************
 *										changeDirection()														 *
 *****************************************************************************************************************
 * Input: direction (Down, Up, Left, or Right)																	 *
 * Output: None																								     *
 * Description: The purpose of this function is to alter the direction based on the key pressed by the user.     *
 * Changing the direction of the snake is important for its movement on the board								 *
 ****************************************************************************************************************/
void Snake::changeDirection(Direction direction)
{
	/* DO NOT allow the user to go in the opposite direction or else
	   the snake will self collide in a straight line */
	if ((directionFacing == Up && direction == Down) ||
		(directionFacing == Down && direction == Up) ||
		(directionFacing == Left && direction == Right) ||
		(directionFacing == Right && direction == Left))
	{ 
		// Do nothing
	}
	else
	{
		directionFacing = direction;
	}

}

/*****************************************************************************************************************
 *										resetSpeed()														     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Private function that resets the speed of the snake based on the STARTING_SPEED					 *
 ****************************************************************************************************************/
void Snake::resetSpeed()
{
	speed = STARTING_SPEED;
}

/*****************************************************************************************************************
 *										increaseSpeed()														     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Private function that increased the speed of the snake based on the SPEED_BOOST   				 *
 ****************************************************************************************************************/
void Snake::increaseSpeed()
{
	speed += SPEED_BOOST;
}

/*****************************************************************************************************************
 *										resetSize()														         *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Private function that resets the size of the snake based on the STARTING_Size					 *
 ****************************************************************************************************************/
void Snake::resetSize()
{
	initializeDeque();
	length = STARTING_LENGTH;
	directionFacing = STARTING_DIRECTION;
}

void Snake::resetGame()
{
	resetSize();
	resetSpeed();
	deathSound.play();
}

/*****************************************************************************************************************
 *										increaseSize()														     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Private function that increased the size of the snake							 				 *
 ****************************************************************************************************************/
void Snake::increaseSize()
{
	// Get the position for where the next head piece should be placed
	sf::Vector2f temp;
	sf::Vector2f position(0, 0);
	position.x += snakeBody.front().location.x;
	position.y += snakeBody.front().location.y;
	position = getOffset(position);

	// Change the head sprite to a torso sprite to prevent the torso front rendering as a head
	snakeBody.front().body = torso;

	// Push the new head part to the front
	snakeBody.front().body.setPosition(snakeBody.front().location);
	snakeBody.push_front(initializeSnakeBody(position, BodyType::Type::Head));

	length++;
}

/*****************************************************************************************************************
 *										getOffset()														         *
 *****************************************************************************************************************
 * Input: sf::Vector2f position																					 *
 * Output: sf::Vector2f																							 *
 * Description: The following function calculates the new position of where the next head part should be located *
 * The position is based on the current direction that the snake is facing.										 *
 ****************************************************************************************************************/
sf::Vector2f Snake::getOffset(sf::Vector2f position)
{
	if (directionFacing == Up)
	{
		position.y -= BODY_DIMENSIONS;
	}
	else if (directionFacing == Down)
	{
		position.y += BODY_DIMENSIONS;
	}
	else if (directionFacing == Right)
	{
		position.x += BODY_DIMENSIONS;
	}
	else if (directionFacing == Left)
	{
		position.x -= BODY_DIMENSIONS;
	}

	return position;
}

/*****************************************************************************************************************
 *										getLength()															     *
 *****************************************************************************************************************
 * Input: None																									 *
 * Output: None																									 *
 * Description: Generic getter function that returns the snake's length. The user may use this in conjunction    *
 * with the ScoreBoard class to output the current score of the player											 *
 ****************************************************************************************************************/
int Snake::getLength()
{
	return length;
}