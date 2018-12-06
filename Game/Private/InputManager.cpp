#include "InputManager.h"

InputManager::InputManager()
{
	inputState = new InputState();
}

InputManager::~InputManager()
{
	delete inputState;
	inputState = nullptr;
}

void InputManager::Update()
{
	// Storing the previous state before updating the current state
	inputState->mPreviousState = inputState->mState;
	// Resetting Current State
	inputState->mState = 0;

	SDL_GetMouseState(&(inputState->mMouseState.x), &(inputState->mMouseState.y));

	if (IsMouseButtonDown(SDL_BUTTON_LEFT))
	{
		inputState->mState |= INPUT_LMB;
	}

	if (IsButtonDown(SDL_SCANCODE_L))
	{
		inputState->mState |= INPUT_DEBUG;
	}

	if (IsButtonDown(SDL_SCANCODE_1))
	{
		inputState->mState |= INPUT_1;
	}

	if (IsButtonDown(SDL_SCANCODE_2))
	{
		inputState->mState |= INPUT_2;
	}

	if (IsButtonDown(SDL_SCANCODE_3))
	{
		inputState->mState |= INPUT_3;
	}
}

bool InputManager::IsButtonDown(Uint8 nScancode) const
{
	int keys = 0;
	const Uint8 *pState = SDL_GetKeyboardState( &keys );
	return pState[nScancode];
}

bool InputManager::IsMouseButtonDown(Uint8 nScanCode)const
{
	const Uint32 State = SDL_GetMouseState(&(inputState->mMouseState.x), &(inputState->mMouseState.y));
	return State & SDL_BUTTON(nScanCode);
}

InputState* InputManager::GetInputState() const
{
	return inputState;
}