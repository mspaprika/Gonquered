#include "pch.h"
#include "GameMath.h"
#include "Missile.h"


const char* missileSprites[ TOTAL_M_COLORS ] =
{
	"WHITE_Missile",
	"BLUE_Missile",
	"YELLOW_Missile",
	"GREEN_Missile",
	"RED_Missile",
	"PURPLE_Missile",
};

std::vector< Missile* > vMissiles;
int vMissileSpriteIDs[ TOTAL_M_COLORS ];


void AddMissileSpriteIDs()
{	
	vMissileSpriteIDs[ M_WHITE ] = Play::GetSpriteId(missileSprites[ M_WHITE ]);
	vMissileSpriteIDs[ M_BLUE ] = Play::GetSpriteId(missileSprites[ M_BLUE ]);
	vMissileSpriteIDs[ M_YELLOW ] = Play::GetSpriteId(missileSprites[ M_YELLOW ]);
	vMissileSpriteIDs[ M_GREEN ] = Play::GetSpriteId(missileSprites[ M_GREEN ]);
	vMissileSpriteIDs[ M_RED ] = Play::GetSpriteId(missileSprites[ M_RED ]);
	vMissileSpriteIDs[ M_PURPLE ] = Play::GetSpriteId(missileSprites[ M_PURPLE ]);
}

void UpdateMissiles()
{
	for ( Missile* m : vMissiles )
	{
		m->velocity += m->gravity;
		m->pos3D += m->velocity;

		Play::Point2D pos = TransformOrtho(m->pos3D);

		if (pos.y < 0)
		{
			DeleteMissile(m);
		}
	}
}

void DrawMissiles()
{
	for ( Missile* m : vMissiles )
	{
		float angle = atan2(m->velocity.y, m->velocity.x) + 3.14f;
		Play::DrawSpriteRotated( vMissileSpriteIDs[ m->color ], TransformOrtho( m->pos3D ), 0, angle, kMissileScale );
	}
}

void AddMissileToArray( Missile* m )
{
	vMissiles.push_back(m);
}

const std::vector< Missile* >& GetMissileArray()
{
	return vMissiles;
}

float GetMissileWidth()
{
	return Play::GetSpriteWidth( vMissileSpriteIDs[ M_WHITE ] );
}

void DeleteMissile( Missile* m )
{
	for ( int i = 0; i < vMissiles.size(); i++ )
	{
		Missile* missile = vMissiles[ i ];
		if ( m->pos3D == missile->pos3D )
		{
			Missile* m2 = vMissiles[ vMissiles.size() - 1 ];
			vMissiles[ i ] = m2;
			vMissiles.pop_back();
			delete missile;
			return;
		}
	}
}

void ClearMissiles()
{
	for (Missile* m : vMissiles)
	{
		delete m;
	}
	vMissiles.clear();
}



