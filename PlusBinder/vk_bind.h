//=================================================
// File: vk_bind.h
// Written By: Blanket
// 
// Purpose: Representing Virtual Key Data
// 
//=================================================


#pragma once
#include <vector>
#include <functional>


enum e_KeyState {
	KEY_HELD = 0,	// key is held down
	KEY_PRESSED,	// key was pressed
	KEY_UNPRESSED,	// key was unpressed
	KEY_NOP			// you should never get this, it represents key being fully released ( if its fully released llkeyboard callback will never be called )
};

struct VirtualKey_t {
	std::vector<std::function<void( int /* vkCode */ )>> m_KeyCallbacks{ };

	// todo: use a vector of bools for storing previous states
	bool m_bWasDown = false;
	bool m_bIsDown = false;


	//========================================================================================================
	// Purpose: Easily tell what "state" key is in ( note, do not call this outside of key change callback)
	//========================================================================================================
	e_KeyState GetKeyState( ) {
		// this isnt great, its really simple, works, and is easy to visualize.
		if ( m_bIsDown )
			if ( m_bWasDown )
				return e_KeyState::KEY_HELD;
			else
				return e_KeyState::KEY_PRESSED;
		else
			if ( m_bWasDown )
				return e_KeyState::KEY_UNPRESSED;

		return e_KeyState::KEY_NOP;
	}

	VirtualKey_t( ) = default;

private:

};
