#pragma once


static int sWinner{ -1 };

constexpr int kMaxGonkFrames{ 15 };
constexpr int kMaxBuildingsLevel1{ 3 };
constexpr int kMaxBuildingsLevel2{ 6 };
constexpr int kMaxBuildingsLevel3{ 9 };
constexpr int kMaxBuildingsDefault{ 9 };


enum AllControls : uint8_t
{
    C_LEFT = 0,
    C_RIGHT,
    C_UP,
    C_DOWN,
    C_SELECT,
    C_REMOVE,
    C_FRACTION,
    C_UPGRADE,
    C_RESTART,
    C_PAUSE,

    C_MAX_CONTROLS
};

enum Winner : uint8_t
{
	W_WHITE = 0,
	W_BLUE,
	W_GREEN,
	W_PURPLE,
	W_RED,
	W_YELLOW,

	W_TOTAL,
};

struct GameState;


void ClearMemory();
void UpdateGamePlay();
void RestartGame( GameState& gState );
void MainControls( GameState& gState );
void CreateGamePlay( const GameState& gState );
void SetLevelBuildings( const GameState& gState );





