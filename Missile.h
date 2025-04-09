#pragma once

constexpr int kMaxMissiles{ 15 };
constexpr float kMissileSpeed{ 10.0f };
constexpr float kMissileScale{ 0.25f };


enum MissileColor : uint8_t
{
	M_WHITE,
	M_BLUE,
	M_YELLOW,
	M_GREEN,
	M_RED,
	M_PURPLE,

	TOTAL_M_COLORS,
};

struct Missile
{
	Play::Point3D pos3D{ 0, 0, 0 };
	Play::Vector3f velocity{ 0.0f, 0.0f, 0.0f };
	Play::Vector3f gravity{ 0.0f, 0.0f, 0.0f };
	MissileColor color{ M_WHITE };
	float targetY{ 0 };
};


void AddMissileSpriteIDs();
void UpdateMissiles();
void DrawMissiles();
void DeleteMissile( Missile* m );
void AddMissileToArray( Missile* m );
void ClearMissiles();

float GetMissileWidth();
const std::vector< Missile* >& GetMissileArray();