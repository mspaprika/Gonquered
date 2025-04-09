#define PLAY_IMPLEMENTATION
#include "Play.h"
#include "GameMath.h"
#include "GameState.h"
#include "Winner.h"
#include "Map.h"


constexpr int DISPLAY_SCALE{ 1 };
const char* SPR_BACKGROUND{ "Data\\Backgrounds\\PlayField.png" };

GameState gState;

// The entry point for a PlayBuffer program
void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground( SPR_BACKGROUND );
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	sWinner = GetWinner();

	switch ( gState.state )
	{
		case STATE_LOBBY:
			UpdateLobby( gState );
			DrawLobby();
			break;

		case STATE_PLAY:
			gState.levelInfoTimer += elapsedTime;
			UpdatePlayState( gState );
			DrawPlayState( gState );
			UpdateWinner( gState, sWinner );
			break;

		case STATE_WIN:
			UpdateWinState( gState );
			DrawWinState();
			break;

		case STATE_PAUSE:
			MainControls( gState );
			DrawPauseState();
			break;
	}

	return Play::KeyDown( KEY_ESCAPE );
}


// Gets called once when the player quits the game 
int MainGameExit( void )
{
	ClearMemory();
	Play::DestroyManager();
	return PLAY_OK;
}












