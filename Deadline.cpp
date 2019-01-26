#include "Deadline.h"

int main()
{

	std::locale::global(std::locale(""));
	std::srand(std::time(0));

	Game game;
	game.play();

	Deck deck;
	deck.loadFromFile("Data/deck.txt");

	return 0;

} // int main()