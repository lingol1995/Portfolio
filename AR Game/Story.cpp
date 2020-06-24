#include "Story.h"

Story::Story()
{
}

void Story::storylines(int level)		//Lines fed to application, Apologies for awful story
{	
	if (level == 1)						//If in Level 1, Assign these lines
	{
		lines[0] = "Welcome. Press X to cycle through...";		
		lines[1] = "There once was a brave warrior...";
		lines[2] = "That's you!...";
		lines[3] = "They were on a journey...";
		lines[4] = "and came across something strange...";
		lines[5] = "a weird flying thing...";
		lines[6] = "It's movements were strange...";
		lines[7] = "And almost...";
		lines[8] = "Oh no!";
		lines[9] = "It's escaping";
	}

	if (level == 2)						//If in Level 2, Assign these lines
	{
		lines[0] = "Hello again";
		lines[1] = "Sorry about that...";
		lines[2] = "Phew!!...";
		lines[3] = "That was close...";
		lines[4] = "Think you got it...";
		lines[5] = "Did you say something?...";
		lines[6] = "Oh no...";
		lines[7] = "I...";
		lines[8] = "I think there's another!";
		lines[9] = "Be careful!";
	}
}