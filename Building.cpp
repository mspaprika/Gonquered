#include "pch.h"
#include "GameMath.h"
#include "Missile.h"
#include "Building.h"


const char* buildings[ TOTAL_COLORS ][ TOTAL_TYPES ] =
{
	{ "HouseT1_building_WHITE", "HouseT2_building_WHITE", "HouseT3_building_WHITE", "Tower_building_WHITE" },
	{ "HouseT1_building_BLUE", "HouseT2_building_BLUE", "HouseT3_building_BLUE", "Tower_building_BLUE" },
	{ "HouseT1_building_YELLOW", "HouseT2_building_YELLOW", "HouseT3_building_YELLOW", "Tower_building_YELLOW" },
	{ "HouseT1_building_GREEN", "HouseT2_building_GREEN", "HouseT3_building_GREEN", "Tower_building_GREEN" },
	{ "HouseT1_building_RED", "HouseT2_building_RED", "HouseT3_building_RED", "Tower_building_RED" },
	{ "HouseT1_building_PURPLE", "HouseT2_building_PURPLE", "HouseT3_building_PURPLE", "Tower_building_PURPLE" }
};

const char* bubbleSprites[ TOTAL_COLORS ] =
{
	 "SpeechBubble_WHITE",  "SpeechBubble_BLUE",  "SpeechBubble_YELLOW",  "SpeechBubble_GREEN",  "SpeechBubble_RED",  "SpeechBubble_PURPLE"
};

Play::Point3D buildingPositions[ kMaxBuildings ] =
{
	{ 500, -120, 0 }, 
	{ DISPLAY_WIDTH / 2 + 200, -580, 0 },  
	{ DISPLAY_WIDTH - 100, -1035, 0 },

	{ 500, DISPLAY_HEIGHT / 2 - 170, 0 }, 
	{ DISPLAY_WIDTH / 2 + 200, DISPLAY_HEIGHT / 2 - 630, 0 },  
	{ DISPLAY_WIDTH - 100, DISPLAY_HEIGHT / 2 - 1085, 0 },

	{ 500, DISPLAY_HEIGHT - 220, 0 }, 
	{ DISPLAY_WIDTH / 2 + 200, DISPLAY_HEIGHT - 680, 0 },  
	{ DISPLAY_WIDTH - 100, DISPLAY_HEIGHT - 1135, 0 },
};

int bubbleSpritesIDs[ TOTAL_COLORS ];
int buildingSpritesIDs[ TOTAL_COLORS ][ TOTAL_TYPES ];

std::vector< int > vAllIndeces{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
std::vector< int > vLevelIndeces;
std::vector< Building* > vBuildings;


void AddBuildingSpriteIDs()
{
	for ( int i = 0; i < TOTAL_COLORS; i++ )
	{
		for ( int j = 0; j < TOTAL_TYPES; j++ )
		{
			buildingSpritesIDs[ i ][ j ] = Play::GetSpriteId( buildings[ i ][ j ] );
		}
		bubbleSpritesIDs[ i ] = Play::GetSpriteId( bubbleSprites[ i ] );
	}
}

void CreateBuildings()
{
	int i{ 0 };
	for ( int i = 0; i < vLevelIndeces.size(); i++ )
	{		
		int index = vLevelIndeces[ i ];
		Play::Point3D pos = buildingPositions[ index ];
		Building* b = new Building();
		b->pos3D = pos;
		b->gonks[ WHITE ] = Play::RandomRollRange(0, 1);
		b->index = vLevelIndeces[ i ];

		vBuildings.push_back(b);
	}
	SortBuildings();
}

void SetBuildingsIndeces( int count )
{
	if ( count == 9 )
	{	
		vLevelIndeces.insert( vLevelIndeces.begin(), vAllIndeces.begin(), vAllIndeces.end() );
		return;
	}

	for ( int i = 0; i < count; i++ )
	{
		int index = Play::RandomRollRange(0, vAllIndeces.size() - 1);
		vLevelIndeces.push_back( vAllIndeces[ index ] );
		vAllIndeces.erase( vAllIndeces.begin() + index );
	}
}

void DrawBuildings()
{
	for ( Building* b : vBuildings )
	{
		Play::Vector2D newPos = TransformOrtho( b->pos3D );
		Play::DrawSpriteRotated(buildingSpritesIDs[ b->owner ][ b->type ], newPos, 0, 0.0f, 2.0f);
		Play::DrawSpriteRotated(bubbleSpritesIDs[ b->owner ], {newPos.x - 100, newPos.y + 100}, 0, 0.0f, 0.75f);
		Play::DrawSprite(GetGonkSpriteID( b->owner ), { newPos.x - 140, newPos.y + 130 }, 0);
		Play::DrawDebugText({ newPos.x - 70, newPos.y + 130 }, std::to_string( b->gonks[ b->owner ]).c_str(), Play::cBlack );
	}
}

void UpdateBuildings()
{
	for ( Building* b : vBuildings )
	{
		b->fight = ( b->gonks[ b->owner ] < b->prevGonks[ b->owner ] ) ? true : false;
		b->prevGonks[ b->owner ] = b->gonks[ b->owner ];
		b->lastSpawnTime += DELTA_TIME;
		b->lastFireTime += DELTA_TIME;

		float spawnTimeInterval = GonkSpawnTime( b->type );
		if ( b->gonks[ b->owner ] > 100 || b->owner == WHITE )
			spawnTimeInterval = 2.0f;

		if ( b->lastSpawnTime > spawnTimeInterval )
		{		
			b->lastSpawnTime = 0.0f;
			b->gonks[ b->owner ]++;		
		}

		if (b->gonks[ b->owner ] < 0) 
			b->gonks[ b->owner ] = 0;	
	}
}

void ClearBuildings()
{
	for ( Building* b : vBuildings )
	{
		delete b;
	}
	vBuildings.clear();
	vLevelIndeces.clear();
}

void ResetBuildingIndeces()
{
	vAllIndeces = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
}

void SortBuildings()
{
	std::sort( vBuildings.begin(), vBuildings.end(), [](Building* a, Building* b) { return a->index < b->index; } );
}


Building* GetBuilding( Play::Point3D pos )
{
	for ( Building* b : vBuildings )
	{
		if ( b->pos3D == pos )
		{
			return b;
		}
	}
	return nullptr;
}

const std::vector< Building* >& GetBuildingArray()
{
	return vBuildings;
}

const Play::Point3D& GetBuildingPos( int index )
{
	return buildingPositions[ index ];
}

float GetBuildingHeight( Building* b )
{
	return Play::GetSpriteHeight( buildingSpritesIDs[ b->owner ][ b->type ] );
}

std::vector< int >& GetLevelIndeces()
{
	return vLevelIndeces;
}

int GetBuildingArrayIndex( int index )
{
	for ( int i = 0; i < vBuildings.size(); i++ )
	{
		if ( vBuildings[ i ]->index == index )
		{
			return i;
		}
	}
	return -1;
}










