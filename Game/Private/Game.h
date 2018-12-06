//
// * ENGINE-X
// * SAMPLE GAME
//
// + Game.h
// definition of MyGame, an implementation of exGameInterface
//

#include "Game/Public/GameInterface.h"
#include "Engine/Public/EngineTypes.h"
#include "GameObjectManager.h"
#include "InputManager.h"
#include "COGTurret.h"
#include "COGEnemySpawner.h"
#include <vector>
#include <string>

//-----------------------------------------------------------------
//-----------------------------------------------------------------

class MyGame : public exGameInterface
{
public:

								MyGame();
	virtual						~MyGame();

	virtual void				Initialize( exEngineInterface* pEngine );

	virtual const char*			GetWindowName() const;
	virtual void				GetClearColor( exColor& color ) const;

	virtual void				OnEvent( SDL_Event* pEvent );
	virtual void				OnEventsConsumed();

	virtual void				Run(float fDeltaT);

private:

	void						InitializeGame();
	GameObjectHandle			CreateTurret(exVector2 pTurretPosition);
	GameObjectHandle			CreateFloor();
	GameObjectHandle			CreateTurretBoundary();
	GameObjectHandle			CreateEnemySpawner();

private:

	GameObjectHandle			mTurret;
	COGTurret*					mTurretComponent;
	GameObjectHandle			mEnemySpawner;
	COGEnemySpawner*			mEnemySpawnerComponent;
	GameObjectHandle			mEnemy;
	exVector2					mPlayer1ScorePosition;
	exVector2					mPlayer2ScorePosition;

	exEngineInterface*			mEngine;

	GameObjectManager*			mGameObjectManager;
	InputManager*				mInputManager;

	bool						mGameOver;
	std::string					mGameOverText;
	exVector2					mGameOverTextPosition;

	exColor						mScoreFontColor;
	exColor						mSelectedWeaponTextColor;
	exColor						mHealthColor;

	int							mFontID;

	exVector2					mTextPosition;

};
