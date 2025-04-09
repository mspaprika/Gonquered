#pragma once

constexpr int kPriceBuildLevel2{ 10 };
constexpr int kPriceBuildLevel3{ 15 };
constexpr int kPriceBuildTower{ 20 };

constexpr int kBuildingCountPlayerLevel1{ 1 };
constexpr int kBuildingCountPlayerLevel2{ 2 };
constexpr int kBuildingCountDefault{ 3 };


struct Building;

enum Controls : uint8_t
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN,
	SELECT,
	REMOVE,
	FRACTION,
	UPGRADE,

	MAX_CONTROLS
};

enum SelectMode : uint8_t
{
	SELECT_SOURCE = 0,
	SELECT_TARGET,
	SELECT_GREEN,
	ARROW,

	MAX_SELECTIONS,
};

enum FractionWarriors : uint8_t
{
	QUARTER = 0,
	HALF,
	THREE_QUARTERS,
	FULL,

	TOTAL_FRACTIONS,
};

enum PlayerColors : uint8_t
{
	P_WHITE = 0,
	P_BLUE,
	P_GREEN,
	P_PURPLE,
	P_RED,
	P_YELLOW,

	P_TOTAL_COLORS,
};


struct Player
{
	Play::KeyboardButton controls[ MAX_CONTROLS ]{ Play::KEY_SPACE };
	Building* src{ nullptr };
	Building* selected{ nullptr };
	int id{ 0 };
	int morale{ 50 };
	int frame{ 0 };
	SelectMode mode{ SELECT_SOURCE };
	PlayerColors color{ P_WHITE };
	FractionWarriors fraction{ FULL };
};

void CreatePlayers();
void AddSelectionSpritesIDs();
void CreateSinglePlayer( const std::vector< Play::KeyboardButton >& buttons, int c, int ID );
void SetPlayerBuildings( int player );
void UpdatePlayers();
void DrawPlayers();
void DrawPlayerDebug();
void UpgradeBuilding( Player* p );
void ClearPlayers();

int CheckWinner();
int& GetBuildingsForPlayerCount();
void SetBuildingsForPlayer( int& buildingCount );
int CalculateFractionGonks( int gonks, int fraction );