/*===================================================================#
| 'Main' source file last updated on 31 May 2021                     |
#===================================================================*/

#include "Game.h"
#include "MenuState.h"

//TODO - Add 'assert' where required
//TODO - Consider RAII for class design
//TODO - Load settings from a config file
//TODO - Make sure all code is const correct

int main(int argc, char* args[])
{
	Game game(new MenuState);

	if (game.Initialize("<insert game name here>", 1280, 720))
	{
		if (!game.Run())
		{
			game.Shutdown();
			return 0;
		}
	}
}