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
#include <mutex>
#include <bitset>


enum e_KeyState {
	KEY_HELD = 0,	// key is held down
	KEY_PRESSED,	// key was pressed
	KEY_UNPRESSED,	// key was unpressed
	KEY_NOP			// you should never get this, it represents key being fully released ( if its fully released llkeyboard callback will never be called )
};


enum e_ButtonState {
	BUTTON_PRESSED = 0,
	BUTTON_WAS_PRESSED = 1
};


struct VirtualKey_t {
	std::vector<std::function<void( std::uint32_t /* vkCode */ )>> m_KeyCallbacks{ };

	//========================================================================================================
	// Purpose: Easily tell what "state" key is in ( note, do not call this outside of key change callback)
	//========================================================================================================
	e_KeyState GetKeyState( ) {
		std::scoped_lock( m_Mutex );

		// this isnt great, its really simple, works, and is easy to visualize.
		if ( m_bIsKeyDown )
			if ( m_bWasKeyDown )
				return e_KeyState::KEY_HELD;
			else
				return e_KeyState::KEY_PRESSED;
		else
			if ( m_bWasKeyDown )
				return e_KeyState::KEY_UNPRESSED;

		return e_KeyState::KEY_NOP;
	}



	//========================================================================================================
	// Note: Not Thread Safe
	//========================================================================================================
	bool& GetIsKeyDown( ) {
		std::scoped_lock( m_Mutex );
		return m_bIsKeyDown;
	}


	//========================================================================================================
	// Note: Not Thread Safe
	//========================================================================================================
	bool& GetWasKeyDown( ) {
		std::scoped_lock( m_Mutex );
		return m_bWasKeyDown;
	}


	//========================================================================================================
	// Constructor
	//========================================================================================================
	VirtualKey_t( ) = default;

private:

	bool m_bIsKeyDown = false;
	bool m_bWasKeyDown = false;

	std::mutex m_Mutex;
};
