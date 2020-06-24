#include "GameStates.h"

GameStates::GameStates()
{
}

void GameStates::initState()
{
	curr_state = start;					//Initial state is the start
	curr_level = one;					//Initial level is level one (0)
	changeLevel = false;				//Level can't change
}

void GameStates::levelActivate(Enemy& enemy, Controller& controller_)
{
	
	switch (curr_level)						//Switching current level
	{
	case one:								//If level one	
		enemy.powerLevel = 1;				//Power multiplier is 1
		if (enemy.health == 0.0f)			//If enemy dies
		{
			changeLevel = true;				//Level can change
			controller_.storydone = false;	//Story is not finished anymore (start array again)
			curr_level = two;				//Level 2 activated
		}
		break;

	case two:								//If level 2
		if (changeLevel == true)			//If level has just changed
		{
			enemy.Reset();					//Reset enemy (health and power reset)
			changeLevel = false;			//No longer change level
		}
		enemy.powerLevel = 1.5;				//Power multiplier 1.5
		if (enemy.health == 0.0f)			//If enemy dies
		{
			changeLevel = true;				//Can change level
			controller_.storydone = false;	//Story is not finished (enter story mode)
			curr_level = three;				//Level 3 activated
			
		}
		break;

	case three:								//If level 3
		if (changeLevel == true)			//If level just changed
		{
			enemy.Reset();					//Reset enemy
			changeLevel = false;			//Don't change level
		}
		enemy.powerLevel = 3.5;				//Power multiplier is 3.5
		if (enemy.health == 0)				//If enemy dies
		{
			curr_state = congrats;			//Game Complete
		}
		break;
	}
}

void GameStates::stateActivate(Controller& controller_, Markers& marker, GameObject& gameObject, Enemy& enemy)	//Determines game states
{
	switch (curr_state)							//Switch the current state
	{
	case start:									//Starting state (Start menu)
		gameObject.Reset();						//Reset object (player)
		enemy.Reset();							//Reset enemy
		curr_level = one;						//Reset level back to 1
		if (controller_.Start())				//If start button pressed
			curr_state = pause;					//Switch to pause state (Pause menu)
		break;

	case pause:									//In Pause state
		if (marker.marker1Found() && marker.marker2Found() && marker.marker3Found() && marker.marker4Found())		//If markers 1, 2 and 3 are found
		{
			curr_state = messages;				//Messages state (Story mode)
		}
		break;

	case messages:								//Messages state
		if (controller_.storydone == true)		//If story is finished
		{
			curr_state = battle;				//Battle mode activated
		}

		if (marker.marker1Found() == false || marker.marker2Found() == false || marker.marker3Found() == false )	//If marker or marker 2 aren't found
		{
			curr_state = pause;					//Pause activated
		}
		break;
	case battle:								//Battle Mode
		if (controller_.storydone == false)		//If story isn't finished
		{
			curr_state = messages;				//Go back to story mode
		}

		if (marker.marker1Found() == false || marker.marker2Found() == false || marker.marker3Found() == false)		//If markers aren't found, pause game
		{
			curr_state = pause;					//Pause state
		}

		if (gameObject.health <= 1)				//If player dies
		{
			curr_state = end;					//End state (Game Over)
		}
		break;
	case end:									//If Game Over
		if (controller_.Start())				//If start button pressed			
		curr_state = start;						//Return to start state
		controller_.Quit();						//If select button pressed, quit
		break;

	case congrats:								//If game complete
		if (controller_.Start())				//If start button pressed		
		curr_state = start;						//Return to start state
		controller_.Quit();						//If select button pressed, quit
		break;
	}
}
