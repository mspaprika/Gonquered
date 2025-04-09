#include "pch.h"
#include "GameMath.h"
#include "Missile.h"
#include "Building.h"
#include "Tower.h"
#include "Order.h"
#include "Corpse.h"
#include "Ghost.h"
#include "Gonk.h"


Play::Vector2f directionsNormalized[ TOTAL_DIRECTIONS ] =
{
	{ 0.0f, -1.0f }, { -0.7f, -0.7f }, { -1.0f, 0.0f }, { -0.7f, 0.7f }, 
	{ 0.0f, 1.0f }, { 0.7f, 0.7f }, { 1.0f, 0.0f }, { 0.7f, -0.7f },
};

std::vector< Gonk* > vGonks;

float GonkSpawnTime( int type )
{
	if ( type == BUILD_LEVEL1 ) return 2.0f;
	else if ( type == BUILD_LEVEL2 ) return 1.5f;
	else if ( type == BUILD_LEVEL3 ) return 1.3f;
	else if ( type == BUILD_TOWER ) return 1.0f;
	return -1.0f;
}

void DrawGonks()
{
	SortGonks();
	for ( Gonk* g : vGonks )
	{
		DrawGonk( g );
	}
}

void DrawGonk( Gonk* g )
{	
	Play::Vector2D newPos = TransformOrtho( g->pos3D );

	if ( g->spawnTimer < 0.0f )
	{
		int id = GetGonkSpriteID( g->spriteID, STRAIGHT );

		Play::DrawSprite( GetGonkSpriteID( g->spriteID, STRAIGHT ), newPos, (static_cast<int>(g->frame) % kMaxFrames + g->spriteDir * kMaxFrames) );
	}
}

void UpdateGonks()
{
	for ( Gonk* g : vGonks )
	{
		if ( g->spawnTimer < 0.0f )
		{
			if ( !(g->leftBuilding) )
			{
				g->order->source->gonks[ g->order->source->owner ]--;
				g->leftBuilding = true;
			} 

			g->progress += kGonkSpeed;
			g->frame++;

			UpdateGonkPosition( g );
			GonkTowerVisibility( g );
			MissileCollisions( g );
		}
		g->spawnTimer -= DELTA_TIME;
	}
	FightGonks();
}

void GonkTowerVisibility( Gonk* g )
{
	int towerIndex = IsGonkVisible( g );

	if ( towerIndex != -1 )
	{
		Play::Point3D pos = GetBuildingPos(towerIndex);
		Building* tower = GetBuilding( pos );
		if ( tower->lastFireTime > kFireInterval && tower->owner != g->spriteID )
		{
			tower->lastFireTime = 0.0f;
			Play::Vector2f distance = TransformOrtho(g->pos3D) - TransformOrtho(tower->pos3D);

			Missile* m = new Missile;
			m->targetY = g->pos3D.y;
			m->color = static_cast< MissileColor >(tower->owner);
			m->pos3D = GetBuildingPos( towerIndex );
			m->pos3D.y += GetBuildingHeight(tower);

			// projectile motion setup
			m->gravity = { 0.0f, -0.5f, 0.0f }; // gravity on y axis
			m->velocity.x = Play::dot(distance, { 1.0f, 0.0f }) * 0.02f; // distance vector projection on x axis
			m->velocity.y = ((m->velocity.x / distance.x) * distance.y - (m->gravity.y / 2) * (distance.x / m->velocity.x));
			
			AddMissileToArray( m );
		}
	}
}

void MissileCollisions( Gonk* g )
{
	for ( Missile* m : GetMissileArray() )
	{
		float mRadius = ( GetMissileWidth() / 2.0f ) * kMissileScale;
		float gRadius = Play::GetSpriteHeight( GetGonkSpriteID( WHITE )) / 2.0f;

		float distance = (m->pos3D - g->pos3D).Length();

		if ( distance < mRadius + gRadius )
		{
			Corpse* corpse = new Corpse;
			corpse->pos3D = g->pos3D;
			corpse->rotationBottom = static_cast<float>(Play::RandomRollRange(0, 628)) / 100.0f;
			corpse->rotationTop = static_cast<float>(Play::RandomRollRange(0, 628)) / 100.0f;
			corpse->spriteColor = g->spriteID;
			AddCorpseToArray( corpse );

			DeleteGonk( g );
			DeleteMissile( m );
			return;
		}
	}
}

