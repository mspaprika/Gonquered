#pragma once

struct Player;

void RemoveSelections( Player* p );
void MoveSelector( Player* p, int direction );
void MakeSelection( Player* p );
void SelectionControls( Player* p );
void NavigateMap( Player* p );

