#include "GameManager.h"

int main(int argc, char* args[])
{
	GameManager gameManager;

	gameManager.Initalize();
	gameManager.Game();
	gameManager.Close();

	return 0;
}