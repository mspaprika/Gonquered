#pragma once


enum GameStates : uint8_t
{
	STATE_LOBBY = 0,
	STATE_PLAY,
	STATE_WIN,
	STATE_PAUSE,

	TOTAL_STATES,
};

struct GameState
{
	GameStates state{ STATE_LOBBY };
	int level{ 1 };
	bool levelPassed{ false };
	float levelInfoTimer{ 0.0f };
};

void DrawLobby();
void UpdateLobby( GameState& gState );
void DrawPlayState( const GameState& gState );
void DrawPauseState();
void UpdateWinState( GameState& gState );
void UpdatePlayState( GameState& gState );
void DrawWinState();