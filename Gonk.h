#pragma once

constexpr int kMaxFrames{ 15 };
constexpr float kGonkSpeed{ 2.0f };

constexpr int kGonkProgressPartOne{ 30 };
constexpr int kGonkProgressPartTwo{ 75 };

constexpr float kOffsetMultiplyPartOne{ 4.5f };
constexpr float kOffsetMultiplyPartTwo{ 5.5f };


struct Order;

enum Gonks : uint8_t
{
	GONK_WHITE = 0,
	GONK_BLUE,
	GONK_GREEN,
	GONK_PURPLE,
	GONK_RED,
	GONK_YELLOW,

	GONKS_TOTAL,
};

enum GonkDir : uint8_t
{
	DIR_DOWN = 0,
	DIR_LEFT_DOWN,
	DIR_LEFT,
	DIR_LEFT_UP,
	DIR_UP,
	DIR_RIGHT_UP,
	DIR_RIGHT,
	DIR_RIGHT_DOWN,

	TOTAL_DIRECTIONS,
};


struct Gonk
{
	Play::Point3D pos3D{ 200, 200, 0 };
	Play::Vector3f velocity{ 0.0f, 0.0f, 0.0f };
	Order* order{ nullptr };
	float spawnTimer{ 0.2f };
	float progress{ 0.0f };
	float frame{ 0.0f };
	float offset{ 0.0f };
	bool leftBuilding{ false };
	Gonks spriteID{ 0 };
	GonkDir spriteDir{ DIR_DOWN };
};



void DrawGonks();
void UpdateGonks();

void FightGonks();
void DeleteGonk( Gonk* g );
void DrawGonk( Gonk* g );
void GonkFight( Gonk* g );

void UpdateGonkPosition( Gonk* g );
void GonkTowerVisibility( Gonk* g );
void MissileCollisions( Gonk* g );
void AddGonkToArray( Gonk* gonk );
void ClearGonks();

void SortGonks();

const std::vector< Gonk* >& GetGonkArray();
bool IsTargetReached( Gonk* g );
int GetDirectionGonk( const Play::Point3f& posSrc, const Play::Point3f& posTrg );

void GonkDirectionBugs( Gonk* g, Play::Vector3f& vPerp );


