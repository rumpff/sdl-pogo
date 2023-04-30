#include "GameManager.h"

int main(int argc, char* args[])
{
	GameManager gameManager;

	gameManager.Initialize();
	gameManager.Game();
	gameManager.Close();

	return 0;
}