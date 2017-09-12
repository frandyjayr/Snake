#include "Game.hpp"
#include <stdlib.h>
#include <time.h>
#include <memory>
#include <SFML/Graphics.hpp>

int main()
{
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(1024, 896, 32), "Snake");
	std::unique_ptr<GameState> game(new Game(window));
	std::unique_ptr<GameState> menu(new Menu(window));

	menu->run();
	game->run();

	return 0;
}