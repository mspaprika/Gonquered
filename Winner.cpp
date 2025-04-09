#include "pch.h"
#include "GameMath.h"
#include "Player.h"
#include "GameState.h"
#include "Winner.h"


std::string winnerStrings[ P_TOTAL_COLORS ] =
{
	"WHITE Wins!",
	"BLUE Wins!",
	"YELLOW Wins!",
	"GREEN Wins!",
	"RED Wins!",
	"PURPLE Wins!",
};

void UpdateWinner( GameState& gState, int winner )
{
	if ( winner != -1 )
	{
		gState.state = STATE_WIN;
		gState.levelPassed = true;
	}
}

int GetWinner()
{
	return CheckWinner();
}

const std::string& GetWinnerString( int color )
{
	return winnerStrings[ color ];
}