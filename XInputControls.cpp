#include "Play.h"
#include <iostream>
#include "XInputControls.h"
#include <XInput.h>

#pragma comment(lib, "Xinput.lib") 


constexpr int kMaxPlayers{ 2 };

std::vector< bool > inputsReceived[ kMaxPlayers ]
{
    { false, false, false, false, false, false, false, false, false, false },
    { false, false, false, false, false, false, false, false, false, false }
};

std::vector< int > xBoxButtonBits
{
	XINPUT_GAMEPAD_DPAD_LEFT, XINPUT_GAMEPAD_DPAD_RIGHT, XINPUT_GAMEPAD_DPAD_UP, XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_A, XINPUT_GAMEPAD_B, XINPUT_GAMEPAD_X, XINPUT_GAMEPAD_Y,
    XINPUT_GAMEPAD_LEFT_SHOULDER , XINPUT_GAMEPAD_RIGHT_SHOULDER
};


bool XInputReceived( int button, int player ) 
{
    if ( XInputGetState == nullptr ) 
    {
        std::cerr << "XInput not available" << std::endl;
        return false;
    }

    XINPUT_STATE state;
    DWORD result = XInputGetState( player, &state );

    if ( result == ERROR_SUCCESS ) 
    {
        if ( state.Gamepad.wButtons & xBoxButtonBits[ button ] ) 
        {
            if ( !inputsReceived[ player ][ button ] )
            {
                inputsReceived[ player ][ button ] = true;
                return true;
            }
        }
        else 
        {
            inputsReceived[ player ][ button ] = false;
        }
    }
    else 
    {
        std::cerr << "Controller not connected" << std::endl;
    }

    return false;
}
