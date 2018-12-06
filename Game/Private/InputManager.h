#pragma once
#include "InputState.h"
#include "Engine\Public\SDL.h"
#include "Singleton.h"


const int WASD = 0;
const int ARROWS = 1;

class InputManager : public Singleton<InputManager>
{
private:
	InputState* inputState;
	int controlScheme;
public:
	// Constructor
	InputManager();
	//Destructor
	~InputManager();
	
	void Update();
	bool IsButtonDown(Uint8 nScancode) const;
	bool IsMouseButtonDown(Uint8 nScancode) const;
	InputState* GetInputState() const;

};

InputManager* Singleton<InputManager>::existingInstance = nullptr;