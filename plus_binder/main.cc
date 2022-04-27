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
#include "plus_binder/keyboard.h"

void OnLeftDown( plus_binder::VirtualKey_t vkThisKey, uint32_t uVkCode ) {
	std::cout << "keystate changed\n";
}

int main( ) {
	std::cout << R"(
C++ Key Binding System
Written By: Blanket
Github: https://github.com/iBlanket/PlusBinder
)";

	plus_binder::CKeyboard::Get( ).Initialize( );

	plus_binder::CKeyboard::Get( ).SetCallback( VK_LEFT, OnLeftDown );

	std::cin.get( );
}
