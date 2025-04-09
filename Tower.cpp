#include "pch.h"
#include "GameMath.h"
#include "Building.h"
#include "Gonk.h"
#include "Tower.h"


std::vector< int > towerIndeces;

void SetTowers()
{
	int i{ 0 };

	std::vector< Building* > vBuildings = GetBuildingArray();

	for ( Building* b : vBuildings )
	{
		if ( b->owner == WHITE )
		{
			b->type = BUILD_TOWER;
			b->owner = WHITE;
			b->gonks[ b->owner ] = Play::RandomRollRange(10, 5);

			towerIndeces.push_back( b->index );
			i++;
		}
		if ( i == kMaxTowers ) break;
	}
}

void AddTowerToArray( int index )
{
	towerIndeces.push_back( index );
}

const std::vector< int >& GetTowerArray()
{
	return towerIndeces;
}

void ClearTowers()
{
	towerIndeces.clear();
}

int IsGonkVisible( Gonk* g )
{
	for ( int index : towerIndeces )
	{
		Building* tower = GetBuilding( GetBuildingPos( index ) );
		float distance = (TransformOrtho(g->pos3D) - TransformOrtho(tower->pos3D)).Length();

		if ( distance <= kMaxVisibilityRadius && distance >= kMinVisibilityRadius )
		{
			return index;
		}
	}
	return -1;
}