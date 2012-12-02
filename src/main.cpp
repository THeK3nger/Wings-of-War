#include "Game.h"
#include "libconfig.h++"
#include <tclap/CmdLine.h>

using namespace std;
using namespace libconfig;
/*
 * 
 */
int main(int argc, char** argv) {

	//COMMAND LINE PARSING
	//============================================================================
	string gameString;
	string enemyString;

	try {

		TCLAP::CmdLine cmd("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\nWings of War\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~", ' ', "0.1");
		TCLAP::ValueArg<std::string> gamearg("g","gamefile","Game config file to open",false,"game_option.cfg","string");
		TCLAP::ValueArg<std::string> enemyArg("e","enemyfile","Enemy config file to open",false,"red_baron.cfg","string");
		cmd.add( gamearg );
		cmd.add( enemyArg );
		cmd.parse( argc, argv );
		gameString = gamearg.getValue();
		enemyString = enemyArg.getValue();
		std::cout << "Game config file requested is: " << gameString << std::endl;
		std::cout << "Enemy config file requested is: " << enemyString << std::endl;

	}
	catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}
	//============================================================================


	//CONF file reading
	//============================================================================
	//Game conf
	Config cfg;
	char path[100];
	sprintf(path,"conf/%s",gameString.c_str());
	cfg.readFile(path);
	int search_depth_1=cfg.lookup("game.ai1_depth");
	int search_depth_2=cfg.lookup("game.ai2_depth");
	cout << "Search depth AI1: " <<search_depth_1<<endl;
	cout << "Search depth AI2: " <<search_depth_2<<endl;
	//============================================================================
	//Enemy conf
	sprintf(path,"conf/%s",enemyString.c_str());
	cfg.readFile(path);
	int distance=cfg.lookup("enemy.distance");
	int visibility=cfg.lookup("enemy.visibility");
	int health=cfg.lookup("enemy.health");
	int moves_change=cfg.lookup("enemy.moves_change");
	moves_change = max(moves_change, 0);
	moves_change = min(moves_change, 100);
	cout << "Enemy weights D[" <<distance<<"] V["<<visibility<<"] H["<<health<<"]" <<endl;
	cout << "Enemy changes his mind " << moves_change << "\% of the times" << std::endl;

	Game* gioco = new Game(600, 800, 32);

	gioco->conf.ai1_search_depth=search_depth_1;
	gioco->conf.ai2_search_depth=search_depth_2;
	gioco->conf.moves_change = moves_change;
	gioco->conf.E_distance=distance;
	gioco->conf.E_visibility=visibility;
	gioco->conf.E_health=health;

	gioco->mainGameLoop();
	delete gioco;

	return 0;
}
