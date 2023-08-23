#define OBJECT_CREATION_FAILED -1
#include <memory>

#include "Game/Game.h"

int main()
{
	srand(time(NULL));

	std::shared_ptr<Game> game = std::make_shared<Game>();
	if (!game)
		return OBJECT_CREATION_FAILED;

	game->run();

	return 0;
}