void UpdateGonkPosition( Gonk* g )
{
	Play::Vector3f velocityPerp = TransformOrtho( g->velocity ).Perpendicular();

	GonkDirectionBugs( g, velocityPerp );

	float progressOnePercent = (g->order->dest->pos3D - g->order->source->pos3D).Length() / 100;
	float progressPercentage = g->progress / progressOnePercent;

	if ( g->progress < progressOnePercent * kGonkProgressPartOne)
	{	
		g->pos3D += g->velocity * kGonkSpeed + (g->offset * kOffsetMultiplyPartOne * (progressPercentage / 100.f) * velocityPerp);
	} 
	else if ( g->progress < progressOnePercent * kGonkProgressPartTwo)
	{
		g->pos3D += g->velocity * kGonkSpeed;
	}
	else
	{
		g->pos3D += g->velocity * kGonkSpeed - (g->offset * kOffsetMultiplyPartTwo * (1.0f - (progressPercentage / 100.f)) * velocityPerp);
	}
}

void GonkDirectionBugs( Gonk* g, Play::Vector3f& vPerp )
{
	// TODO - fix  annoying bugs
	// why I need to do this? For perpendicular gonk velocity, only two directions need rotation adjustment - others are correct
	if ( g->spriteDir == DIR_UP || g->spriteDir == DIR_DOWN )
	{
		vPerp = Play::MatrixRotation(-0.59f).Transform( (g->velocity).As2D() ).Perpendicular();
	} // sometimes the direction is set to right down instead of down, but just SOMETIMES. In both occasions (either it's right direction or not) the tendency persists throughout the game.
	if ( g->spriteDir == DIR_RIGHT_DOWN && g->velocity.x == 0 )
	{
		g->spriteDir = DIR_DOWN;
	}
}

void FightGonks()
{
	for ( int i = 0; i < vGonks.size(); i++ )
	{
		Gonk* gonk = vGonks[ i ];
		if ( IsTargetReached( gonk ) )
		{
			gonk->order->warriors--;
			GonkFight( gonk );			
			DeleteGonk( gonk );
			i--;
		}
	}
}

void DeleteGonk( Gonk* g )
{
	for ( int i = 0; i < vGonks.size(); i++ )
	{
		if ( vGonks[ i ]->pos3D == g->pos3D )
		{
			Gonk* gonk2 = vGonks[ vGonks.size() - 1 ];
			vGonks[ i ] = gonk2;
			vGonks.pop_back();

			if ( g->order->warriors == 0 )
			{
				DeleteOrder( g->order->id );
			}
			delete g;
			return;
		}
	}
}

void GonkFight( Gonk* g )
{
	( g->order->dest->owner != g->spriteID ) ?
		g->order->dest->gonks[ g->order->dest->owner ]-- :
		g->order->dest->gonks[ g->order->dest->owner ]++;

	if ( g->order->dest->prevGonks[ g->order->dest->owner ] > g->order->dest->gonks[ g->order->dest->owner ] )
	{
		Ghost* ghost = new Ghost;
		Play::Vector3f offset = { static_cast<float>(Play::RandomRollRange(-30, 70)), 0.0f, 0.0f };
		ghost->pos3D = g->order->dest->pos3D + offset;
		ghost->velocity = { 0.0f, kGonkSpeed, 0.0f };

		AddGhostToArray( ghost );
	}

	if ( g->order->dest->gonks[ g->order->dest->owner ] < 0 )
	{
		g->order->dest->owner = g->spriteID;
	}
}

void ClearGonks()
{
	for ( Gonk* g : vGonks )
	{
		delete g;
	}
	vGonks.clear();
}

void SortGonks()
{
	std::sort( vGonks.begin(), vGonks.end(), [](Gonk* a, Gonk* b) { return a->pos3D.y > b->pos3D.y; } );
}


const std::vector< Gonk* >& GetGonkArray()
{
	return vGonks;
}

void AddGonkToArray( Gonk* gonk )
{
	vGonks.push_back( gonk );
}

int GetDirectionGonk( const Play::Point3f& posSrc, const Play::Point3f& posTrg )
{
	Play::Vector2f toTarget = TransformOrtho( posTrg ) - TransformOrtho( posSrc );
	toTarget.Normalize();

	static int biggest{ 0 };

	for ( int i = 1; i < TOTAL_DIRECTIONS; i++ )
	{
		float dotDirection1 = Play::dot( toTarget, directionsNormalized[ biggest ] );
		float dotDirection2 = Play::dot( toTarget, directionsNormalized[ i ] );

		if ( dotDirection2 >= dotDirection1 )
		{
			biggest = i;
		}
	}
	return biggest;
}

bool IsTargetReached( Gonk* g )
{
	float distance = (g->order->dest->pos3D - g->order->source->pos3D).As2D().Length();

	if ( g->progress >= distance )
	{
		return true;
	}
	return false;
}



