#ifndef INPUT_H
#define INPUT_H
// Input class


#include <Windows.h>

class Input
{
	typedef struct Mouse
	{
		int x,y;
		bool left, right;
	};

public:
	void SetKeyDown(WPARAM);
	void SetKeyUp(WPARAM);

	bool isKeyDown(int);
	void setMouseX(int);
	void setMouseY(int);
	
	int getMouseX();
	int getMouseY();
	// set mouse botton down (left, right, middle)
	// set mouse botton up

private:
	bool keys[256];
	Mouse mouse;

};

#endif