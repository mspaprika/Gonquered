
//#include <Xinput.h>
#include "pch.h"
#include "GameMath.h"
#include "Order.h"
#include "Building.h"
#include "Missile.h"
#include "Player.h"
#include "LilCreatures.h"
#include "Map.h"
#include "Winner.h"
#include "GameState.h"
#include "XInputControls.h"



const char* gonkLogoSprite{ "GonkLOGO" };


void DrawLobby()
{
	Play::ClearDrawingBuffer( Play::cWhite );
	Play::DrawBackground();
	Play::DrawFontText( "64", "G  o  n  k  q  u  e  r  e  d", { DISPLAY_WIDTH / 2 - 200, DISPLAY_HEIGHT - 300 }, Play::LEFT );
	Play::DrawDebugText( { DISPLAY_WIDTH / 2 + 100, DISPLAY_HEIGHT / 2 + 150 }, "Press Enter To Start" );
	Play::DrawDebugText( { DISPLAY_WIDTH / 2 + 100, DISPLAY_HEIGHT / 2 + 125 }, "Space To Pause...Delete To Restart" );
	Play::DrawSprite( gonkLogoSprite, { 500, DISPLAY_HEIGHT / 2 + 100 }, 0 );
	
	Play::PresentDrawingBuffer();
}

void UpdateLobby( GameState& gState )
{
	if (Play::KeyPressed( Play::KEY_ENTER ) || XInputReceived( C_SELECT ) )
	{
		CreateGamePlay( gState );
		gState.state = STATE_PLAY;
	}
}

void DrawPlayState( const GameState& gState )
{
	Play::ClearDrawingBuffer( Play::cWhite );
	Play::DrawBackground();
	DrawLilCreatures();
	DrawBuildings();
	DrawPlayers();
	DrawMissiles();

	if ( gState.levelInfoTimer < 3.0f )
	{
		Play::DrawFontText( "64", "Level " + std::to_string(gState.level), { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 } );
	}
	Play::PresentDrawingBuffer();
}

void DrawPauseState()
{
	static float gonkFrame = 0.0f;

	Play::ClearDrawingBuffer( Play::cWhite );
	Play::DrawBackground();

	Play::DrawSprite( gonkLogoSprite, { 500, DISPLAY_HEIGHT / 2 + 100 }, 0 );
	Play::DrawFontText( "64", "G  o  n  k  q  u  e  r  e  d", { DISPLAY_WIDTH / 2 - 200, DISPLAY_HEIGHT - 300 }, Play::LEFT );
	Play::DrawSpriteRotated( GetGonkSpriteID( W_RED ), { DISPLAY_WIDTH / 2 + 250, DISPLAY_HEIGHT / 2 - 50 }, static_cast<int>(gonkFrame) % kMaxGonkFrames, 0.0f, 3.0f );
	Play::DrawFontText( "64", "Paused...", { DISPLAY_WIDTH / 2 - 50, DISPLAY_HEIGHT / 2 - 100 } );
	Play::PresentDrawingBuffer();

	gonkFrame += 0.3f;
}

void DrawWinState()
{
	Play::ClearDrawingBuffer( Play::cWhite );
	Play::DrawBackground();
	DrawLilCreatures();
	DrawBuildings();

	static int color = GetWinner();
	static std::string winner = GetWinnerString( color );

	Play::DrawRect( { DISPLAY_WIDTH / 2 - 300, DISPLAY_HEIGHT / 2 - 180 }, { DISPLAY_WIDTH / 2 + 300, DISPLAY_HEIGHT / 2 + 150 }, Play::Colour{ 70, 70, 70 }, true );
	Play::DrawSpriteRotated( GetGonkSpriteID( color ), { DISPLAY_WIDTH / 2 - 200, DISPLAY_HEIGHT / 2 }, 0, 0.0f, 6.0f );
	Play::DrawFontText( "64", winner, { DISPLAY_WIDTH / 2 - 50, DISPLAY_HEIGHT / 2 } );
	Play::DrawDebugText( { DISPLAY_WIDTH / 2 + 100, DISPLAY_HEIGHT / 2 - 100 }, "Press Delete To Continue" );
	Play::PresentDrawingBuffer();
}

void UpdatePlayState( GameState& gState )
{
	UpdateBuildings();
	UpdatePlayers();
	UpdateLilCreatures();
	UpdateMissiles();
	MainControls( gState );
}

void UpdateWinState( GameState& gState )
{
	UpdateLilCreatures();

	if (Play::KeyPressed( Play::KEY_DELETE ) || XInputReceived( C_RESTART ))
	{
		RestartGame( gState );
	}
}
