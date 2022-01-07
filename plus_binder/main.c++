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

void KeyDown( DWORD vkKey ) {
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

}

void KeyDown2( DWORD vkKey ) {
	std::cout << "callback2\n";
}
int main( ) {
	std::cout << R"(
C++ Key Binding System
Written By: Blanket
Github: https://github.com/fuckblanket/PlusBinder
)";

	n_KeyBoard::Initialize( );

	n_KeyBoard::VirtualKeys[ VK_LEFT ].m_KeyCallbacks.emplace_back( KeyDown );
	n_KeyBoard::VirtualKeys[ VK_LEFT ].m_KeyCallbacks.pop_back( );
	n_KeyBoard::VirtualKeys[ VK_LEFT ].m_KeyCallbacks.emplace_back( KeyDown2 );

	std::cin.get( );
}
