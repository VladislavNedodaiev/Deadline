#include "Deadline.h"

int main()
{

	std::locale::global(std::locale(""));
	std::srand(std::time(0));

	Game game;
	game.play();

	return 0;

} // int main()