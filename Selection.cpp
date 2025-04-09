#include "pch.h"
#include "Building.h"
#include "Player.h"
#include "Order.h"
#include "XInputControls.h"
#include "Selection.h"



void MakeSelection( Player* p )
{
	SelectionControls(p);
	UpgradeBuilding(p);

	if (Play::KeyPressed(p->controls[ REMOVE ]) || XInputReceived( REMOVE, p->id ))
	{
		RemoveSelections(p);
	}

	if (Play::KeyPressed(p->controls[ FRACTION ]) || XInputReceived( FRACTION, p->id ))
	{
		p->fraction = static_cast< FractionWarriors >( (p->fraction + 1) % TOTAL_FRACTIONS );
	}

	p->mode = (p->src == nullptr) ? SELECT_SOURCE : SELECT_TARGET;
}

void SelectionControls( Player* p )
{
	NavigateMap(p);

	
	if ((Play::KeyPressed(p->controls[ SELECT ]) || XInputReceived( SELECT, p->id )) && p->selected != nullptr)
	{
		if (p->src == nullptr)
		{
			if (p->selected->owner == p->color)
			{
				p->src = p->selected;
			}
		}
		else if (p->selected != nullptr && !(p->src->fight))
		{
			CreateOrder(p->src->owner, CalculateFractionGonks(p->src->gonks[p->src->owner], p->fraction), p->src, p->selected);
			RemoveSelections(p);
		}
	}
}

void NavigateMap( Player* p )
{
	if (Play::KeyPressed(p->controls[ UP ]) || XInputReceived( UP, p->id ))
	{
		MoveSelector( p, N_UP );
	}
	else if (Play::KeyPressed(p->controls[ DOWN ]) || XInputReceived( DOWN, p->id ))
	{
		MoveSelector( p, N_DOWN );
	}
	else if (Play::KeyPressed(p->controls[ LEFT ]) || XInputReceived( LEFT, p->id ))
	{
		MoveSelector( p, N_LEFT );
	}
	else if (Play::KeyPressed(p->controls[ RIGHT ]) || XInputReceived( RIGHT, p->id ))
	{
		MoveSelector( p, N_RIGHT );
	}
}

void MoveSelector( Player* p, int direction )
{
	if (p->selected == nullptr)
	{
		p->selected = GetBuilding( GetBuildingPos( GetBuildingArray()[ 0 ]->index ) );
		return;
	}

	int totalIndeces = GetBuildingArray().size();
	int rows = totalIndeces / kGridSize;
	int currentIndex = GetBuildingArrayIndex(p->selected->index);
	int index{ 0 };

	switch (direction)
	{
	case N_UP:
		index = GetBuildingArray()[((currentIndex + rows + totalIndeces) % totalIndeces)]->index;
		break;

	case N_DOWN:
		index = GetBuildingArray()[(currentIndex - rows + totalIndeces) % totalIndeces]->index;
		break;

	case N_LEFT:
		index = GetBuildingArray()[(currentIndex - 1 + totalIndeces) % totalIndeces]->index;
		break;

	case N_RIGHT:
		index = GetBuildingArray()[(currentIndex + 1 + totalIndeces) % totalIndeces]->index;
		break;

	default:
		break;
	}

	p->selected = GetBuilding( GetBuildingPos( index ) );
}

void RemoveSelections( Player* p )
{
	p->selected = nullptr;
	p->src = nullptr;
	p->fraction = FULL;
}