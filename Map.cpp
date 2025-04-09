#include "pch.h"
#include "GameMath.h"
#include "Order.h"
#include "Building.h"
#include "Tower.h"
#include "Missile.h"
#include "Player.h"
#include "LilCreatures.h"
#include "GameState.h"
#include "XInputControls.h"
#include "Map.h"


void CreateGamePlay( const GameState& gState )
{
	ResetBuildingIndeces();
	AddGonkSpriteIDs();
	AddBuildingSpriteIDs();
	AddMissileSpriteIDs();
	AddSelectionSpritesIDs();
	SetLevelBuildings( gState );
	CreateBuildings();
	CreatePlayers();
}

void UpdateGamePlay()
{
	UpdatePlayers();
	UpdateLilCreatures();
	UpdateBuildings();
	UpdateMissiles();
}

void MainControls( GameState& gState )
{
	if (Play::KeyPressed( Play::KEY_SPACE ) || XInputReceived( C_PAUSE ) )
	{
		gState.state = ( gState.state == STATE_PLAY ) ? STATE_PAUSE : STATE_PLAY;
	}
	if (Play::KeyPressed( Play::KEY_DELETE ) || XInputReceived( C_RESTART ))
	{
		RestartGame( gState );
	}
}

void SetLevelBuildings( const GameState& gState )
{
	static int buildingCount{ 0 };

	switch ( gState.level )
	{
		case 1:
			buildingCount = kMaxBuildingsLevel1;
			break;

		case 2:
			buildingCount = kMaxBuildingsLevel2;
			break;

		case 3:
			buildingCount = kMaxBuildingsLevel3;
			break;

		default:
			buildingCount = kMaxBuildingsDefault;
	}
	SetBuildingsIndeces( buildingCount );
}

void RestartGame( GameState& gState )
{
	ClearMemory();
	sWinner = -1;

	if (gState.levelPassed)
	{
		gState.level++;
		gState.levelPassed = false;
	}
	else gState.level = 1;
	
	CreateGamePlay( gState );
	gState.levelInfoTimer = 0.0f;
	gState.state = STATE_PLAY;
}

void ClearMemory()
{
	ClearLilCreatures();
	ClearBuildings();
	ClearTowers();
	ClearPlayers();
	ClearMissiles();
	ClearOrders();
}