#pragma once

constexpr int kMaxBuildings{ 9 };
constexpr int kGridSize{ 3 };
constexpr int kMaxPlayers{ 2 };


enum BuildType : uint8_t
{
	BUILD_LEVEL1 = 0,
	BUILD_LEVEL2,
	BUILD_LEVEL3,
	BUILD_TOWER,

	TOTAL_TYPES
};

enum Color : uint8_t
{
	WHITE = 0,
	BLUE,
	YELLOW,
	GREEN,
	RED,
	PURPLE,

	TOTAL_COLORS,
};

enum Direction : uint8_t
{
	N_LEFT = 0,
	N_RIGHT,
	N_UP,
	N_DOWN,

	MAXL_DIRECTIONS,
};

struct Building
{
	bool fight{ false };
	Play::Point3D pos3D{ 0, 0, 0 };
	BuildType type{ BUILD_LEVEL1 };

	int index{ 0 };
	int owner{ WHITE };
	float lastSpawnTime{ 0.0f };
	float lastFireTime{ 0.0f };
	int gonks[ TOTAL_COLORS ];
	int prevGonks[ TOTAL_COLORS ];
};


void AddBuildingSpriteIDs();
void CreateBuildings();
void DrawBuildings();
void UpdateBuildings();
void SetBuildingsIndeces( int count );
void SortBuildings();
void ClearBuildings();
void ResetBuildingIndeces();


Building* GetBuilding( Play::Point3D pos );
const std::vector< Building* >& GetBuildingArray();
const Play::Point3D& GetBuildingPos( int index );
float GetBuildingHeight( Building* b );
int GetBuildingArrayIndex( int index );
std::vector< int >& GetLevelIndeces();


/////////////////////////////////////
int GetGonkSpriteID( int color, int type = 0 );
float GonkSpawnTime( int type );