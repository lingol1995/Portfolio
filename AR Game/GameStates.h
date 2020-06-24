#ifndef _GAMESTATES_H
#define _GAMESTATES_H

#include "samples\ar_app\build\vs2015\Controller.h"
#include "samples\ar_app\build\vs2015\Player.h"
#include "samples\ar_app\build\vs2015\Markers.h"
#include "samples\ar_app\build\vs2015\fbxModels.h"
#include "samples\ar_app\build\vs2015\Enemy.h"

enum state { start, pause, messages, battle, end, congrats };		//Game States
enum levels { one, two, three };									//Game Levels

class GameStates
{
public:
	GameStates();

	state curr_state;												//Current game state
	levels curr_level;												//Current game level
	void initState();												//Initialise states
	void stateActivate(Controller& controller_, Markers& marker, GameObject& game_object, Enemy& enemy);	//Decides which state the game is in by looking at player and enemy, marker tracking and button presses
	void levelActivate(Enemy& enemy, Controller& controller_);		//Decides level of game based on enemy health
	bool changeLevel;												//Level can/can't change

	Player player;													//Player object
	fbxModels fbx_model;											//FBX Model

};
#endif

