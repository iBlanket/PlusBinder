//=================================================
// File: main.cpp
// Written By: Blanket
// 
// Purpose: Example Usage
// 
// Project Todo:
// Add handling of mouse inputs
// Add keyflag stuff
// Clean up code some
// 
//=================================================

#include <iostream>
#include "keyboard.h"

void OnLeftDown( VirtualKey_t vkThisKey, uint32_t uVkCode ) {
	if ( vkThisKey.m_bIsDown ) { /* is key down? */
		if ( vkThisKey.m_bWasDown ) { /* if key is down and key was down then the user is holding the key */
			std::cout << "key is held down\n";

		} else {					  /* likewise, if the key is down and it wasnt down we know the use just hit the key */
			std::cout << "key just pressed\n";
		}

	} else {
		if ( vkThisKey.m_bWasDown ) { /* if user was holding key down and they arent now we know they just released the key */
			std::cout << "key was just released\n";

		} else					  /* this will never be hit because of how the low level hook works however */
			std::cout << "how did this get hit????\n";
	}
}

int main( ) {
	std::cout << R"(
C++ Key Binding System
Written By: Blanket
Github: https://github.com/iBlanket/PlusBinder
)";

	CKeyboard::Get( ).Initialize( );

	CKeyboard::Get( ).SetCallback( VK_LEFT, OnLeftDown );

	std::cin.get( );
}
