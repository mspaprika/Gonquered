#include "pch.h"
#include "Corpse.h"
#include "Ghost.h"
#include "LilCreatures.h"
#include "Gonk.h"



const char* gonkSprites[ GONKS_TOTAL ][ TOTAL_GONK_TYPES ] =
{
	{ "Gonk_Straight_WHITE", "Gonk_Straight_Corpse_Top_WHITE", "Gonk_Corpse_Bottom_WHITE", "Gonk_Wonky_WHITE" },
	{ "Gonk_Straight_BLUE", "Gonk_Straight_Corpse_Top_BLUE", "Gonk_Corpse_Bottom_BLUE", "Gonk_Wonky_BLUE" },
	{ "Gonk_Straight_YELLOW", "Gonk_Straight_Corpse_Top_YELLOW", "Gonk_Corpse_Bottom_YELLOW", "Gonk_Wonky_YELLOW" },
	{ "Gonk_Straight_GREEN", "Gonk_Straight_Corpse_Top_GREEN", "Gonk_Corpse_Bottom_GREEN", "Gonk_Wonky_GREEN" },
	{ "Gonk_Straight_RED", "Gonk_Straight_Corpse_Top_RED", "Gonk_Corpse_Bottom_RED", "Gonk_Wonky_RED" },
	{ "Gonk_Straight_PURPLE", "Gonk_Straight_Corpse_Top_PURPLE", "Gonk_Corpse_Bottom_PURPLE", "Gonk_Wonky_PURPLE" },
};

int gonkSpriteIDs[ GONKS_TOTAL ][ TOTAL_GONK_TYPES ];

void UpdateLilCreatures()
{
	UpdateGonks();
	UpdateGhosts();
	UpdateCorpses();
}

void DrawLilCreatures()
{
	DrawCorpses();
	DrawGonks();
	DrawGhosts();
}

void ClearLilCreatures()
{
	ClearGonks();
	ClearCorpses();
	ClearGhosts();
}

void AddGonkSpriteIDs()
{
	for ( int i = 0; i < GONKS_TOTAL; i++ )
	{
		for ( int j = 0; j < TOTAL_GONK_TYPES; j++ )
		{
			gonkSpriteIDs[ i ][ j ] = Play::GetSpriteId( gonkSprites[ i ][ j ] );
		}
	}
}

int GetGonkSpriteID( int color, int type )
{
	return gonkSpriteIDs[ color ][ type ];
}



