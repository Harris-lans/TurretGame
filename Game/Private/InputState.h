#pragma once
#include "Engine\Public\EngineInterface.h"
#include "Engine\Public\EngineInterface.h"

enum States
{
	INPUT_LMB = 1 << 0,
	INPUT_DEBUG = 1 << 1,
	INPUT_1 = 1 << 2,
	INPUT_2 = 1 << 3,
	INPUT_3 = 1 << 4,
};

enum class Devices
{
	MOUSE = 0,
	KEYBOARD
};

class InputState
{
private:
	int mState;
	int mPreviousState;
	exIntegerVector2 mMouseState;

public:
	friend class InputManager;

	InputState();
	~InputState();

	bool PressedFireButton() const;
	bool ReleasedFireButton() const;
	bool HoldingFireButton() const;

	bool PressedBulletStormButton() const;
	bool PressedTargettedMissilesButton() const;
	bool PressedPulseDisruptionButton() const;

	bool PressedDebug() const;

	exVector2& GetMousePosition();
};