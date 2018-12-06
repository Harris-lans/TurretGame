#include "InputState.h"
#include <iostream>

InputState::InputState()
{
	mState = 0;
	mPreviousState = 0;
}

InputState::~InputState()
{
	// Nothing to destruct for now
}

bool InputState::PressedFireButton() const
{
	// Checks if the Mouse Button has just been pressed
	return ((mPreviousState & INPUT_LMB) == 0 && (mState & INPUT_LMB) != 0);
}

bool InputState::HoldingFireButton() const
{
	// Checks if the mouse button is being held
	return ((mPreviousState & INPUT_LMB) != 0 && (mState & INPUT_LMB) != 0);
}

bool InputState::ReleasedFireButton() const
{
	// Check if the mouse button has just been released
	return ((mPreviousState & INPUT_LMB) != 0 && (mState & INPUT_LMB) == 0);
}

bool InputState::PressedDebug() const
{
	return ((mState & INPUT_DEBUG) != 0 && (mPreviousState & INPUT_DEBUG) == 0);
}

bool InputState::PressedBulletStormButton() const
{
	return ((mState & INPUT_1) != 0 && (mPreviousState & INPUT_1) == 0);
}

bool InputState::PressedTargettedMissilesButton() const
{
	return ((mState & INPUT_2) != 0 && (mPreviousState & INPUT_2) == 0);
}

bool InputState::PressedPulseDisruptionButton() const
{
	return ((mState & INPUT_3) != 0 && (mPreviousState & INPUT_3) == 0);
}

exVector2& InputState::GetMousePosition()
{
	// Sending the mouse position as a exVector2-float
	exVector2 mousePosition = { float(mMouseState.x), float(mMouseState.y) };
	return mousePosition;
}