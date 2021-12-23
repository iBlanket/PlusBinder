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

void* KeyDown( int vkKey ) {
	VirtualKey_t* vkBind = &n_KeyBoard::VirtualKeys[ vkKey ];

	// only call this in callbacks
	auto keyState = vkBind->GetKeyState( );


	switch ( keyState ) {
		case e_KeyState::KEY_HELD:
		{
			std::cout << "Key is held down\n";
		}
		break;

		case e_KeyState::KEY_PRESSED:
		{
			std::cout << "Key was pressed\n";
		}
		break;

		case e_KeyState::KEY_UNPRESSED:
		{
			std::cout << "Key was released\n";
		}
		break;
	}

	return 0;
}

int main( ) {
	std::cout << R"(
C++ Key Binding System
Written By: Blanket
Github: https://github.com/fuckblanket
)";

	n_KeyBoard::Initialize( );

	n_KeyBoard::VirtualKeys[ VK_LEFT ].m_KeyCallbacks.push_back( KeyDown );


	std::cin.get( );
}
