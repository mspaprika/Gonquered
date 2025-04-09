#pragma once

struct GameState;

void UpdateWinner( GameState& gState, int winner );
int GetWinner();
const std::string& GetWinnerString( int color );