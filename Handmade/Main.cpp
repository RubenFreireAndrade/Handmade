/*===================================================================#
| 'Main' source file last updated on 28 May 2021                     |
#===================================================================*/

#include "Game.h"
#include "MenuState.h"

//TODO - Add 'assert' where required
//TODO - Use 'auto' and range-based for loops where possible
//TODO - Consider RAII for class design
//TODO - Load settings from a config file

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