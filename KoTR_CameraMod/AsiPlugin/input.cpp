#include "input.h"

using namespace std;

bool keyStates[255];

bool IsKeyPressed(int key)
{
	return HIBYTE(GetKeyState(key)) == 0xFF;
}

bool IsKeyJustPressed(int key)
{
	if (IsKeyPressed(key)){
		if (!keyStates[key]){
			keyStates[key] = true;
			return true;
		}
	}
	else {
		keyStates[key] = false;
	}
	return false;
}
