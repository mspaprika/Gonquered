#include "pch.h"
#include "GameMath.h"
#include "Building.h"
#include "Tower.h"
#include "Order.h"
#include "Selection.h"
#include "XInputControls.h"
#include "Player.h"



const char* selectionSprites[ TOTAL_COLORS ][ MAX_SELECTIONS ] =
{
	"Sel1_WHITE", "Sel2_WHITE", "Sel3_WHITE", "Arrow_WHITE",
	"Sel1_BLUE", "Sel2_BLUE", "Sel3_BLUE", "Arrow_BLUE",
	"Sel1_YELLOW", "Sel2_YELLOW", "Sel3_YELLOW", "Arrow_YELLOW",
	"Sel1_GREEN", "Sel2_GREEN", "Sel3_GREEN", "Arrow_GREEN",
	"Sel1_RED", "Sel2_RED", "Sel3_RED", "Arrow_RED",
	"Sel1_PURPLE", "Sel2_PURPLE", "Sel3_PURPLE", "Arrow_PURPLE",
};

int percentages[ TOTAL_FRACTIONS ] =
{
	25, 50, 75, 100
};

std::vector< Play::KeyboardButton > playersControls[ MAX_CONTROLS ] =
{
	{ Play::KEY_LEFT, Play::KEY_RIGHT, Play::KEY_UP, Play::KEY_DOWN, Play::KEY_ENTER, Play::KEY_BACKSPACE, Play::KEY_0, Play::KEY_SHIFT },  // player1
	{ Play::KEY_A, Play::KEY_D, Play::KEY_W, Play::KEY_S, Play::KEY_TAB, Play::KEY_Q, Play::KEY_1, Play::KEY_CTRL },  // player2
};

std::vector< Player* > vPlayers;
std::string selectModes[ kMaxPlayers ] = { "source", "target" };
int  selectionSpritesIDs[ TOTAL_COLORS ][ MAX_SELECTIONS ];
int players[ kMaxPlayers ] = { BLUE, PURPLE };
int  buildingsForPlayer{ 0 };
std::vector< Building* > copyBuildings;


void AddSelectionSpritesIDs()
{
	for ( int i = 0; i < TOTAL_COLORS; i++ )
	{
		for ( int j = 0; j < MAX_SELECTIONS; j++ )
		{
			selectionSpritesIDs[ i ][ j ] = Play::GetSpriteId( selectionSprites[ i ][ j ] );
		}
	}
}

void CreatePlayers()
{
	const std::vector< Building* >& vBuildings = GetBuildingArray();
	copyBuildings = vBuildings;

	for ( int i = 0; i < kMaxPlayers; i++ )
	{
		CreateSinglePlayer( playersControls[ i ], players[ i ], i );
	
		SetPlayerBuildings( players[ i ]);
	}

	SetTowers();
}

void CreateSinglePlayer( const std::vector< Play::KeyboardButton >& buttons, int c, int ID )
{
	Player* player = new Player;
	player->color = static_cast< PlayerColors >(c);
	player->id = ID;
	player->controls[ LEFT ] = buttons[ LEFT ];
	player->controls[ RIGHT ] = buttons[ RIGHT ];
	player->controls[ UP ] = buttons[ UP ];
	player->controls[ DOWN ] = buttons[ DOWN ];
	player->controls[ SELECT ] = buttons[ SELECT ];
	player->controls[ REMOVE ] = buttons[ REMOVE ];
	player->controls[ FRACTION ] = buttons[ FRACTION ];
	player->controls[ UPGRADE ] = buttons[ UPGRADE ];

	vPlayers.push_back( player );
}

void UpdatePlayers()
{
	UpdateOrders();

	for ( Player* p : vPlayers )
	{
		MakeSelection( p );		
		p->frame++;
	}
}

void DrawPlayerDebug()
{
	Player* p = vPlayers[ 0 ];
	Play::DrawFontText("64", "Select mode: " + selectModes[ p->mode ], { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 50 });
}

