//=================================================
// File: vbind.h
// Written By: Blanket
// 
// Purpose: Representing Virtual Key Data
// 
//=================================================


#pragma once
#include <vector>

typedef void( __cdecl* pKeyStateCallback )( int vkKey );

enum e_KeyState {
	KEY_HELD = 0,	// key is held down
	KEY_PRESSED,	// key was pressed
	KEY_UNPRESSED,	// key was unpressed
	KEY_NOP			// you should never get this, it represents key being fully released (if its fully released llkeyboard callback will never be called)
};

struct VirtualKey_t {
private:

public:
	std::vector<pKeyStateCallback> m_KeyCallbacks{ };

	// todo: use a vector of bools for storing previous states
	bool m_bWasDown = false;
	bool m_bIsDown = false;


	//========================================================================================================
	// Purpose: Easily tell what "state" key is in ( note, do not call this outside of key change callback)
	//========================================================================================================
	e_KeyState GetKeyState( ) {
		/* this may be the worst code ive written in my entire life... */
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
};