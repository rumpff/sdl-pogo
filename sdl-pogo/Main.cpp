#include "GameManager.h"

int main(int argc, char* args[])
{
	GameManager game;

	game.Initalize();
	game.GameLoop();
	game.Close();

	return 0;
}