void DrawPlayers()
{
	for ( Player* p: vPlayers )
	{
		if ( p->selected != nullptr )
		{
			static int frame{ 0 };
			Play::Vector2D newPos = TransformOrtho( p->selected->pos3D );
			Play::DrawSpriteRotated( selectionSpritesIDs[ p->color ][ p->mode ], newPos, p->frame, 0.0f, 2.f );
		}
		if ( p->src != nullptr )
		{
			static int frame{ 0 };
			Play::Vector2D newPos = TransformOrtho( p->src->pos3D );
			Play::DrawSpriteRotated( selectionSpritesIDs[ p->color ][ SELECT_SOURCE ], newPos, p->frame, 0.0f, 2.0f );		
		}
		if ( p->selected != nullptr && p->src != nullptr )
		{
			Play::Vector3f newPos = TransformOrtho( p->src->pos3D );
			Play::Vector3f toTarget = TransformOrtho( p->selected->pos3D - p->src->pos3D );
			float angle = atan2( toTarget.y, toTarget.x ) + 3.14f;
			float length = toTarget.Length();
			toTarget.Normalize();
			 
			Play::DrawSpriteRotated( selectionSpritesIDs[ p->color ][ ARROW ], newPos + (toTarget * (length / 2)), 0, angle , 1.0f );
			Play::DrawDebugText( { newPos.x - 70, newPos.y + 150 }, (std::to_string(percentages[ p->fraction ])).c_str(), Play::cBlack);
		}	
	}
}

int CheckWinner()
{
	static int winner{ -1 };

	const std::vector< Building* >& vBuildings = GetBuildingArray();
	if ( vBuildings.size() == 0 ) return -1;

	winner = vBuildings[ 0 ]->owner;

	for (int i = 1; i < vBuildings.size(); i++)
	{
		Play::Point3D pos = GetBuildingPos( vBuildings[ i ]->index );
		Building* b = GetBuilding( pos );

		int testWinner = b->owner;
		if ( testWinner != winner )
		{
			return -1;
		}	
	}
	return winner;
}

void ClearPlayers()
{
	for (Player* p : vPlayers)
	{
		delete p;
	}
	vPlayers.clear();
}



int CalculateFractionGonks( int gonks, int fraction )
{
	return static_cast<int>( static_cast<float>(gonks / 100.0f) * percentages[ fraction ] );
}

int& GetBuildingsForPlayerCount()
{
	return buildingsForPlayer;
}

void SetPlayerBuildings( int player )
{
	SetBuildingsForPlayer( buildingsForPlayer );

	for (int i = 0; i < buildingsForPlayer; i++)
	{
		std::vector< int >& buildings = GetLevelIndeces();
		int roll = Play::RandomRollRange(0, buildings.size() - 1);

		Building* b = copyBuildings[ roll ];
		b->owner = player;
		b->gonks[ b->owner ] = Play::RandomRollRange(15, 20);
		b->prevGonks[ b->owner ] = b->gonks[ b->owner ];

		copyBuildings.erase(copyBuildings.begin() + roll);
		buildings.erase(buildings.begin() + roll);
	}
}

void SetBuildingsForPlayer( int& buildingCount )
{
	size_t bSize = GetBuildingArray().size();

	if ( bSize > 8 )
	{
		buildingCount = kBuildingCountDefault;
	}
	else if ( bSize > 5 )
	{
		buildingCount = kBuildingCountPlayerLevel2;
	}
	else
	{
		buildingCount = kBuildingCountPlayerLevel1;
	}
}

void UpgradeBuilding( Player* p )
{
	if ((Play::KeyPressed(p->controls[ UPGRADE ]) || XInputReceived( UPGRADE, p->id )) && p->selected != nullptr && p->src == nullptr && p->color == p->selected->owner)
	{
		if (p->selected->type == BUILD_LEVEL1 && p->selected->gonks[ p->color ] >= kPriceBuildLevel2)
		{
			p->selected->gonks[ p->color ] -= kPriceBuildLevel2;
			p->selected->type = BUILD_LEVEL2;
		}
		else if (p->selected->type == BUILD_LEVEL2 && p->selected->gonks[ p->color ] >= kPriceBuildLevel3)
		{
			p->selected->gonks[ p->color ] -= kPriceBuildLevel3;
			p->selected->type = BUILD_LEVEL3;
		}
		else if (p->selected->type != BUILD_TOWER && p->selected->gonks[ p->color ] >= kPriceBuildTower)
		{
			p->selected->gonks[ p->color ] -= kPriceBuildTower;
			p->selected->type = BUILD_TOWER;
			AddTowerToArray( p->selected->index );
		}
	}
}