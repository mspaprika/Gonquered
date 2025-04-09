#pragma once

struct Corpse
{
	Play::Point3D pos3D{ 200, 200, 0 };
	float rotationTop{ 0.0f };
	float rotationBottom{ 0.0f };
	int spriteColor{ 0 };
	float frame{ 0.0f };
	float spread{ 1.0f };
};

enum GonkType : uint8_t
{
	STRAIGHT = 0,
	CORPSE_TOP,
	CORPSE_BOTTOM,
	WONKY,

	TOTAL_GONK_TYPES,
};


void UpdateCorpses();
void AddCorpseToArray( Corpse* c );
void DrawCorpses();
void ClearCorpses();
int GetGonkSpriteID( int color, int type );
